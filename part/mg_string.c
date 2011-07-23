#include "mg_defs.h"
#include "mongoose.h"

#include "mg_ssl.h"

// Darwin prior to 7.0 and Win32 do not have socklen_t
#ifdef NO_SOCKLEN_T
typedef int socklen_t;
#endif // NO_SOCKLEN_T


// Unified socket address. For IPv6 support, add IPv6 address structure
// in the union u.
struct usa {
  socklen_t len;
  union {
    struct sockaddr sa;
    struct sockaddr_in sin;
  } u;
};

// Describes listening socket, or socket which was accept()-ed by the master
// thread and queued for future handling by the worker thread.
struct socket {
  struct socket *next;  // Linkage
  SOCKET sock;          // Listening socket
  struct usa lsa;       // Local socket address
  struct usa rsa;       // Remote socket address
  int is_ssl;           // Is socket SSL-ed
  int is_proxy;
};

struct mg_connection {
  struct mg_connection *peer; // Remote target in proxy mode
  struct mg_request_info request_info;
  struct mg_context *ctx;
  SSL *ssl;                   // SSL descriptor
  struct socket client;       // Connected client
  time_t birth_time;          // Time connection was accepted
  int64_t num_bytes_sent;     // Total bytes sent to client
  int64_t content_len;        // Content-Length header value
  int64_t consumed_content;   // How many bytes of content is already read
  char *buf;                  // Buffer for received data
  int buf_size;               // Buffer size
  int request_len;            // Size of the request + headers in a buffer
  int data_len;               // Total size of data in a buffer
};


#include "mg_string.h"

#ifdef _WIN32

// For Windows, change all slashes to backslashes in path names.
void change_slashes_to_backslashes(char *path)
{
	int i;

	for (i = 0; path[i] != '\0'; i++) {
		if (path[i] == '/')
			path[i] = '\\';
		// i > 0 check is to preserve UNC paths, like \\server\file.txt
		if (path[i] == '\\' && i > 0)
			while (path[i + 1] == '\\' || path[i + 1] == '/')
				(void) memmove(path + i + 1,
				path + i + 2, strlen(path + i + 1));
	}
}

// Encode 'path' which is assumed UTF-8 string, into UNICODE string.
// wbuf and wbuf_len is a target buffer and its length.
void to_unicode(const char *path, wchar_t *wbuf, size_t wbuf_len)
{
	char buf[PATH_MAX], *p;

	mg_strlcpy(buf, path, sizeof(buf));
	change_slashes_to_backslashes(buf);

	// Point p to the end of the file name
	p = buf + strlen(buf) - 1;

	// Trim trailing backslash character
	while (p > buf && *p == '\\' && p[-1] != ':') {
		*p-- = '\0';
	}

	// Protect from CGI code disclosure.
	// This is very nasty hole. Windows happily opens files with
	// some garbage in the end of file name. So fopen("a.cgi    ", "r")
	// actually opens "a.cgi", and does not return an error!
	if (*p == 0x20 ||               // No space at the end
		(*p == 0x2e && p > buf) ||  // No '.' but allow '.' as full path
		*p == 0x2b ||               // No '+'
		(*p & ~0x7f)) {             // And generally no non-ascii chars
			(void) fprintf(stderr, "Rejecting suspicious path: [%s]", buf);
			buf[0] = '\0';
	}

	(void) MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, (int) wbuf_len);
}




#else


#endif


void mg_strlcpy(register char *dst, register const char *src, size_t n)
{
	for (; *src != '\0' && n > 1; n--) {
		*dst++ = *src++;
	}
	*dst = '\0';
}


int lowercase(const char *s) {
	return tolower(* (unsigned char *) s);
}

int mg_strncasecmp(const char *s1, const char *s2, size_t len) {
	int diff = 0;

	if (len > 0)
		do {
			diff = lowercase(s1++) - lowercase(s2++);
		} while (diff == 0 && s1[-1] != '\0' && --len > 0);

	return diff;
}

int mg_strcasecmp(const char *s1, const char *s2) {
	int diff;

	do {
		diff = lowercase(s1++) - lowercase(s2++);
	} while (diff == 0 && s1[-1] != '\0');

	return diff;
}

char * mg_strndup(const char *ptr, size_t len) {
	char *p;

	if ((p = (char *) malloc(len + 1)) != NULL) {
		mg_strlcpy(p, ptr, len + 1);
	}

	return p;
}

char * mg_strdup(const char *str) {
	return mg_strndup(str, strlen(str));
}

// Like snprintf(), but never returns negative value, or the value
// that is larger than a supplied buffer.
// Thanks to Adam Zeldis to pointing snprintf()-caused vulnerability
// in his audit report.
int mg_vsnprintf(struct mg_connection *conn, char *buf, size_t buflen,
	const char *fmt, va_list ap) {
		int n;

		if (buflen == 0)
			return 0;

		n = vsnprintf(buf, buflen, fmt, ap);

		if (n < 0) {
			cry(conn, "vsnprintf error");
			n = 0;
		} else if (n >= (int) buflen) {
			cry(conn, "truncating vsnprintf buffer: [%.*s]",
				n > 200 ? 200 : n, buf);
			n = (int) buflen - 1;
		}
		buf[n] = '\0';

		return n;
}

int mg_snprintf(struct mg_connection *conn, char *buf, size_t buflen,
	const char *fmt, ...) {
		va_list ap;
		int n;

		va_start(ap, fmt);
		n = mg_vsnprintf(conn, buf, buflen, fmt, ap);
		va_end(ap);

		return n;
}

// Skip the characters until one of the delimiters characters found.
// 0-terminate resulting word. Skip the rest of the delimiters if any.
// Advance pointer to buffer to the next word. Return found 0-terminated word.
char *skip(char **buf, const char *delimiters) {
	char *p, *begin_word, *end_word, *end_delimiters;

	begin_word = *buf;
	end_word = begin_word + strcspn(begin_word, delimiters);
	end_delimiters = end_word + strspn(end_word, delimiters);

	for (p = end_word; p < end_delimiters; p++) {
		*p = '\0';
	}

	*buf = end_delimiters;

	return begin_word;
}