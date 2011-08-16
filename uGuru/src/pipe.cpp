#include <stdio.h>
#include <stdlib.h>

#include "mongoose.h"

#include "pipe.h"

int redirect_io()
{
	/* Variables 
	in=UserINPUT */ 
	char * in = (char *)malloc( 20 * sizeof( char ) );
	
	/* Setup the streams */
	/*freopen( "stdin.log", "w", stdin ); This messes up fgets :( */ 
	freopen( "stderr.log", "w", stderr );
	freopen( "stdout.log", "w", stdout );
	
	/* Send the streams some text */ 
	fprintf( stdout, "This is stdout\n" ); 
	fprintf( stderr, "This is stderr\n" );
	/*fprintf( stdin, "This should not work" ); This messes up fgets :( */ 
	
	/* Send stdin some good ol' user text */ 
	fgets( in, 20, stdin );
	
	/* Echo out user input */ 
	puts( in );
    
    /* */
    free(in);
	
	/* Return success */ 
	return 0;
}

#if defined(_WIN32)  // Windows specific #includes and #defines
#define _WIN32_WINNT 0x0400 // To make it link in VS2005
#include <windows.h>

#define BUFSIZE 4096 

HANDLE hChildStdoutRd, hChildStdoutWr,hStdout;

BOOL CreateChildProcess(VOID);
VOID ReadFromPipe(struct mg_connection *conn); 
VOID ErrorExit(LPCSTR); 

int mypipe(struct mg_connection *conn) 
{ 
    SECURITY_ATTRIBUTES saAttr; 
    BOOL fSuccess; 

    // Set the bInheritHandle flag so pipe handles are inherited. 

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
    saAttr.bInheritHandle = TRUE; 
    saAttr.lpSecurityDescriptor = NULL; 

    // Get the handle to the current STDOUT. 

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

    // Create a pipe for the child process's STDOUT. 

    if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0)) 
        ErrorExit("Stdout pipe creation failed\n"); 

    // Ensure the read handle to the pipe for STDOUT is not inherited.
    SetHandleInformation( hChildStdoutRd, HANDLE_FLAG_INHERIT, 0);


    // Now create the child process. 

    fSuccess = CreateChildProcess();
    if (! fSuccess) 
        ErrorExit("Create process failed with"); 


    // Read from pipe that is the standard output for child process. 

    ReadFromPipe(conn); 

    return 0; 
} 

BOOL CreateChildProcess() 
{ 
    TCHAR szCmdline[]=TEXT("hello.bat");
    PROCESS_INFORMATION piProcInfo; 
    STARTUPINFO siStartInfo;
    BOOL bFuncRetn = FALSE; 

    // Set up members of the PROCESS_INFORMATION structure. 

    ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );

    // Set up members of the STARTUPINFO structure. 

    ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
    siStartInfo.cb = sizeof(STARTUPINFO); 
    siStartInfo.hStdError = hChildStdoutWr;
    siStartInfo.hStdOutput = hChildStdoutWr;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Create the child process. 

    bFuncRetn = CreateProcess(NULL, 
        szCmdline,     // command line 
        NULL,          // process security attributes 
        NULL,          // primary thread security attributes 
        TRUE,          // handles are inherited 
        0,             // creation flags 
        NULL,          // use parent's environment 
        NULL,          // use parent's current directory 
        &siStartInfo,  // STARTUPINFO pointer 
        &piProcInfo);  // receives PROCESS_INFORMATION 

    if (bFuncRetn == 0) 
        ErrorExit("CreateProcess failed\n");
    else 
    {
        CloseHandle(piProcInfo.hProcess);
        CloseHandle(piProcInfo.hThread);
        return bFuncRetn;
    }

    return FALSE;
}


VOID ReadFromPipe(struct mg_connection *conn) 
{ 
    DWORD dwRead, dwWritten; 
    CHAR chBuf[BUFSIZE]; 

    // Close the write end of the pipe before reading from the 
    // read end of the pipe. 

    if (!CloseHandle(hChildStdoutWr)) 
        ErrorExit("Closing handle failed"); 

    // Read output from the child process, and write to parent's STDOUT. 
    mg_printf(conn,"HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Connection: close\r\n\r\n");


    for (;;) 
    { 
        if( !ReadFile( hChildStdoutRd, chBuf, BUFSIZE, &dwRead, 
                NULL) || dwRead == 0) break; 

        mg_write(conn, chBuf, dwRead);

        if (! WriteFile(hStdout, chBuf, dwRead, &dwWritten, NULL)) 
            break;
        //mg_printf(conn, "%s", chBuf);
    } 
} 

VOID ErrorExit (LPCSTR lpszMessage) 
{ 
    fprintf(stderr, "%s\n", lpszMessage); 
    ExitProcess(0); 
}

#else // UNIX

#include <unistd.h>

int mypipe(struct mg_connection *conn)
{
    int	writepipe[2] = {-1,-1},	/* parent -> child */
    int  readpipe [2] = {-1,-1};	/* child -> parent */
    pid_t	childpid;
   

    return 0;
}

