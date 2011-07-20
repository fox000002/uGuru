#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#endif /* _WIN32 */

#include "tinyxml.h"

#include "global.h"

#include "node.h"

extern "C" {

int node_from_string(const char * str, XNodePtr p)
{
    if (NULL == str)
    {
        LOG_STRING("Passing NULL to node_from_string");
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

    if (strcmp(root->Value(), "Nodes") != 0)
    {
        LOG_STRING("Element Solvers is expected, but find : %s", root->Value());
        return -1;
    }

    for (TiXmlElement *node=root->FirstChildElement(); node;
        node = node->NextSiblingElement())
    {
        strcpy(p->ip, node->FirstChildElement("ip")->FirstChild()->Value());
        p->port = atoi(node->FirstChildElement("port")->FirstChild()->Value());
        strcpy(p->name, node->FirstChildElement("name")->FirstChild()->Value());
    }

    return 0;
}


const char * node_to_string(XNodePtr p, char * str)
{
    if (str == NULL  || p == NULL)
    {
        LOG_STRING("Passing NULL to node_to_string");
        return 0;
    }

    sprintf(str, "<Nodes>"
        "<Node>"
        "<ip>%s</ip>"
        "<port>%d</port>"
        "<name>%s</name>"
        "</node>"
        "</Nodes>",
        p->ip, p->port, p->name);

    return 0;
}

}
