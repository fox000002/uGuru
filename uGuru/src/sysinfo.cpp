#if defined(_WIN32)
#define _CRT_SECURE_NO_WARNINGS  // Disable deprecation warning in VS2005
#else
#define _XOPEN_SOURCE 600  // For PATH_MAX on linux
#endif

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdarg.h>

#include "mongoose.h"

#ifdef _WIN32
#include <windows.h>
#include <winsvc.h>
#define DIRSEP '\\'
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define sleep(x) Sleep((x) * 1000)
#define WINCDECL __cdecl
#else
#include <sys/wait.h>
#include <unistd.h>
#define DIRSEP '/'
#define WINCDECL
#endif // _WIN32

#include "sysinfo.h"

extern "C" {

int is_win()
{
#ifdef _WIN32
    return 1;
#else
    return 0;
#endif
}

int is_32()
{
    return 1;
}

int is_win32()
{
    return is_win() && is_32();
}

int cpu_num()
{
    int n = 1;

#if defined(_WIN32)
    SYSTEM_INFO siSysInfo;
    // Copy the hardware information to the SYSTEM_INFO structure.
    GetSystemInfo(&siSysInfo);

    n = (int)siSysInfo.dwNumberOfProcessors;
#else


#endif // _WIN32

    return n;
}

int system_load()
{
    return 0;
}

}
