//#include <windows.h>
#include <queue>
#include <vector>
#include <string>

#include "tinyxml.h"

#include "global.h"

#include "config.h"

#include "solver.h"

#include "taskman.h"


#include "download.h"

#include "mongoose.h"

typedef std::queue<TaskPtr> TaskQueue;
typedef std::vector<TaskPtr> TaskArray;
typedef std::string UString;

static TaskQueue qu;

static TaskArray qu_back;
static TaskArray tasklist;

#ifdef __cplusplus
extern "C" {
#endif

enum TaskQueueState g_tqs = TQS_EMPTY;

int g_flag_abort = 0;

int add_to_queue(TaskPtr t)
{
    if (is_task_already_exist(t))
    {
        LOG_STRING("Task %d duplicated!!", t->id);
        return -1;
    }

    qu.push(t);
    tasklist.push_back(t);
    return 0;
}

TaskPtr serve_queue()
{
    TaskPtr t = qu.front();

    LOG_STRING("task %d", t->id);
    
    g_tqs = TQS_BUSY;
    
    if (run_task(t)) // Failed
    {
        LOG_STRING("task %d failed", t->id);
        return 0;
    }

    qu.pop();
    qu_back.push_back(t);
    
    if (qu.empty())
    {
        g_tqs = TQS_FINISHED;
    }
    
    return t;
}

void cleanup_task()
{
    TaskPtr t;

    while(!qu.empty())
    {
        t=qu.front();
        qu.pop();
        delete t;
    }

    TaskArray::iterator it = qu_back.begin();

    for(; it != qu_back.end(); ++it)
    {
        t= *it;
        delete t;
    }
    qu_back.clear();

    tasklist.clear();
}


static void callback(void * data)
{
    if (data == NULL)
    {
        return;
    }

//    TaskPtr t = (TaskPtr)data;

//    t->ts = TS_ABORT;

}

int run_task( TaskPtr t )
{
    if (t == NULL)
    {
        return -1;
    }

    char cmdline[512];

    SolverPtr s = solver_from_id(t->sid);

    if (NULL == s)
    {
        LOG_STRING("Error find solver %d", t->sid);
    
        return -2;
    }
    
    sprintf(cmdline, "%s\\solvers\\%s %s\\%s\\%s", document_root, s->command,
        document_root, t->subdir, s->arg);

    t->ts = TS_RUNNING;

    char wdir[512];
    
    sprintf(wdir, "%s\\%s", document_root, t->subdir);
    
    LOG_STRING("StartProgram %s", cmdline);
    
    if (!startProgramCallbackParam(cmdline, wdir, TRUE, &callback, t))
    {
        t->ts = TS_ABORT;
        return -1;
    }

    t->ts = TS_FINISHED;

    return 0;
}

int is_no_task()
{
    if (0 == qu.size())
    {
        return 1;
    }
    return 0;
}


int is_task_processing()
{
    if (0 == qu.size())
    {
        return 0;
    }

    if (TS_RUNNING == qu.front()->ts)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_task_already_exist(TaskPtr t)
{
    TaskArray::iterator it = tasklist.begin();

    for(; it != tasklist.end(); ++it)
    {
        TaskPtr p = *it;

        if (t->id == p->id)
        {
            return 1;
        }
    }
    return 0;
}


//+From mongoose
static int parse_url(const char *url, char *host, int *port)
{
    sscanf(url, "%[0-9.]:%d", host, port);

    return 0;
}
//
//
int tasks_from_string( const char * buffer )
{

    if (NULL == buffer)
    {
        LOG_STRING("Passing NULL to tasks_from_string");
        return -1;
    }

    TiXmlDocument xdoc;


    if (NULL == xdoc.Parse(buffer))
    {
        LOG_STRING("Failed to parse XML: %s", buffer);
        return -2;
    }

    TiXmlElement * root = xdoc.RootElement();

    if (0 == root)
    {
        LOG_STRING("Failed to find XML root in tasks_from_string");
        return -2;
    }

    if (strcmp(root->Value(), "Tasks") != 0)
    {
        LOG_STRING("Element Tasks is expected, but find : %s", root->Value());
        return -1;
    }

    for (TiXmlElement *task=root->FirstChildElement(); task;
        task = task->NextSiblingElement())
    {
        TaskPtr p = new Task();
        char url[512];


        if (NULL != task->Attribute("from"))
        {
            strcpy(url, task->Attribute("from"));

            LOG_STRING("Before Parsing");

            if (parse_url(url, p->from.ip, & p->from.port))
            {
                LOG_STRING("Failed to parse url : %s", url);
            }

            LOG_STRING("Get %s : %d", p->from.ip, p->from.port);
        }



        p->id = atoi(task->FirstChildElement("id")->FirstChild()->Value());
        strcpy(p->name, task->FirstChildElement("name")->FirstChild()->Value());
        p->sid = atoi(task->FirstChildElement("sid")->FirstChild()->Value());
        strcpy(p->subdir, task->FirstChildElement("subdir")->FirstChild()->Value());


        add_to_queue(p);
    }
    
    if (is_no_task())
    {
        return -3;
    }

    // Update TaskQueue status code
    g_tqs = TQS_PENDING;

    return 0;
}

//
static const char * TaskStateText[] = {
	"TS_UNDEFINED",
	"TS_PENDING",
	"TS_READY",
	"TS_RUNNING",
    "TS_FINISHED",
    "TS_ABORT"
};
//
//
//
int front_task_to_string(char * buffer)
{
    if (NULL == buffer)
    {
        return -1;
    }

    if (qu.empty())
    {
        return -2;
    }
    
    TaskPtr p = qu.front();

    if (p == NULL)
    {
        return -3;
    }

    int s = (int)p->ts;

    sprintf(buffer, "<Tasks>"
        "<task>"
        "<id>%d</id>"
        "<name>%s</name>"
        "<sid>%d</sid>"
        "<subdir>%s</subdir>"
        "<status>%s</status>"
        "</task>"
        "</Tasks>",
        p->id, p->name, p->sid, p->subdir, TaskStateText[s]);

    return 0;
}

int all_tasks_to_string( char *buffer )
{
    if (NULL == buffer)
    {
        LOG_STRING("Passing NULL to all_tasks_to_string!!");
        return -1;
    }

    if (tasklist.empty())
    {
        LOG_STRING("Tasklist is empty!!");
        return -2;
    }

    UString tmp = "";
    char buf[1024];
    TaskPtr p;
    int s = 0;
    TaskArray::iterator it = tasklist.begin();

    tmp += "<Tasks>";
    for(; it != tasklist.end(); ++it)
    {
        p= *it;

        s = (int)p->ts;

        sprintf(buf,
            "<task>"
            "<id>%d</id>"
            "<name>%s</name>"
            "<sid>%d</sid>"
            "<subdir>%s</subdir>"
            "<status>%s</status>"
            "</task>",
            p->id, p->name, p->sid, p->subdir, TaskStateText[s]);
        tmp += buf;
    }
    tmp += "</Tasks>";

    sprintf(buffer, "%s", tmp.c_str());

    return 0;
}

int stop_all_job()
{
    if (is_no_task())
    {
        LOG_STRING("No task in queue to stop.");
        return -1;
    }

    g_tqs = TQS_ABORT;

    return 0;
}

int download_task_files( TaskPtr t )
{
    if (NULL == t)
    {
        LOG_STRING("Passing NULL to download_task_files");
        return -1;
    }

    if (strlen(t->from.ip) || t->from.port == 0)
    {
        LOG_STRING("IP or Port in Task is missing!");
        return -1;
    }

    char rpath[512];
    char lpath[512];

    sprintf(rpath, "/%s/WF.inp", t->subdir);
    sprintf(lpath, "%s/%s/WF.inp", document_root, t->subdir);

    if (download_http_file(t->from.ip, (unsigned int)t->from.port, rpath, lpath))
    {
        LOG_STRING("Download file failed : %s from %s:%s", rpath, t->from.ip, t->from.port);
        return -1;
    }

    sprintf(rpath, "/%s/variable.dat", t->subdir);
    sprintf(lpath, "%s/%s/variable.dat", document_root, t->subdir);

    if (download_http_file(t->from.ip, (unsigned int)t->from.port, rpath, lpath))
    {
        LOG_STRING("Download file failed : %s from %s:%s", rpath, t->from.ip, t->from.port);
        return -1;
    }

    sprintf(rpath, "/%s/input.ini", t->subdir);
    sprintf(lpath, "%s/%s/input.ini", document_root, t->subdir);

    if (download_http_file(t->from.ip, (unsigned int)t->from.port, rpath, lpath))
    {
        LOG_STRING("Download file failed : %s from %s:%s", rpath, t->from.ip, t->from.port);
        return -1;
    }

    return 0;
}

#if defined(_WIN32)
int mg_mkdir(const char *path, int mode);
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <dirent.h>
#define mg_mkdir(x,y) mkdir(x,y)
#endif

int prepare_files_taskqueue()
{
    if (is_no_task())
    {
        LOG_STRING("No task in the task queue.");
        return -1;
    }

    TaskArray::iterator it = tasklist.begin();
    TaskPtr p = NULL;
    
    
    for(; it != tasklist.end(); ++it)
    {
        p= *it;
    
        //if (0 != download_task_files(p))
        //{
        //    return -2;
        //}
        char lpath[512];

        sprintf(lpath, "%s\\%s", document_root, p->subdir);
        
        //::CreateDirectory(lpath, NULL);
        mg_mkdir(lpath, 0);
        
    }
    
    //
    g_tqs = TQS_READY;
    
    return 0;
}


}
