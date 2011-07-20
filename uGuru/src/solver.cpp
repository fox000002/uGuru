#include <windows.h>
#include <tchar.h>
#include <map>

#include "tinyxml.h"

#include "global.h"

#include "solver.h"

typedef std::map<int, SolverPtr> SolverTable;

static SolverTable solvers;

extern "C" {

int solver_from_string( const char *str, SolverPtr s )
{
    if (NULL == str || NULL == s)
    {
        LOG_STRING("Passing NULL to solver_from_string");
        return -1;
    }

    TiXmlDocument xdoc;

    if (NULL == xdoc.Parse(str))
    {
        LOG_STRING("Failed to parse XML: %s", str);
        return -2;
    }

    TiXmlElement * root = xdoc.RootElement();

    if (0 == root)
    {
        LOG_STRING("Failed to find XML root in solver_from_string");
        return -2;
    }

    if (strcmp(root->Value(), "Solvers") != 0)
    {
        LOG_STRING("Element Solvers is expected, but find : %s", root->Value());
        return -1;
    }

    for (TiXmlElement *solver=root->FirstChildElement(); solver;
        solver = solver->NextSiblingElement())
    {
        s->id = atoi(solver->FirstChildElement("id")->FirstChild()->Value());
        strcpy(s->name, solver->FirstChildElement("name")->FirstChild()->Value());
        strcpy(s->command, solver->FirstChildElement("command")->FirstChild()->Value());
        strcpy(s->arg, solver->FirstChildElement("arg")->FirstChild()->Value());
    }

    return 0;
}

const char * solver_to_string( const struct Solver *s, char *str )
{
    if (NULL == str || NULL == s)
    {
        LOG_STRING("Passing NULL to solver_to_string");
        return NULL;
    }

    sprintf(str, "<Solvers>"
        "<solver>"
        "<id>%d</id>"
        "<name>%s</name>"
        "<command>%s</command>"
        "<arg>%s</arg>"
        "</solver>"
        "</Solvers>",
        s->id, s->name, s->command, s->arg);


    return str;
}

struct Solver * solver_from_id( int id )
{
    return solvers[id];
}


int init_solvers( const char * fn )
{
    TiXmlDocument xDoc(fn);
    xDoc.LoadFile();

    TiXmlElement * root = xDoc.RootElement();

    if (0 == root)
    {
        LOG_STRING("Failed to find XML root in %s", fn);
        return -2;
    }

    if (strcmp(root->Value(), "Solvers") != 0)
    {
        LOG_STRING("Element Solvers is expected, but find : %s", root->Value());
        return -1;
    }


    for (TiXmlElement *solver=root->FirstChildElement(); solver;
        solver = solver->NextSiblingElement())
    {
        SolverPtr p = new Solver();

        p->id = atoi(solver->FirstChildElement("id")->FirstChild()->Value());
        strcpy(p->name, solver->FirstChildElement("name")->FirstChild()->Value());

        strcpy(p->command, solver->FirstChildElement("command")->FirstChild()->Value());
        strcpy(p->arg, solver->FirstChildElement("command")->FirstAttribute()->Value());

        solvers[p->id] = p;
     }

     return 0;
}

void clear_solvers()
{
    SolverTable::iterator it = solvers.begin();

    for (; it!=solvers.end(); ++it)
    {
        delete it->second;
    }

    solvers.clear();
}

}
