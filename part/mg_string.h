#ifndef MG_STRING_H
#define MG_STRING_H


#ifdef _WIN32

// For Windows, change all slashes to backslashes in path names.
void change_slashes_to_backslashes(char *path);


// Encode 'path' which is assumed UTF-8 string, into UNICODE string.
// wbuf and wbuf_len is a target buffer and its length.
void to_unicode(const char *path, wchar_t *wbuf, size_t wbuf_len);

#else


#endif


void mg_strlcpy(register char *dst, register const char *src, size_t n);

int lowercase(const char *s);

int mg_strncasecmp(const char *s1, const char *s2, size_t len);

int mg_strcasecmp(const char *s1, const char *s2);

char * mg_strndup(const char *ptr, size_t len);

char * mg_strdup(const char *str);

int mg_vsnprintf(struct mg_connection *conn, char *buf, size_t buflen, const char *fmt, va_list ap);

int mg_snprintf(struct mg_connection *conn, char *buf, size_t buflen, const char *fmt, ...);

char *skip(char **buf, const char *delimiters);

void cry(struct mg_connection *conn, const char *fmt, ...);

#endif /* MG_STRING_H */
