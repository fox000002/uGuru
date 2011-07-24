#ifndef MG_CONFIG_H
#define MG_CONFIG_H

extern const char *config_options[];

#define ENTRIES_PER_CONFIG_OPTION 3

const char **mg_get_valid_option_names(void);

int get_option_index(const char *name);

const char *next_option(const char *list, struct vec *val,
                               struct vec *eq_val);
							   

const char *mg_get_option(const struct mg_context *ctx, const char *name);							   
							   
#endif /* MG_CONFIG_H */
