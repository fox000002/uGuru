#include <windows.h>
#include <tchar.h>

#include "tinyxml.h"

#include "mongoose.h"

#include "global.h"

#include "config.h"

#include "solver.h"

extern "C" {

char document_root[512];

void my_set_option(const char *name, const char* value);

int load_config(const char *fn)
{

    TiXmlDocument doc(fn);

    if (doc.LoadFile())
    {
        TiXmlElement * root = doc.RootElement();

        LOG_STRING("Root Element : %s", root->Value());

        if (strcmp(root->Value(), "Configuration") != 0)
        {
            LOG_STRING("Expected 'Configuration' but find", root->Value());

            return 1;
        }

        TiXmlElement * server = root->FirstChildElement("Server");

        if (server == 0)
        {
            LOG_STRING("Cannot find Element : Server");

            return 2;
        }

        TiXmlElement * port = server->FirstChildElement("port");
        
        if (port == 0)
        {
            LOG_STRING("Cannot find Element : port");

            return 2;
        }
        
        my_set_option("listening_ports", port->FirstChild()->Value());


        TiXmlElement * doc_root = server->FirstChildElement("document_root");

        if (doc_root == 0)
        {
            LOG_STRING("Cannot find Element : document_root");

            return 2;
        }

        //SetCurrentDirectory(doc_root->FirstChild()->Value());
        sprintf(document_root, "%s", doc_root->FirstChild()->Value());

        my_set_option("document_root", doc_root->FirstChild()->Value());

        TiXmlElement * solvers = root->FirstChildElement("Solvers");

        if (solvers == 0)
        {
            LOG_STRING("Cannot find Element : Solvers");

            return 2;
        }
        
        char spath[512];
        
        sprintf(spath, "%s\\solver.xml", document_root);
        
        init_solvers(spath);

        return 0;
    }
    else
    {
        LOG_STRING("Error load XML file : %s", fn);

        return -1;
    }
}

}
