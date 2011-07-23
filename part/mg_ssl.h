#ifndef MG_SSL_H
#define MG_SSL_H

// Snatched from OpenSSL includes. I put the prototypes here to be independent
// from the OpenSSL source installation. Having this, mongoose + SSL can be
// built on any system with binary SSL libraries installed.
typedef struct ssl_st SSL;
typedef struct ssl_method_st SSL_METHOD;
typedef struct ssl_ctx_st SSL_CTX;

#define SSL_ERROR_WANT_READ 2
#define SSL_ERROR_WANT_WRITE 3
#define SSL_FILETYPE_PEM 1
#define CRYPTO_LOCK  1

#if defined(NO_SSL_DL)
extern void SSL_free(SSL *);
extern int SSL_accept(SSL *);
extern int SSL_connect(SSL *);
extern int SSL_read(SSL *, void *, int);
extern int SSL_write(SSL *, const void *, int);
extern int SSL_get_error(const SSL *, int);
extern int SSL_set_fd(SSL *, int);
extern SSL *SSL_new(SSL_CTX *);
extern SSL_CTX *SSL_CTX_new(SSL_METHOD *);
extern SSL_METHOD *SSLv23_server_method(void);
extern int SSL_library_init(void);
extern void SSL_load_error_strings(void);
extern int SSL_CTX_use_PrivateKey_file(SSL_CTX *, const char *, int);
extern int SSL_CTX_use_certificate_file(SSL_CTX *, const char *, int);
extern int SSL_CTX_use_certificate_chain_file(SSL_CTX *, const char *);
extern void SSL_CTX_set_default_passwd_cb(SSL_CTX *, mg_callback_t);
extern void SSL_CTX_free(SSL_CTX *);
extern unsigned long ERR_get_error(void);
extern char *ERR_error_string(unsigned long, char *);
extern int CRYPTO_num_locks(void);
extern void CRYPTO_set_locking_callback(void (*)(int, int, const char *, int));
extern void CRYPTO_set_id_callback(unsigned long (*)(void));
#else
// Dynamically loaded SSL functionality
struct ssl_func {
  const char *name;   // SSL function name
  void  (*ptr)(void); // Function pointer
};

#define SSL_free (* (void (*)(SSL *)) ssl_sw[0].ptr)
#define SSL_accept (* (int (*)(SSL *)) ssl_sw[1].ptr)
#define SSL_connect (* (int (*)(SSL *)) ssl_sw[2].ptr)
#define SSL_read (* (int (*)(SSL *, void *, int)) ssl_sw[3].ptr)
#define SSL_write (* (int (*)(SSL *, const void *,int)) ssl_sw[4].ptr)
#define SSL_get_error (* (int (*)(SSL *, int)) ssl_sw[5])
#define SSL_set_fd (* (int (*)(SSL *, SOCKET)) ssl_sw[6].ptr)
#define SSL_new (* (SSL * (*)(SSL_CTX *)) ssl_sw[7].ptr)
#define SSL_CTX_new (* (SSL_CTX * (*)(SSL_METHOD *)) ssl_sw[8].ptr)
#define SSLv23_server_method (* (SSL_METHOD * (*)(void)) ssl_sw[9].ptr)
#define SSL_library_init (* (int (*)(void)) ssl_sw[10].ptr)
#define SSL_CTX_use_PrivateKey_file (* (int (*)(SSL_CTX *, \
        const char *, int)) ssl_sw[11].ptr)
#define SSL_CTX_use_certificate_file (* (int (*)(SSL_CTX *, \
        const char *, int)) ssl_sw[12].ptr)
#define SSL_CTX_set_default_passwd_cb \
  (* (void (*)(SSL_CTX *, mg_callback_t)) ssl_sw[13].ptr)
#define SSL_CTX_free (* (void (*)(SSL_CTX *)) ssl_sw[14].ptr)
#define SSL_load_error_strings (* (void (*)(void)) ssl_sw[15].ptr)
#define SSL_CTX_use_certificate_chain_file \
  (* (int (*)(SSL_CTX *, const char *)) ssl_sw[16].ptr)

#define CRYPTO_num_locks (* (int (*)(void)) crypto_sw[0].ptr)
#define CRYPTO_set_locking_callback \
  (* (void (*)(void (*)(int, int, const char *, int))) crypto_sw[1].ptr)
#define CRYPTO_set_id_callback \
  (* (void (*)(unsigned long (*)(void))) crypto_sw[2].ptr)
#define ERR_get_error (* (unsigned long (*)(void)) ssl_sw[3].ptr)
#define ERR_error_string (* (char * (*)(unsigned long, char *)) ssl_sw[4].ptr)

// set_ssl_option() function updates this array.
// It loads SSL library dynamically and changes NULLs to the actual addresses
// of respective functions. The macros above (like SSL_connect()) are really
// just calling these functions indirectly via the pointer.
static struct ssl_func ssl_sw[] = {
  {"SSL_free",   NULL},
  {"SSL_accept",   NULL},
  {"SSL_connect",   NULL},
  {"SSL_read",   NULL},
  {"SSL_write",   NULL},
  {"SSL_get_error",  NULL},
  {"SSL_set_fd",   NULL},
  {"SSL_new",   NULL},
  {"SSL_CTX_new",   NULL},
  {"SSLv23_server_method", NULL},
  {"SSL_library_init",  NULL},
  {"SSL_CTX_use_PrivateKey_file", NULL},
  {"SSL_CTX_use_certificate_file",NULL},
  {"SSL_CTX_set_default_passwd_cb",NULL},
  {"SSL_CTX_free",  NULL},
  {"SSL_load_error_strings", NULL},
  {"SSL_CTX_use_certificate_chain_file", NULL},
  {NULL,    NULL}
};

// Similar array as ssl_sw. These functions could be located in different lib.
static struct ssl_func crypto_sw[] = {
  {"CRYPTO_num_locks",  NULL},
  {"CRYPTO_set_locking_callback", NULL},
  {"CRYPTO_set_id_callback", NULL},
  {"ERR_get_error",  NULL},
  {"ERR_error_string", NULL},
  {NULL,    NULL}
};
#endif // NO_SSL_DL

#endif /* MG_SSL_H */
