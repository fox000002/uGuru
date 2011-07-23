#ifndef MG_FILE_H
#define MG_FILE_H

#if defined(_WIN32)

FILE *mg_fopen(const char *path, const char *mode);

#else



#endif

#endif /* MG_FILE_H */