#ifndef U_DATETIME_H
#define U_DATETIME_H

#ifdef __cplusplus
extern "C" {
#endif

const char * mg_gettime();

const char * mg_getdate();

void mg_wait(int secs);

/*
 *    Calculates the difference in seconds between t1 and t2.
 */
double mg_difftime(long t1, long t2);

#ifdef __cplusplus
}
#endif

#endif /* U_DATETIME_H */
