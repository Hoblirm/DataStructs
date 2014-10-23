#ifndef MURMUR3_CHAR_HASH
#define MURMUR3_CHAR_HASH
#include <stdint.h>

#define ROTL32(num,amount) (((num) << (amount)) | ((num) >> (32 - (amount))))

struct Murmur3CharHash{

  static const uint32_t c1 = 0xcc9e2d51;
  static const uint32_t c2 = 0x1b873593;
  static const uint32_t r1 = 15;
  static const uint32_t r2 = 13;
  static const uint32_t m = 5;
  static const uint32_t n = 0xe6546b64;

  size_t operator()(const char* key, uint32_t seed=0) const{
    return MurmurHash3_x86_32(key,strlen(key), seed);
  }

  inline uint32_t MurmurHash3_x86_32 ( const void * key, const int len,
      uint32_t seed) const
  {
    const uint8_t * data = (const uint8_t*)key;
    const int nblocks = len / 4;
    uint32_t hash = seed;

    //----------
    // body - Hash the key in 4 byte chunks.

    const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);

    for(int i = -nblocks; i; i++)
    {
      uint32_t k1 = blocks[i];

      k1 *= c1;
      k1 = ROTL32(k1,r1);
      k1 *= c2;

      hash ^= k1;
      hash = ROTL32(hash,r2);
      hash = hash * m + n;
    }

    //----------
    // tail - Hash the last 1 to 3 bytes if there are any remaining.

    const uint8_t * tail = (const uint8_t*)(data + nblocks*4);

    uint32_t k1 = 0;

    switch(len & 3)
    {
      case 3: k1 ^= tail[2] << 16;
      case 2: k1 ^= tail[1] << 8;
      case 1: k1 ^= tail[0];
              k1 *= c1; 
              k1 = ROTL32(k1,r1); 
              k1 *= c2; 
              hash ^= k1;
    };

    //----------
    // finalization - 32 bit finalizer

    hash ^= len;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return hash;
  } 

};

#endif
