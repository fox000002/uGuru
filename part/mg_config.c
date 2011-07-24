#include "mg_defs.h"
#include "mg_pthread.h"
#include "mongoose.h"
#include "mg_ssl.h"
#include "mg_socket.h"

#include "mg_config.h"

const char *config_options[] = {
  "C", "cgi_extensions", ".cgi,.pl,.php",
  "E", "cgi_environment", NULL,
  "G", "put_delete_passwords_file", NULL,
  "I", "cgi_interpreter", NULL,
  "P", "protect_uri", NULL,
  "R", "authentication_domain", "mydomain.com",
  "S", "ssi_extensions", ".shtml,.shtm",
  "a", "access_log_file", NULL,
  "c", "ssl_chain_file", NULL,
  "d", "enable_directory_listing", "yes",
  "e", "error_log_file", NULL,
  "g", "global_passwords_file", NULL,
  "i", "index_files", "index.html,index.htm,index.cgi",
  "k", "enable_keep_alive", "no",
  "l", "access_control_list", NULL,
  "M", "max_request_size", "16384",
  "m", "extra_mime_types", NULL,
  "p", "listening_ports", "8080",
  "r", "document_root",  ".",
  "s", "ssl_certificate", NULL,
  "t", "num_threads", "10",
  "u", "run_as_user", NULL,
  NULL
};


const char **mg_get_valid_option_names(void)
{
	return config_options;
}

int get_option_index(const char *name)
{
  int i;

  for (i = 0; config_options[i] != NULL; i += ENTRIES_PER_CONFIG_OPTION) {
    if (strcmp(config_options[i], name) == 0 ||
        strcmp(config_options[i + 1], name) == 0) {
      return i / ENTRIES_PER_CONFIG_OPTION;
    }
  }
  return -1;
}


// A helper function for traversing comma separated list of values.
// It returns a list pointer shifted to the next value, of NULL if the end
// of the list found.
// Value is stored in val vector. If value has form "x=y", then eq_val
// vector is initialized to point to the "y" part, and val vector length
// is adjusted to point only to "x".
const char *next_option(const char *list, struct vec *val,
                               struct vec *eq_val)
{
  if (list == NULL || *list == '\0') {
    /* End of the list */
    list = NULL;
  } else {
    val->ptr = list;
    if ((list = strchr(val->ptr, ',')) != NULL) {
      /* Comma found. Store length and shift the list ptr */
      val->len = list - val->ptr;
      list++;
    } else {
      /* This value is the last one */
      list = val->ptr + strlen(val->ptr);
      val->len = list - val->ptr;
    }

    if (eq_val != NULL) {
      /*
       * Value has form "x=y", adjust pointers and lengths
       * so that val points to "x", and eq_val points to "y".
       */
      eq_val->len = 0;
      eq_val->ptr = memchr(val->ptr, '=', val->len);
      if (eq_val->ptr != NULL) {
        eq_val->ptr++;  /* Skip over '=' character */
        eq_val->len = val->ptr + val->len - eq_val->ptr;
        val->len = (eq_val->ptr - val->ptr) - 1;
      }
    }
  }

  return list;
}


const char *mg_get_option(const struct mg_context *ctx, const char *name) {
  int i;
  if ((i = get_option_index(name)) == -1) {
    return NULL;
  } else if (ctx->config[i] == NULL) {
    return "";
  } else {
    return ctx->config[i];
  }
}
