#ifndef U_SYSINFO_H
#define U_SYSINFO_H

#ifdef __cplusplus
extern "C" {
#endif

int is_win();

int is_32();

int is_win32();

int cpu_num();

const char * os_type();

/*! \fn int system_load() 
 *  \brief Get the system load.
 *  \return system load in percent.
 */
int system_load();

#ifdef __cplusplus
}
#endif

#endif /* U_SYSINFO_H */
