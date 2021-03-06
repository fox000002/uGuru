#include "mg_defs.h"
#include "mg_pthread.h"
#include "mongoose.h"
#include "mg_ssl.h"
#include "mg_socket.h"

#include "mg_config.h"

#include "mg_string.h"

#include "mg_mime.h"

const struct MIME_Type builtin_mime_types[] = {
  {".html", 5, "text/html",   9},
  {".htm", 4, "text/html",   9},
  {".shtm", 5, "text/html",   9},
  {".shtml", 6, "text/html",   9},
  {".css", 4, "text/css",   8},
  {".js",  3, "application/x-javascript", 24},
  {".ico", 4, "image/x-icon",   12},
  {".gif", 4, "image/gif",   9},
  {".jpg", 4, "image/jpeg",   10},
  {".jpeg", 5, "image/jpeg",   10},
  {".png", 4, "image/png",   9},
  {".svg", 4, "image/svg+xml",  13},
  {".torrent", 8, "application/x-bittorrent", 24},
  {".wav", 4, "audio/x-wav",   11},
  {".mp3", 4, "audio/x-mp3",   11},
  {".mid", 4, "audio/mid",   9},
  {".m3u", 4, "audio/x-mpegurl",  15},
  {".ram", 4, "audio/x-pn-realaudio",  20},
  {".xml", 4, "text/xml",   8},
  {".xslt", 5, "application/xml",  15},
  {".ra",  3, "audio/x-pn-realaudio",  20},
  {".doc", 4, "application/msword",  19},
  {".exe", 4, "application/octet-stream", 24},
  {".zip", 4, "application/x-zip-compressed", 28},
  {".xls", 4, "application/excel",  17},
  {".tgz", 4, "application/x-tar-gz",  20},
  {".tar", 4, "application/x-tar",  17},
  {".gz",  3, "application/x-gunzip",  20},
  {".arj", 4, "application/x-arj-compressed", 28},
  {".rar", 4, "application/x-arj-compressed", 28},
  {".rtf", 4, "application/rtf",  15},
  {".pdf", 4, "application/pdf",  15},
  {".swf", 4, "application/x-shockwave-flash",29},
  {".mpg", 4, "video/mpeg",   10},
  {".mpeg", 5, "video/mpeg",   10},
  {".asf", 4, "video/x-ms-asf",  14},
  {".avi", 4, "video/x-msvideo",  15},
  {".bmp", 4, "image/bmp",   9},
  {NULL,  0, NULL,    0}
};

// Look at the "path" extension and figure what mime type it has.
// Store mime type in the vector.
void get_mime_type(struct mg_context *ctx, const char *path,
                          struct vec *vec)
{
  struct vec ext_vec, mime_vec;
  const char *list, *ext;
  size_t i, path_len;

  path_len = strlen(path);

  // Scan user-defined mime types first, in case user wants to
  // override default mime types.
  list = ctx->config[EXTRA_MIME_TYPES];
  while ((list = next_option(list, &ext_vec, &mime_vec)) != NULL) {
    // ext now points to the path suffix
    ext = path + path_len - ext_vec.len;
    if (mg_strncasecmp(ext, ext_vec.ptr, ext_vec.len) == 0) {
      *vec = mime_vec;
      return;
    }
  }

  // Now scan built-in mime types
  for (i = 0; builtin_mime_types[i].extension != NULL; i++) {
    ext = path + (path_len - builtin_mime_types[i].ext_len);
    if (path_len > builtin_mime_types[i].ext_len &&
        mg_strcasecmp(ext, builtin_mime_types[i].extension) == 0) {
      vec->ptr = builtin_mime_types[i].mime_type;
      vec->len = builtin_mime_types[i].mime_type_len;
      return;
    }
  }

  // Nothing found. Fall back to "text/plain"
  vec->ptr = "text/plain";
  vec->len = 10;
}