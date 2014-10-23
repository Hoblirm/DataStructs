#ifndef MURMUR3_CUI_HASH
#define MURMUR3_CUI_HASH
#include <stdint.h>

#define ROTL32(num,amount) (((num) << (amount)) | ((num) >> (32 - (amount))))

struct Murmur3CuiHash{

  static const uint32_t c1 = 0xcc9e2d51;
  static const uint32_t c2 = 0x1b873593;
  static const uint32_t r1 = 15;
  static const uint32_t r2 = 13;
  static const uint32_t m = 5;
  static const uint32_t n = 0xe6546b64;

  size_t operator()(const char* key, uint32_t seed = 0) const{
    uint32_t hash = seed;
    const uint32_t *blocks = (const uint32_t *) key;
    uint32_t k;

    k = blocks[0];
    k *= c1;
    k = ROTL32(k,r1);
    k *= c2;
    hash ^= k;
    hash = ROTL32(hash,r2) * m + n;

    k = blocks[1];
    k *= c1;
    k = ROTL32(k,r1);
    k *= c2;
    hash ^= k;

    hash = ROTL32(hash,r2) * m + n;
    k = blocks[2];
    k *= c1;
    k = ROTL32(k,r1);
    k *= c2;
    hash ^= k;
    hash = ROTL32(hash,r2) * m + n;

    k = blocks[3];
    k *= c1;
    k = ROTL32(k,r1);
    k *= c2;
    hash ^= k;
    hash = ROTL32(hash,r2) * m + n;

    hash ^= 16;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
  }
};

#endif
