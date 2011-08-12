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

#include "tinyxml.h"

#include "sysinfo.h"

#include "download.h"

#include "taskman.h"

extern "C" {

static const char *standard_reply = "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Connection: close\r\n\r\n";

static const char *standard_xml_reply = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/xml\r\n"
"Connection: close\r\n\r\n";

static const char *standard_html_reply = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html\r\n"
"Connection: close\r\n\r\n";


void show_homepage(struct mg_connection *conn, const struct mg_request_info *ri)
{
    mg_printf(conn, standard_html_reply);

    mg_printf(conn, "<html><head><title>uGuru Serivce</title></head>"
        "<body>"
        "<a href=\"/server_info\">server infomation</a><br/>"
        "<a href=\"/server_state\">server state</a><br/>"
        "<a href=\"/submit\">submit task</a><br/>"
        "<a href=\"/prepare\">prepare files</a><br/>"
        "<a href=\"/start\">start task processing</a><br/>"
        "<a href=\"/query\">query task</a><br/>"
        "<a href=\"/terminate\">terminate</a><br/>"
        "</body></html>");

    UNREFERENCED_PARAMETER(ri)
}

void fetch_server_info(struct mg_connection *conn,
    const struct mg_request_info *ri)
{

    mg_printf(conn, "%s", standard_xml_reply);
    mg_printf(conn,
        "<uGuru>"
        "<sysinfo>"
        "<cpu_number>%d</cpu_number>"
        "</sysinfo>"
        "</uGuru>",
        cpu_num());

    UNREFERENCED_PARAMETER(ri)
}

void fetch_server_state(struct mg_connection *conn,
    const struct mg_request_info *ri)
{
    //const char * doc_root = mg_get_option(conn->ctx, "document_root");

    //char tmp[MAX_PATH];

    //sprintf(tmp, "%s/server.xml", doc_root);
    //TiXmlDocument doc(tmp);

    //sprintf(tmp, "%s/solver.xml", doc_root);
    //TiXmlDocument cfg(tmp);

    TiXmlDocument doc("server.xml");
    TiXmlDocument cfg("solver.xml");

    TiXmlPrinter printer;
    printer.SetIndent( "\t" );

    TiXmlPrinter printer2;
    printer2.SetIndent( "\t" );

    //fprintf( stdout, "%s", printer.CStr() );

    //printer.Visit(doc.RootElement());

    if (cfg.LoadFile() && doc.LoadFile())
    {
        doc.Accept( &printer );
        cfg.Accept( &printer2 );

        mg_printf(conn, "%s", standard_xml_reply);
        mg_printf(conn, "<uGuru>"
            "%s"
            "%s"
            "</uGuru>",
            printer.CStr(),
            printer2.CStr());
    }
    else
    {
        mg_printf(conn, "%s", standard_xml_reply);
        mg_printf(conn, "<uGuru>"
            "<msg>Failed to load xml file</msg>"
            "</uGuru>");
    }

    UNREFERENCED_PARAMETER(ri)
}

void query_running_data(struct mg_connection *conn,
    const struct mg_request_info *ri)
{
    switch (g_tqs)
    {
    case TQS_EMPTY:
        {
            mg_printf(conn, "%s", standard_xml_reply);
            mg_printf(conn, "<uGuru>"
                "<qstatus>%d</qstatus>"
                "<error>No Running Task</error>"
                "</uGuru>",
                g_tqs);
            return;
        }
    case TQS_PENDING:
        {
            mg_printf(conn, "%s", standard_xml_reply);
            mg_printf(conn,
                "<uGuru>"
                "<qstatus>%d</qstatus>"
                "<msg>Task files are missing</msg>"
                "</uGuru>",
                g_tqs);

            return;
        }
    case TQS_READY:
        {
            mg_printf(conn, "%s", standard_xml_reply);
            mg_printf(conn,
                "<uGuru>"
                "<qstatus>%d</qstatus>"
                "<msg>TaskQueue is ready to start</msg>"
                "</uGuru>",
                g_tqs);

            return;
        }
    case TQS_BUSY:
        {
            char buffer[1024];

            mg_printf(conn, "%s", standard_xml_reply);
            mg_printf(conn, "<uGuru>");
            mg_printf(conn, "<qstatus>%d</qstatus>", g_tqs);
            if (!front_task_to_string(buffer))
            {
                mg_printf(conn, buffer);
            }
            else
            {
                mg_printf(conn, "<error>Failed to convert task to XML. Check DEBUG.LOG please!</error>");
            }

            mg_printf(conn, "</uGuru>");

            return;
        }
    case TQS_FINISHED:
        {
            char buffer[2024];

            if (all_tasks_to_string(buffer))
            {
                mg_printf(conn, "%s", standard_xml_reply);
                mg_printf(conn,
                    "<uGuru>"
                    "<qstatus>%d</qstatus>"
                    "<error>Failed to convert task to XML. Check DEBUG.LOG please!</error>"
                    "</uGuru>",
                    g_tqs);
                return;
            }

            // Node is idle
            mg_printf(conn, "%s", standard_xml_reply);
            mg_printf(conn, "<uGuru>"
                "<qstatus>%d</qstatus>"
                "%s"
                "</uGuru>", g_tqs, buffer);
        }
    case  TQS_ABORT:
        {
            mg_printf(conn, "%s", standard_xml_reply);
            mg_printf(conn,
                "<uGuru>"
                "<qstatus>%d</qstatus>"
                "<error>TaskQueue is aborted.</error>"
                "</uGuru>",
                g_tqs);

            return;
        }
    default:
        {
            mg_printf(conn, "%s", standard_xml_reply);
            mg_printf(conn,
                "<uGuru>"
                "<qstatus>%d</qstatus>"
                "<msg>Unknown status</msg>"
                "</uGuru>",
                g_tqs);

            return;
        }
    }

    UNREFERENCED_PARAMETER(ri)
}

void force_terminate(struct mg_connection *conn,
    const struct mg_request_info *ri)
{
    if (stop_all_job())
    {
        mg_printf(conn, "%s", standard_xml_reply);
        mg_printf(conn,
            "<uGuru>"
            "<qstatus>%d</qstatus>"
            "<error>Teminating tasks failed</error>"
            "</uGuru>",
            g_tqs);
        return;
    }

    mg_printf(conn, "%s", standard_xml_reply);
    mg_printf(conn,
        "<uGuru>"
        "<qstatus>%d</qstatus>"
        "<response>OK</response>"
        "</uGuru>",
        g_tqs);

    UNREFERENCED_PARAMETER(ri)
}

void download_file(struct mg_connection *conn, const struct mg_request_info *ri)
{
    if (download_http_file("127.0.0.1", 8080, "/config.xml", "download.dat"))
    {
        mg_printf(conn, "%s", standard_xml_reply);
        mg_printf(conn,
            "<uGuru>"
            "<error>Download Failed</error>"
            "</uGuru>");
        return;
    }


    mg_printf(conn, "%s", standard_xml_reply);
    mg_printf(conn,
        "<uGuru>"
        "<qstatus>%d</qstatus>"
        "</uGuru>",
        g_tqs);

    UNREFERENCED_PARAMETER(ri)
}

void prepare_files(struct mg_connection *conn, const struct mg_request_info *ri)
{
    if (g_tqs == TQS_PENDING)
    {
        prepare_files_taskqueue();
    }

        mg_printf(conn, "%s", standard_xml_reply);
        mg_printf(conn,
          "<uGuru>"
          "<qstatus>%d</qstatus>"
          "</uGuru>",
          g_tqs);



    UNREFERENCED_PARAMETER(ri)
}

void debug_info( struct mg_connection *conn, const struct mg_request_info *ri )
{
    FILE * pfDebug = fopen("DEBUG.OUT", "r");
    char buffer[1024];
    if (!pfDebug)
    {
        mg_printf(conn, "%s", standard_xml_reply);
        mg_printf(conn,
            "<uGuru>"
            "<error>Failed to open file DEBUG.OUT</error>"
            "</uGuru>");

        return;
    }

    mg_printf(conn, "%s", standard_reply);

    while (fgets(buffer, 1024, pfDebug))
    {
        mg_printf(conn,"%s", buffer);
    }

    fclose(pfDebug);

    UNREFERENCED_PARAMETER(ri);
}

}

