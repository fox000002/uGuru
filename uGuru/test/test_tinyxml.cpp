#include <stdio.h>

#include "tinyxml.h"

int main()
{
	TiXmlDocument xdoc;
	
	const char *p = xdoc.Parse("<Tasks>333</Tasks>");
	
	TiXmlElement * root = xdoc.RootElement();


    printf("Element Tasks is expected, but find : %s\n", root->Value());

	printf("P : %p\n", p);

	return 0;
}
