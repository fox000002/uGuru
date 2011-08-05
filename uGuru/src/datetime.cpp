#include <string.h>
#include <time.h>

#include "datetime.h"

extern "C" {

const char * mg_gettime()
{
    struct tm *newTime;
    time_t szClock;
    char * p = NULL;

    // Get time in seconds
    time( &szClock );

    // Convert time to struct tm form 
    newTime = localtime( &szClock );

    // Print local time as a string.
    p = asctime(newTime);

    // get rid of the tail '\n'
    p[strlen(p)-1] = '\0';

    return p;
}

const char * mg_getdate()
{

	return NULL;
}

}
