#include <string.h>
#include <time.h>

#include "datetime.h"

extern "C" {

const char * mg_gettime()
{
    //struct tm *newTime;
    time_t szClock;
    char * p = NULL;

    // Get time in seconds
    time( &szClock );

    // Convert time to struct tm form
    //newTime = localtime( &szClock );

    // Print local time as a string.
    //p = asctime(newTime);

    // format: Www Mmm dd hh:mm:ss yyyy
    p = ctime(&szClock);

    // get rid of the tail '\n'
    p[strlen(p)-1] = '\0';

    return p;
}

const char * mg_getdate()
{

    return NULL;
}

void mg_wait(int secs)
{
    clock_t endwait = clock() + secs * CLOCKS_PER_SEC;
    while (clock() < endwait) {}
}

double mg_difftime( long t1, long t2 )
{
    return difftime(t1, t2);
}

}


class Timer
{
public:


private:
};
