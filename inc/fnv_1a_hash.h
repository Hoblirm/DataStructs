#include <stdlib.h>

/**
 * Global functionallity.  This is functionality that is shared by
 * ALL templates.  Even those that are specialized.
 **/
class FNV1aHash_base
{
  protected:
  static std::size_t offset_basis;
  static std::size_t FNV_prime;
  static bool initialized;

  public:
  FNV1aHash_base(){
    if (!initialized)
    {
      initialized = true;
      switch (sizeof(std::size_t))
      {
        default:
          // For 32 bit machines:
          FNV_prime = 16777619u;
          offset_basis = 2166136261u;
          break;
/*
        case 8:
          // For 64 bit machines:
          printf("We are on a 64 bit machine~\n");
          FNV_prime = 1099511628211u;
          offset_basis = 14695981039346656037u;
          break;

        case 16:
          // For 128 bit machines:
          FNV_prime = 309485009821345068724781401u;
          offset_basis = 275519064689413815358837431229664493455u;
          break;

        case 32:
          // For 256 bit machines:
          FNV_prime = 374144419156711147060143317175368453031918731002211u;
          offset_basis = 100029257958052580907070968620625704837092796014241193945225284501741471925557u;
          break;
          */
      }
    }
  };

/*  uint64_t hash64(uint64_t key) const
  {
    uint8_t* bytes = (uint8_t*)(&key);
    uint32_t hash = 2166136261U;
    hash = (16777619U * hash) ^ bytes[0];
    hash = (16777619U * hash) ^ bytes[1];
    hash = (16777619U * hash) ^ bytes[2];
    hash = (16777619U * hash) ^ bytes[3];
    hash = (16777619U * hash) ^ bytes[4];
    hash = (16777619U * hash) ^ bytes[5];
    hash = (16777619U * hash) ^ bytes[6];
    hash = (16777619U * hash) ^ bytes[7];
    return hash;
  }*/

};

bool FNV1aHash_base::initialized = false;
std::size_t FNV1aHash_base::FNV_prime = 0;
std::size_t FNV1aHash_base::offset_basis = 0;

/*
 * Default functionality for non-pointers.
 * */
template <class Key> class FNV1aHash : FNV1aHash_base
{
  int mNumberOfBytes;

  public:
  FNV1aHash(){
    if (!FNV1aHash_base::initialized) mNumberOfBytes = sizeof(Key);
  };

  std::size_t operator()(Key&) const;
};

template <class Key> std::size_t FNV1aHash<Key>::operator()(Key& key) const
{
  const unsigned char * data = (const unsigned char *)&key;
  size_t hash = FNV1aHash_base::offset_basis;
  int len = mNumberOfBytes;
  unsigned int c;
  while (len--){
    c = *data;
    hash = (hash ^ c) * FNV1aHash_base::FNV_prime;
    ++data;
  }
  return hash;
}

/*
 * Default functionality for ALL pointer types.
 **/

/*
template <class Key> class FNV1aHash<Key*> : FNV1aHash_base
{
  int mNumberOfBytes;

  public:
  FNV1aHash(){
    if (!FNV1aHash_base::initialized) mNumberOfBytes = sizeof(Key);
  };

  std::size_t operator()(const Key*) const;
};

template <class Key> std::size_t FNV1aHash<Key*>::operator()(const Key* key) const
{
  const unsigned char * data = (const unsigned char *)key;
  size_t hash = FNV1aHash_base::offset_basis;
  int len = mNumberOfBytes;
  unsigned int c;
  while (len--){
    c = *data;
    hash = (hash ^ c) * FNV1aHash_base::FNV_prime;
    ++data;
  }
  return hash;
}
*/

/*
 * Specialized functionality for const char*
 * */


template <> class FNV1aHash<const char*> : FNV1aHash_base
{
  public:
    FNV1aHash(){}
    std::size_t operator()(const char* str) const;
}; 

std::size_t FNV1aHash<const char*>::operator()(const char* str) const
{
  size_t hash = offset_basis;
  int len = strlen(str);
  for (int i=0;i<len;i++){
    hash = (hash ^ str[i]) * FNV_prime;
  }

  return hash;
}

