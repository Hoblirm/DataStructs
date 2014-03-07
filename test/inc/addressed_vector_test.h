#include <cxxtest/TestSuite.h>

#include <vector>

#include <iostream>
using namespace std;

class addressed_vector_test : public CxxTest::TestSuite {
  public:

    // It should be able to perform a simple insert and find.
    void testBraceOperator(void) {
      vector<int> addr(2);

      /*
      addr[2] = 2;
      addr[4] = 4;
      addr[8] = 8;
      addr[16] = 16;
      addr[32] = 32;
      addr[64] = 64;
      */

      cout << "Looking through the list with size" << addr.size() << ".\n";
      for (vector<int>::iterator it = addr.begin(); it != addr.end(); ++it) {      
        cout << "  " << *it << "\n";
      }

      addr.insert(addr.end(),1);
      cout << "Looking through the list with size" << addr.size() << "and cap " << addr.capacity() << ".\n";
      for (vector<int>::iterator it = addr.begin(); it != addr.end(); ++it) {      
        cout << "  " << *it << "\n";
      }

    }

};
