#ifndef U_SOLVER_H
#define U_SOLVER_H

#ifdef __cplusplus
extern "C" {
#endif

struct Solver {
	int id;
	char name[256];
	char command[512];
    char arg[512];
};

typedef struct Solver * SolverPtr;

int solver_from_string(const char *str, struct Solver * s);

const char * solver_to_string(const struct Solver *s, char *str);

struct Solver * solver_from_id(int id);

int init_solvers(const char * fn);

void clear_solvers();

#ifdef __cplusplus
}
#endif

#endif /* U_SOLVER_H */
