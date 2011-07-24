#include "mg_defs.h"
#include "mg_pthread.h"
#include "mongoose.h"
#include "mg_ssl.h"
#include "mg_socket.h"

#include "mg_config.h"
#include "mg_file.h"


#include "mg_string.h"

#if defined(_WIN32)

FILE *mg_fopen(const char *path, const char *mode)
{
	wchar_t wbuf[PATH_MAX], wmode[20];

	to_unicode(path, wbuf, ARRAY_SIZE(wbuf));
	MultiByteToWideChar(CP_UTF8, 0, mode, -1, wmode, ARRAY_SIZE(wmode));

	return _wfopen(wbuf, wmode);
}

#else


#endif
