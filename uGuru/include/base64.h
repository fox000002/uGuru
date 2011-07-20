#ifndef HUYS_BASE64_H
#define HUYS_BASE64_H

#ifdef __cplusplus
extern "C" {
#endif

char* encode(const char* data, int len, char* dest);
char* decode(const char* data, int len, char* dest);

#ifdef __cplusplus
}
#endif

#endif // HUYS_BASE64_H