int start_pipe(char PROGRAM_B_INPUT[])
{
    int fd1[2];
    int fd2[2];
    int fd3[2];
    pid_t pid;
    char line[MAXLINE];

    if ( (pipe(fd1) < 0) || (pipe(fd2) < 0) || (pipe(fd3) < 0) )
    {
        cerr << "PIPE ERROR" << endl;
        return -2;
    }
    
    if ( (pid = fork()) < 0 )
    {
        cerr << "FORK ERROR" << endl;
        return -3;
    }
    else if (pid == 0)     // CHILD PROCESS
    {
        close(fd1[1]);
        close(fd2[0]);

        if (fd1[0] != STDIN_FILENO)
        {
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
            {
                cerr << "dup2 error to stdin" << endl;
            }
            close(fd1[0]);
        }

        if (fd2[1] != STDOUT_FILENO)
        {
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
                cerr << "dup2 error to stdout" << endl;
            }
            close(fd2[1]);
        }

        if ( execl("path/PROGRAM B", "PROGRAM B", (char *)0) < 0 )
        {
            cerr << "system error" << endl;
            return -4;
        }

        return 0;
    }
    else        // PARENT PROCESS
    {
        int rv;
        close(fd1[0]);
        close(fd2[1]);

        if ( write(fd1[1], PROGRAM_B_INPUT, strlen(PROGRAM_B_INPUT) ) != strlen(PROGRAM_B_INPUT) )
        {
            cerr << "READ ERROR FROM PIPE" << endl;
        }

        if ( (rv = read(fd2[0], line, MAXLINE)) < 0 )
        {
            cerr << "READ ERROR FROM PIPE" << endl;
        }
        else if (rv == 0)
        {
            cerr << "Child Closed Pipe" << endl;
            return 0;
        }

        cout << "OUTPUT of PROGRAM B is: " << line;

        return 0;
    }
    return 0;
}

#ifndef TRUE
#  define TRUE 1
#endif

#ifndef FALSE
#  define FALSE 0
#endif

/*------------------------------------------------------------------------
 * Every time we run a dup2(), we always close the old FD, so this macro
 * runs them both together and evaluates to TRUE if it all went OK and 
 * FALSE if not.
 */
#define	DUP2CLOSE(oldfd, newfd)	(dup2(oldfd, newfd) == 0  &&  close(oldfd) == 0)

int remap_pipe_stdin_stdout(int rpipe, int wpipe)
{
	/*------------------------------------------------------------------
	 * CASE [A]
	 *
	 * This is the trivial case that probably never happens: the two FDs
	 * are already in the right place and we have nothing to do. Though
	 * this probably doesn't happen much, it's guaranteed that *doing*
	 * any shufflingn would close descriptors that shouldn't have been.
	 */
	if ( rpipe == 0  &&  wpipe == 1 )
		return TRUE;

	/*----------------------------------------------------------------
	 * CASE [B] and [C]
	 *
	 * These two have the same handling but not the same rules. In case
	 * [C] where both FDs are "out of the way", it doesn't matter which
	 * of the FDs is closed first, but in case [B] it MUST be done in
	 * this order.
	 */
	if ( rpipe >= 1  &&  wpipe > 1 )
	{
		return DUP2CLOSE(rpipe, 0)
		    && DUP2CLOSE(wpipe, 1);
	}


	/*----------------------------------------------------------------
	 * CASE [D]
	 * CASE [E]
	 *
 	 * In these cases, *one* of the FDs is already correct and the other
	 * one can just be dup'd to the right place:
	 */
	if ( rpipe == 0  &&  wpipe >= 1 )
		return DUP2CLOSE(wpipe, 1);

	if ( rpipe  >= 1  &&  wpipe == 1 )
		return DUP2CLOSE(rpipe, 0);


	/*----------------------------------------------------------------
	 * CASE [F]
	 *
	 * Here we have the write pipe in the read slot, but the read FD
	 * is out of the way: this means we can do this in just two steps
	 * but they MUST be in this order.
	 */
	if ( rpipe >= 1   &&  wpipe == 0 )
	{
		return DUP2CLOSE(wpipe, 1)
		    && DUP2CLOSE(rpipe, 0);
	}

	/*----------------------------------------------------------------
	 * CASE [G]
	 *
	 * This is the trickiest case because the two file descriptors  are
	 * *backwards*, and the only way to make it right is to make a
	 * third temporary FD during the swap.
	 */
	if ( rpipe == 1  &&  wpipe == 0 )
	{
	const int tmp = dup(wpipe);		/* NOTE! this is not dup2() ! */

		return	tmp > 1
		    &&  close(wpipe)   == 0
		    &&  DUP2CLOSE(rpipe, 0)
		    &&  DUP2CLOSE(tmp,   1);
	}

	/* SHOULD NEVER GET HERE */

	return  FALSE;
}


#endif 