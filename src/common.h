#ifndef common_H
#define common_H

#include <stdint.h>
#include <stdlib.h>

#define ROTR32(X, B) (uint32_t)(((X) >> (B)) | ((X) << (32 - (B))))

#define LOAD32_LE(SRC) load32_le(SRC)
static inline uint32_t
load32_le(const uint8_t src[4])
{
#ifdef NATIVE_LITTLE_ENDIAN
    uint32_t w;
    memcpy(&w, src, sizeof w);
    return w;
#else
    uint32_t w = (uint32_t) src[0];
    w |= (uint32_t) src[1] << 8;
    w |= (uint32_t) src[2] << 16;
    w |= (uint32_t) src[3] << 24;
    return w;
#endif
}

#define STORE32_LE(DST, W) store32_le((DST), (W))
static inline void
store32_le(uint8_t dst[4], uint32_t w)
{
#ifdef NATIVE_LITTLE_ENDIAN
    memcpy(dst, &w, sizeof w);
#else
    dst[0] = (uint8_t) w;
    w >>= 8;
    dst[1] = (uint8_t) w;
    w >>= 8;
    dst[2] = (uint8_t) w;
    w >>= 8;
    dst[3] = (uint8_t) w;
#endif
}

#define G(A, B, C, D)                \
    do {                             \
        (A) += (B);                  \
        (D) = ROTR32((D) ^ (A), 16); \
        (C) += (D);                  \
        (B) = ROTR32((B) ^ (C), 12); \
        (A) += (B);                  \
        (D) = ROTR32((D) ^ (A), 8);  \
        (C) += (D);                  \
        (B) = ROTR32((B) ^ (C), 7);  \
    } while (0)

static const uint32_t IV[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

#endif
