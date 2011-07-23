#ifndef MG_PTHREAD_H
#define MG_PTHREAD_H

typedef void * (*mg_thread_func_t)(void *);

#if defined(_WIN32)  // Windows specific #includes and #defines

typedef HANDLE pthread_mutex_t;
typedef struct {HANDLE signal, broadcast;} pthread_cond_t;
typedef DWORD pthread_t;
#define pid_t HANDLE // MINGW typedefs pid_t to int. Using #define here.

int pthread_mutex_lock(pthread_mutex_t *);
int pthread_mutex_unlock(pthread_mutex_t *);
int pthread_mutex_init(pthread_mutex_t *mutex, void *unused);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_cond_init(pthread_cond_t *cv, const void *unused);
int pthread_cond_wait(pthread_cond_t *cv, pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t *cv);
int pthread_cond_broadcast(pthread_cond_t *cv);
int pthread_cond_destroy(pthread_cond_t *cv);
pthread_t pthread_self(void);

#else    // UNIX  specific

#include <pthread.h>

#endif /* _WIN32 */

#endif /* MG_PTHREAD_H */
