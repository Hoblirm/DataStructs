#include <cxxtest/TestSuite.h>

#include "object_pool.h"
#include <string>

using namespace std;

class object_pool_test : public CxxTest::TestSuite {
  public:

    // It should return the capacity of the pool
    void testCapacity(void) {
      object_pool<string> pool(10);
      TS_ASSERT_EQUALS(pool.capacity(),10);
    }

    // It should return the available objects in the pool.
    void testAvailable(void) {
       object_pool<string> pool(10);
       string* ptrList[10];
       for (int i=10;i>0;i--) {
          TS_ASSERT_EQUALS(pool.available(),i);
          ptrList[i] = pool.allocate();
       }
       
       for (int i=0;i<10;i++) {
          TS_ASSERT_EQUALS(pool.available(),i);
          pool.release(ptrList[i]);
       }
    }

};
