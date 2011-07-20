#ifndef U_CONFIG_H
#define U_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int load_config(const char *fn);

extern char document_root[512];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* U_CONFIG_H */
