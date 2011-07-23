#ifndef MG_MD5_H
#define MG_MD5_H

typedef struct MD5Context {
  uint32_t buf[4];
  uint32_t bits[2];
  unsigned char in[64];
} MD5_CTX;

void MD5Init(MD5_CTX *ctx);

void MD5Update(MD5_CTX *ctx, unsigned char const *buf, unsigned len);

void MD5Final(unsigned char digest[16], MD5_CTX *ctx);

#endif /* MG_MD5_H */
