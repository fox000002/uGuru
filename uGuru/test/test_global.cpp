#include <stdio.h>

#include "global.h"

int main()
{
    const char * cmd = "/bin/ls -l -a";

    char ** argv;
    int argc;

    argv = CommandLineToArgv(cmdline, &argc);

    printf("argc : %d\n", argc);
    
    for (int i=0; i<argc; ++i)
    {
        printf("argv %d : %s\n", i, argv[i])
    }

    return 0;
}
