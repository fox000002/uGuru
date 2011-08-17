#include "download.h"

#if defined(_WIN32)

#include <windows.h>
#include <tchar.h>

#include <stdio.h>

#ifndef _MSC_VER

#define __out_ecount(size)
#define __out_ecount_full_opt(size)
#define __in_ecount(size)

#define __in
#define __out
#define __inout

#include "winhttp.h"

#endif // _MSC_VER

#include "global.h"



int download_http_file(const char * host, unsigned int port, const char *rfile, const char *lfile)
{
    WCHAR host_wc[512];
    WCHAR rfile_wc[512];

    DWORD data;
    DWORD dwSize = sizeof(DWORD);
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;
    HINTERNET  hSession = NULL;
    HINTERNET  hConnect = NULL;
    HINTERNET  hRequest = NULL;

    FILE * pfOut;

    //
    mbstowcs(host_wc, host, 512);
    mbstowcs(rfile_wc, rfile, 512);


    // Use WinHttpOpen to obtain an HINTERNET handle.
    hSession = WinHttpOpen(
        L"uGuru Service Kit/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    if (!hSession)
    {
        LOG_STRING( "Error %u in WinHttpOpen.\n", GetLastError());
        return -1;
    }


    // Use WinHttpQueryOption to retrieve internet options.
    if (WinHttpQueryOption( hSession,
            WINHTTP_OPTION_CONNECT_TIMEOUT,
            &data, &dwSize))
    {
        LOG_STRING("Connection timeout: %u ms\n\n",data);
    }
    else
    {
        LOG_STRING( "Error %u in WinHttpQueryOption.\n", GetLastError());
        return -1;
    }

    // When finished, release the HINTERNET handle.
    WinHttpCloseHandle(hSession);


    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen( L"uGuru Service Kit/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0 );

    // Specify an HTTP server.
    if( !hSession )
    {
        LOG_STRING( "Error %u in WinHttpOpen.\n", GetLastError());
        return -1;
    }

    hConnect = WinHttpConnect( hSession,
            host_wc,
            port,
            0 );

    // Create an HTTP request handle.
    if( !hConnect )
    {
        LOG_STRING( "Error %u in WinHttpConnect.\n", GetLastError());
        return -1;
    }


    hRequest = WinHttpOpenRequest( hConnect,
            L"GET",
            rfile_wc,
            NULL,
            WINHTTP_NO_REFERER,
            NULL,
            0 );

    // Send a request.
    if( !hRequest )
    {
        LOG_STRING( "Error %u in WinHttpConnect.\n", GetLastError());
        return -1;
    }

    bResults = WinHttpSendRequest( hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0,
            WINHTTP_NO_REQUEST_DATA,
            0,
            0,
            0);


    // End the request.
    if( !bResults )
    {
        LOG_STRING( "Error %u in WinHttpSendRequest.\n", GetLastError());
        return -1;
    }

    bResults = WinHttpReceiveResponse( hRequest, NULL );

       // Report any errors.
    if( !bResults )
    {
        LOG_STRING( "Error %d has occurred.\n", GetLastError());
        return -1;
    }


    pfOut = fopen(lfile, "w+b");
    // Keep checking for data until there is nothing left.
    do
    {
         // Check for available data.
         dwSize = 0;
         if( !WinHttpQueryDataAvailable( hRequest, &dwSize ) )
         {
             LOG_STRING( "Error %u in WinHttpQueryDataAvailable.\n",
                    GetLastError( ) );
            return -1;
         }

         // Allocate space for the buffer.
         pszOutBuffer = (char *)malloc((dwSize+1)*sizeof(char));
         if( !pszOutBuffer )
         {
            LOG_STRING( "Out of memory\n" );
            dwSize=0;
         }
         else
         {
             // Read the data.
             ZeroMemory( pszOutBuffer, dwSize+1 );

             if( !WinHttpReadData( hRequest, (LPVOID)pszOutBuffer,
                        dwSize, &dwDownloaded ) )
             {
                 LOG_STRING( "Error %u in WinHttpReadData.\n", GetLastError( ) );
                return -1;
             }

             //printf( "%s", pszOutBuffer );
            fwrite(pszOutBuffer, 1, dwDownloaded, pfOut);

          }

            // Free the memory allocated to the buffer.
          free(pszOutBuffer);
    } while( dwSize > 0 );

    fclose(pfOut);



    // Close any open handles.
    if( hRequest ) WinHttpCloseHandle( hRequest );
    if( hConnect ) WinHttpCloseHandle( hConnect );
    if( hSession ) WinHttpCloseHandle( hSession );

    return 0;
}

#else


int download_http_file(const char * host, unsigned int port, const char *rfile, const char *lfile)
{

}

#endif

