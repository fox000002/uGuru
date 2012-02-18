#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#if defined(_WIN32)

#include <windows.h>
#include <tchar.h>

#include "global.h"

#define vsnprintf _vsnprintf

extern "C" {

void odprintf(const char *format, ...)
{
    char    buf[4096], *p = buf;
    va_list args;
    int     n;

    va_start(args, format);
    n = _vsnprintf(p, sizeof(buf) - 3, format, args); // buf-3 is room for CR/LF/NUL
    va_end(args);

    p += (n < 0) ? sizeof buf - 3 : n;

    while ( p > buf  &&  isspace(p[-1]) )
        *--p = '\0';

    *p++ = '\r';
    *p++ = '\n';
    *p   = '\0';

    ::OutputDebugStringA(buf);
}



/*
// CommandLineToArgv converts a command-line string to argc and
// argv similar to the ones in the standard main function.
// This is a specialized version coded specifically for rundll32
// and is not intended to be used in any other program.
LPTSTR *WINAPI CommandLineToArgv(LPCTSTR lpCmdLine, int *lpArgc)
{
    LPTSTR *argv, lpSrc, lpDest, lpArg;
    int argc, nBSlash, nNames;
    BOOL bInQuotes, bFirstChar;

    // If null was passed in for lpCmdLine, there are no arguments
    if (!lpCmdLine)
    {
        if (lpArgc)
        {
            *lpArgc = 0;
        }
        return 0;
    }

    lpSrc = (LPTSTR)lpCmdLine;
    // Skip spaces at beginning
    while (*lpSrc == _T(' ') || *lpSrc == _T('\t'))
    {
        lpSrc++;
    }

    // If command-line starts with null, there are no arguments
    if (*lpSrc == 0)
    {
        if (lpArgc)
        {
            *lpArgc = 0;
        }
        return 0;
    }

    lpArg = lpSrc;
    argc = 0;
    nBSlash = 0;
    bInQuotes = FALSE;
    bFirstChar = TRUE;
    nNames = 0;

    // Count the number of arguments
    while (nNames < 4)
    {
        if (*lpSrc == 0 || (*lpSrc == _T(',') && nNames == 2)
                || ((*lpSrc == _T(' ') || *lpSrc == _T('\t')) && !bInQuotes))
        {
            // Whitespace not enclosed in quotes signals the start of another argument

            argc++;

            // Skip whitespace between arguments
            while (*lpSrc == _T(' ') || *lpSrc == _T('\t') || (*lpSrc == _T(',') && nNames == 2))
                lpSrc++;
            if (*lpSrc == 0)
                break;
            if (nNames >= 3)
            {
                // Increment the count for the last argument
                argc++;
                break;
            }
            nBSlash = 0;
            bFirstChar = TRUE;
            continue;
        }
        else if (*lpSrc == _T('\\'))
        {
            // Count consecutive backslashes
            nBSlash++;
            bFirstChar = FALSE;
        }
        else if (*lpSrc == _T('\"') && !(nBSlash & 1))
        {
            // Open or close quotes
            bInQuotes = !bInQuotes;
            nBSlash = 0;
        }
        else
        {
            // Some other character
            nBSlash = 0;
            if (bFirstChar && ((*lpSrc != _T('/') && nNames <= 1) || nNames > 1))
                nNames++;
            bFirstChar = FALSE;
        }
        lpSrc++;
    }

    // Allocate space for the pointers in argv and the strings in one block
    argv = (LPTSTR *)malloc(argc * sizeof(LPTSTR) + (_tcslen(lpArg) + 1) * sizeof
            (TCHAR));

    if (!argv)
    {
        // Memory allocation failed
        if (lpArgc)
            *lpArgc = 0;
        return 0;
    }

    lpSrc = lpArg;
    lpDest = lpArg = (LPTSTR)(argv + argc);
    argc = 0;
    nBSlash = 0;
    bInQuotes = FALSE;
    bFirstChar = TRUE;
    nNames = 0;

    // Fill the argument array
    while (nNames < 4)
    {
        if (*lpSrc == 0 || (*lpSrc == _T(',') && nNames == 2) || ((*lpSrc == _T
                        (' ') || *lpSrc == _T('\t')) && !bInQuotes))
        {
            // Whitespace not enclosed in quotes signals the start of another argument

            // Null-terminate argument
            *lpDest++ = 0;
            argv[argc++] = lpArg;

            // Skip whitespace between arguments
            while (*lpSrc == _T(' ') || *lpSrc == _T('\t') || (*lpSrc == _T(',') && nNames == 2))
                lpSrc++;
            if (*lpSrc == 0)
                break;
            lpArg = lpDest;
            if (nNames >= 3)
            {
                // Copy the rest of the command-line to the last argument
                argv[argc++] = lpArg;
                _tcscpy(lpArg,lpSrc);
                break;
            }
            nBSlash = 0;
            bFirstChar = TRUE;
            continue;
        }
        else if (*lpSrc == _T('\\'))
        {
            *lpDest++ = _T('\\');
            lpSrc++;

            // Count consecutive backslashes
            nBSlash++;
            bFirstChar = FALSE;
        }
        else if (*lpSrc == _T('\"'))
        {
            if (!(nBSlash & 1))
            {
                // If an even number of backslashes are before the quotes,
                // the quotes don't go in the output
                lpDest -= nBSlash / 2;
                bInQuotes = !bInQuotes;
            }
            else
            {
                // If an odd number of backslashes are before the quotes,
                // output a quote
                lpDest -= (nBSlash + 1) / 2;
                *lpDest++ = _T('\"');
                bFirstChar = FALSE;
            }
            lpSrc++;
            nBSlash = 0;
        }
        else
        {
            // Copy other characters
            if (bFirstChar && ((*lpSrc != _T('/') && nNames <= 1) || nNames > 1))
                nNames++;
            *lpDest++ = *lpSrc++;
            nBSlash = 0;
            bFirstChar = FALSE;
        }
    }

    if (lpArgc)
        *lpArgc = argc;
    return argv;
}
*/


BOOL startProgramCallback( const char *cmdline, const char *wdir, BOOL bWait, PFSpCallback pfc)
{
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        BOOL bResult;

        ::ZeroMemory( &si, sizeof(STARTUPINFO) );
        si.cb = sizeof(si);
        si.dwFlags=STARTF_USESHOWWINDOW;
        si.wShowWindow=SW_HIDE;

        ::ZeroMemory( &pi, sizeof(PROCESS_INFORMATION) );

        bResult = ::CreateProcess(NULL,
            (TCHAR *)cmdline,
            NULL,
            NULL,
            TRUE,
            NORMAL_PRIORITY_CLASS,
            NULL,
            wdir,
            &si,
            &pi);

        if (!bResult)
        {
            fprintf(stderr, "Failed to start %s\n", cmdline);
            LOG_STRING("Failed to start %s", cmdline);

            if (pfc)
            {
                pfc();
            }

            ::ExitThread(123);
            return FALSE;
        }

        if (bWait)
        {
            ::WaitForSingleObject(pi.hProcess, INFINITE);
        }

        //g_hChildProcess = pi.hProcess;

        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return TRUE;
}

BOOL startProgramCallbackParam( const char *cmdline, const char *wdir, BOOL bWait, PFSpCallbackParam pfc, void * data)
{
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        BOOL bResult;

        ::ZeroMemory( &si, sizeof(STARTUPINFO) );
        si.cb = sizeof(si);
        si.dwFlags=STARTF_USESHOWWINDOW;
        si.wShowWindow=SW_HIDE;

        ::ZeroMemory( &pi, sizeof(PROCESS_INFORMATION) );

        bResult = ::CreateProcess(NULL,
            (TCHAR *)cmdline,
            NULL,
            NULL,
            TRUE,
            NORMAL_PRIORITY_CLASS,
            NULL,
            wdir,
            &si,
            &pi);

        if (!bResult)
        {
            fprintf(stderr, "Failed to start %s\n", cmdline);
            LOG_STRING("Failed to start %s", cmdline);

            if (pfc)
            {
                pfc(data);
            }

            //::ExitThread(123);
            return FALSE;
        }

        if (bWait)
        {
            ::WaitForSingleObject(pi.hProcess, INFINITE);
        }

        //g_hChildProcess = pi.hProcess;

        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return TRUE;
}


}

