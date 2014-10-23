#include <cxxtest/TestSuite.h>
#include "murmur3_hash.h"
#include "murmur3_cui_hash.h"
#include <string>

using namespace std;

class hash_test : public CxxTest::TestSuite {
  public:

    // It should return the capacity of the pool
    void testVerification(void) {
      Murmur3CharHash m;
      TS_ASSERT(VerificationTest(m,0xB0F57EE3));
    }

    void testCuiHash(void) {
      Murmur3CharHash m;
      Murmur3CuiHash c;
      TS_ASSERT_EQUALS(m("1234567890123456"), c("1234567890123456"));
    }

  private:
    bool VerificationTest(Murmur3CharHash hash, uint32_t expected)
    {
      const int hashbytes = 4;
      uint8_t * key    = new uint8_t[256];
      uint32_t * hashes = new uint32_t[256];
      uint32_t final;

      memset(key,0,256);
      memset(hashes,0,256);

      // Hash keys of the form {0}, {0,1}, {0,1,2}... up to N=255,using 256-N as
      // the seed

      for(int i = 0; i < 256; i++)
      {
        key[i] = (uint8_t)i;
        hashes[i]=hash.MurmurHash3_x86_32(key,i,256-i);
      }

      // Then hash the result array
      
      final = hash.MurmurHash3_x86_32(hashes,hashbytes*256,0);

      // The first four bytes of that hash, interpreted as a little-endian integer, is our
      // verification value

      uint32_t verification = final;//(final[0] << 0) | (final[1] << 8) | (final[2] << 16) | (final[3] << 24);

      if(expected != verification)
      {
        printf("Verification value 0x%08X : Failed! (Expected 0x%08x)\n",verification,expected);
        return false;
      }
      else
      {
        return true;
      }

      delete [] key;
      delete [] hashes;
    }

};
