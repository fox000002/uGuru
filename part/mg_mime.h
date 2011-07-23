#ifndef MG_MIME_H
#define MG_MIME_H

struct MIME_Type {
 const char *extension;
 size_t ext_len;
 const char *mime_type;
 size_t mime_type_len;
};

extern const struct MIME_Type builtin_mime_types[];

#endif /* MG_MIME_H */