#else

#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>

#include "global.h"


BOOL startProgramCallback( const char *cmdline, const char *wdir, BOOL bWait, PFSpCallback pfc)
{
    pid_t pid;
    int status;

    char * exe;
    int argc;
    char ** argv;

    argv = CommandLineToArgv(cmdline, &argc);

    exe = argv[0];


    /* Attempt to fork and check for errors */
    if( (pid=fork()) == -1)
    {
        LOG_STRING("Fork error. Exiting.");  /* something went wrong */

        if (pfc)
        {
           pfc();
        }

        return FALSE;
    }


    if (pid > 0)  // parent
    {
        if (bWait)
        {
            waitpid(pid, &status, 0);
        }
        return status;
    }
    else if (pid == 0) // child
    {
        if (chdir(wdir) != 0)
        {
            LOG_STRING("Failed to chdir: %s", wdir);
        }

        execvp(exe, argv);
        exit(1);
    }


    return FALSE;
}

BOOL startProgramCallbackParam( const char *cmdline, const char *wdir, BOOL bWait, PFSpCallbackParam pfc, void *data)
{

    pid_t pid;
    int status;

    char * exe;
    int argc;
    char ** argv;

    argv = CommandLineToArgv(cmdline, &argc);

    exe = argv[0];

    /* Attempt to fork and check for errors */
    if( (pid=fork()) == -1)
    {
        LOG_STRING("Fork error. Exiting.");  /* something went wrong */

        if (pfc)
        {
           pfc(data);
        }

        return FALSE;
    }


    if (pid > 0)  // parent
    {
        if (bWait)
        {
            waitpid(pid, &status, 0);
        }
        return status;
    }
    else if (pid == 0) // child
    {
        if (chdir(wdir) != 0)
        {
            LOG_STRING("Failed to chdir: %s", wdir);
        }

        execvp(exe, argv);
        exit(1);
    }


    return FALSE;
}



