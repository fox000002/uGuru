#ifndef U_GLOBAL_H
#define U_GLOBAL_H

/*! \mainpage uGuru
 *
 * \section intro_sec Introduction
 *
 * What is uGuru?
 * Some useful macros, functions and classes for windows API development.
 *
 * 1. Simple wrappers for win32 window, dialog and controls.
 *
 * 2. Simple wrappers for win32 process, thread and pipe.
 *
 * 3. Simple wrappers for system information query.
 *
 * 4. Simple wrappers for gdi, opengl and image.
 *
 * 5. Simple wrappers for DLL.
 *
 * 6. Simple wrappers for plugin architecture.
 *
 * 7. Simple wrappers for Hooks.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Edit the file make.inc
 *
 * \subsection step2 Step 2: run Make
 *
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void w2printf(const char *format, ...);

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
#ifdef DEBUG
void odprintf(const char *format, ...);
void write2file(const char *format, ...);
void reset_debug();
//#define LOG_STRING odprintf
#define LOG_STRING write2file
//#define LOG_STRING(format, args...) UDebugger::odprintf(format, ##args)
#else
void write2file(const char *format, ...);
void reset_debug();
#define LOG_STRING write2file
#endif

/*
#define CHECK_PTR(p) \
if (!p) {     \
    delete p; \
}

#define CHECK_PTR_ARRAY(p) \
    if (!p) {     \
    delete [] p; \
    }

// CommandLineToArgv converts a command-line string to argc and
// argv similar to the ones in the standard main function.
// This is a specialized version coded specifically for rundll32
// and is not intended to be used in any other program.
LPTSTR *WINAPI CommandLineToArgv(LPCTSTR lpCmdLine, int *lpArgc);
*/


typedef void (*PFSpCallback)();
BOOL startProgramCallback( const char *cmdline, const char *wdir, BOOL bWait, PFSpCallback pfc);

typedef void (*PFSpCallbackParam)(void *userData);
BOOL startProgramCallbackParam( const char *cmdline, const char *wdir, BOOL bWait, PFSpCallbackParam pfc, void *data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // U_GLOBAL_H
