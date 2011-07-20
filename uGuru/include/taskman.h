#ifndef U_TASKMAN_H
#define U_TASKMAN_H

#include "node.h"

#ifdef __cplusplus
extern "C" {
#endif

enum TaskState {
	TS_UNDEFINED = 0,
	TS_PENDING   = 1,
	TS_READY     = 2,
	TS_RUNNING   = 3,
    TS_FINISHED  = 4,
    TS_ABORT     = 5
};

struct Task {
	int id;
    char name[512];
	enum TaskState ts;
    int sid;
    char subdir[512];

    struct XNode from;
};

enum TaskQueueState {
	TQS_EMPTY     = 0,
	TQS_PENDING   = 1,
	TQS_READY     = 2,
	TQS_BUSY      = 3,
    TQS_ABORT     = 4,
	TQS_FINISHED  = 5
};

extern enum TaskQueueState g_tqs;
extern int g_flag_abort;

typedef struct Task * TaskPtr;

/*! \fn int tasks_from_string(const char * buffer)
 *  \brief Create tasks from a XML string.
 *  \param buffer a XML string.
 *  \return 0 for success, or -1 for fail.
 */
int tasks_from_string(const char * buffer);

int add_to_queue(struct Task * t);

/*! \fn int stop_all_job()
 *  \brief Stop all tasks.
 *  \return 0 for success, or -1 for fail.
 */
int stop_all_job();

void cleanup_task();

/*! \fn TaskPtr serve_queue()
 *  \brief Processing the task queue.
 *  \return the task processed for success, or NULL for fail.
 */
TaskPtr serve_queue();

int run_task(struct Task *t);

int is_no_task();

int is_task_processing();

int is_task_already_exist(TaskPtr t);

int front_task_to_string(char *buffer);

int all_tasks_to_string(char *buffer);

/*! \fn int download_task_files(TaskPtr t) 
 *  \brief Download files for the task.
 *  \param t a struct Task pointer.
 *  \return 0 for success, or -1 for fail.
 */
int download_task_files(TaskPtr t);

#ifdef __cplusplus
}
#endif


#endif /* U_TASKMAN_H */