#endif /* */


static char path[512];

class FileHolder
{
public:
    FileHolder()
    {

        //++
#if defined(_WIN32)
        GetModuleFileName(NULL, path, sizeof(path));

        int i;

        for (i=strlen(path); i>0; i--)
        {
            if (path[i] == '\\' || path[i] == '/')
            {
                path[i] = '\0';
                break;
            }
        }

        strcat(path, "\\DEBUG.OUT");
#else /* UNIX */
        sprintf(path, "DEBUG.OUT");
#endif


        pf = fopen(path, "w");
    }

    ~FileHolder()
    {
        fclose(pf);
    }

    static void reset()
    {
        if (pf) fclose(pf);
        pf = fopen(path, "w");
    }
public:
    static FILE * pf;
};

FILE * FileHolder::pf = 0;

FileHolder fh;

extern "C" {

void w2printf(const char *format, ...)
{
    char    buf[4096], *p = buf;
    va_list args;
    int     n;

    va_start(args, format);
    n = vsnprintf(p, sizeof(buf) - 3, format, args); // buf-3 is room for CR/LF/NUL
    va_end(args);

    p += (n < 0) ? sizeof buf - 3 : n;

    //while ( p > buf  &&  isspace(p[-1]) )
    //    *--p = '\0';

    //   *p++ = '\r';
    //if(strcmp(format, "\n") == 0 )
    //{
    //    *p++ = '\n';
    //    *p   = '\0';
    //}

    fprintf(FileHolder::pf, buf);
    fflush(FileHolder::pf);
}

void write2file(const char *format, ...)
{
    char    buf[4096], *p = buf;
    va_list args;
    int     n;

    va_start(args, format);
    n = vsnprintf(p, sizeof(buf) - 3, format, args); // buf-3 is room for CR/LF/NUL
    va_end(args);

    p += (n < 0) ? sizeof buf - 3 : n;

    //while ( p > buf  &&  isspace(p[-1]) )
    //    *--p = '\0';

 //   *p++ = '\r';
     *p++ = '\n';
     *p   = '\0';

    fprintf(FileHolder::pf, buf);
    fflush(FileHolder::pf);
}

void reset_debug()
{
    FileHolder::reset();
}

// CommandLineToArgv converts a command-line string to argc and
// argv similar to the ones in the standard main function.
// This is a specialized version coded specifically for rundll32
// and is not intended to be used in any other program.
char ** CommandLineToArgv(const char * lpCmdLine, int *lpArgc)
{
    char **argv;
    char * lpSrc;
    char * lpDest;
    char * lpArg;
    int argc, nBSlash, nNames;
    BOOL bInQuotes, bFirstChar;

    // If null was passed in for lpCmdLine, there are no arguments
    if (!lpCmdLine)
    {
        if (lpArgc)
        {
            *lpArgc = 0;
        }
        return 0;
    }

    lpSrc = (char *)lpCmdLine;
    // Skip spaces at beginning
    while (*lpSrc == ' ' || *lpSrc == '\t')
    {
        lpSrc++;
    }

    // If command-line starts with null, there are no arguments
    if (*lpSrc == 0)
    {
        if (lpArgc)
        {
            *lpArgc = 0;
        }
        return 0;
    }

    lpArg = lpSrc;
    argc = 0;
    nBSlash = 0;
    bInQuotes = FALSE;
    bFirstChar = TRUE;
    nNames = 0;

    // Count the number of arguments
    while (nNames < 4)
    {
        if (*lpSrc == 0 || (*lpSrc == ',' && nNames == 2)
                || ((*lpSrc == ' ' || *lpSrc == '\t') && !bInQuotes))
        {
            // Whitespace not enclosed in quotes signals the start of another argument

            argc++;

            // Skip whitespace between arguments
            while (*lpSrc == ' ' || *lpSrc == '\t' || (*lpSrc == ',' && nNames == 2))
                lpSrc++;
            if (*lpSrc == 0)
                break;
            if (nNames >= 3)
            {
                // Increment the count for the last argument
                argc++;
                break;
            }
            nBSlash = 0;
            bFirstChar = TRUE;
            continue;
        }
        else if (*lpSrc == '\\')
        {
            // Count consecutive backslashes
            nBSlash++;
            bFirstChar = FALSE;
        }
        else if (*lpSrc == '\"' && !(nBSlash & 1))
        {
            // Open or close quotes
            bInQuotes = !bInQuotes;
            nBSlash = 0;
        }
        else
        {
            // Some other character
            nBSlash = 0;
            if (bFirstChar && ((*lpSrc != '/' && nNames <= 1) || nNames > 1))
                nNames++;
            bFirstChar = FALSE;
        }
        lpSrc++;
    }

    // Allocate space for the pointers in argv and the strings in one block
    argv = (char **)malloc(argc * sizeof(char *) + (strlen(lpArg) + 1) * sizeof
            (char));

    if (!argv)
    {
        // Memory allocation failed
        if (lpArgc)
            *lpArgc = 0;
        return 0;
    }

    lpSrc = lpArg;
    lpDest = lpArg = (char *)(argv + argc);
    argc = 0;
    nBSlash = 0;
    bInQuotes = FALSE;
    bFirstChar = TRUE;
    nNames = 0;

    // Fill the argument array
    while (nNames < 4)
    {
        if (*lpSrc == 0 || (*lpSrc == ',' && nNames == 2) || ((*lpSrc ==
                        ' ' || *lpSrc == '\t') && !bInQuotes))
        {
            // Whitespace not enclosed in quotes signals the start of another argument

            // Null-terminate argument
            *lpDest++ = 0;
            argv[argc++] = lpArg;

            // Skip whitespace between arguments
            while (*lpSrc == ' ' || *lpSrc == '\t' || (*lpSrc == ',' && nNames == 2))
                lpSrc++;
            if (*lpSrc == 0)
                break;
            lpArg = lpDest;
            if (nNames >= 3)
            {
                // Copy the rest of the command-line to the last argument
                argv[argc++] = lpArg;
                strcpy(lpArg,lpSrc);
                break;
            }
            nBSlash = 0;
            bFirstChar = TRUE;
            continue;
        }
        else if (*lpSrc == '\\')
        {
            *lpDest++ = '\\';
            lpSrc++;

            // Count consecutive backslashes
            nBSlash++;
            bFirstChar = FALSE;
        }
        else if (*lpSrc == '\"')
        {
            if (!(nBSlash & 1))
            {
                // If an even number of backslashes are before the quotes,
                // the quotes don't go in the output
                lpDest -= nBSlash / 2;
                bInQuotes = !bInQuotes;
            }
            else
            {
                // If an odd number of backslashes are before the quotes,
                // output a quote
                lpDest -= (nBSlash + 1) / 2;
                *lpDest++ = '\"';
                bFirstChar = FALSE;
            }
            lpSrc++;
            nBSlash = 0;
        }
        else
        {
            // Copy other characters
            if (bFirstChar && ((*lpSrc != '/' && nNames <= 1) || nNames > 1))
                nNames++;
            *lpDest++ = *lpSrc++;
            nBSlash = 0;
            bFirstChar = FALSE;
        }
    }

    if (lpArgc)
        *lpArgc = argc;
    return argv;
}

}

