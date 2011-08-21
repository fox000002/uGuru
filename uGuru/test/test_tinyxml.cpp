#include <stdio.h>

#include "tinyxml.h"

int main()
{
    TiXmlDocument xdoc;

    const char * p = xdoc.Parse("<X><Tasks>333</Tasks></X>\n");

    TiXmlElement * root = xdoc.RootElement();


    printf("Element Tasks is expected. Find : %s\n", root->Value());

    printf("P : %p\n", p);

    return 0;
}
