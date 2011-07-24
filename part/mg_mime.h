#ifndef MG_MIME_H
#define MG_MIME_H

struct MIME_Type {
 const char *extension;
 size_t ext_len;
 const char *mime_type;
 size_t mime_type_len;
};

extern const struct MIME_Type builtin_mime_types[];

// Look at the "path" extension and figure what mime type it has.
// Store mime type in the vector.
void get_mime_type(struct mg_context *ctx, const char *path,
                          struct vec *vec);

#endif /* MG_MIME_H */
