#include <cxxtest/TestSuite.h>

#include <addressed_vector>
#include <string>
using namespace std;

class addressed_vector_test : public CxxTest::TestSuite {
  public:

    // It should be able to perform a simple insert and find.
    void testZeroBasedKey(void) {
      addressed_vector<string> addr;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      addr.insert(0,str1);
      addr.insert(1,str2);
      addr.insert(2,str3);

      TS_ASSERT(*addr.find(1) == "Banana");
      TS_ASSERT(*addr.find(0) == "Apple");
      TS_ASSERT(*addr.find(2) == "Carrot");
    }

    // It should be able to perform inserts on negative keys.
    void testNegativeKey(void) {
      addressed_vector<string> addr;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      addr.insert(-2,str1);
      addr.insert(-1,str2);
      addr.insert(-3,str3);

      TS_ASSERT(*addr.find(-2) == "Apple");
      TS_ASSERT(*addr.find(-1) == "Banana");
      TS_ASSERT(*addr.find(-3) == "Carrot");
    }

    // It should be able to perform inserts on sparse keys.
    void testSparseKey(void) {
      addressed_vector<string> addr;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      addr.insert(10,str1);
      addr.insert(-128,str2);
      addr.insert(512,str3);

      TS_ASSERT(*addr.find(-128) == "Banana");
      TS_ASSERT(*addr.find(10) == "Apple");
      TS_ASSERT(*addr.find(512) == "Carrot");
    }

    // It should return end() for an invalid key.
    void testInvalidKey(void) {
      addressed_vector<string> addr;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");     

      addr.insert(0,str1);
      addr.insert(1,str2);
      addr.insert(2,str3);

      TS_ASSERT(addr.find(3) == addr.end());
      TS_ASSERT(addr.find(-1) == addr.end());
    }

    // It should be able to initalize to a range of keys.
    void testRangeInitialize(void) {
      addressed_vector<string> addr(-1,1);

      TS_ASSERT_EQUALS(addr.capacity(),3);

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");     

      addr.insert(-1,str1);
      addr.insert(0,str2);
      addr.insert(1,str3);

      TS_ASSERT_EQUALS(addr.capacity(),3);
    }

    // It should be able to used the [] operator for find and insert
    void testBraceOperator(void) {
      addressed_vector<string> addr(3);

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      addr[0] = str1;
      addr[1] = str2;
      addr[2] = str3;

      TS_ASSERT(addr[1] == "Banana");
      TS_ASSERT(addr[0] == "Apple");
      TS_ASSERT(addr[2] == "Carrot");
    }

    // It should be able to remove entries by key.
    void testKeyRemoval(void) {
      addressed_vector<string> addr;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      addr.insert(0,str1);
      addr.insert(1,str2);
      addr.insert(2,str3);

      // Verify everything was properly inserted.
      TS_ASSERT(*addr.find(0) == "Apple");
      TS_ASSERT(*addr.find(1) == "Banana");
      TS_ASSERT(*addr.find(2) == "Carrot");

      // Remove the middle entry.
      addr.erase(1);

      // Ensure that the middle entry was removed.
      TS_ASSERT(addr.find(-1) == addr.end());
      TS_ASSERT_EQUALS(*addr.find(0), "Apple");
      TS_ASSERT(addr.find(1) == addr.end());
      TS_ASSERT_EQUALS(*addr.find(2), "Carrot");
      TS_ASSERT(addr.find(4) == addr.end());
    }

    // It should be able to provide the count for a key.
    void testKeyCount(void) {
      addressed_vector<string> addr;
      
      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      addr.insert(0,str1);
      addr.insert(1,str2);
      addr.insert(2,str3);

      TS_ASSERT_EQUALS(addr.count(0),1);
      TS_ASSERT_EQUALS(addr.count(1),1);
      TS_ASSERT_EQUALS(addr.count(2),1);
      TS_ASSERT_EQUALS(addr.count(-1),0);
      TS_ASSERT_EQUALS(addr.count(3),0);
    }

    // It should be able to iterate all the objects in the addr.
    void testObjectIteration(void) {
      addressed_vector<string> addr;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");
      string str4("Doritos");
      string str5("Egg");

      addr.insert(0,str2);
      addr.insert(1,str3);
      addr.insert(2,str1);
      addr.insert(3,str4);
      addr.insert(4,str5);

      // Loop through all the objects.
      int i = 0;
      int found = 0;
      for (addressed_vector<string>::iterator it = addr.begin(); it != addr.end(); it++) {
        if (addr.find(i) != addr.end()) {
          TS_ASSERT_EQUALS(*it,*addr.find(i));
          found++;
        }
        i++;
      }
      TS_ASSERT_EQUALS(i,addr.capacity());
      TS_ASSERT_EQUALS(found,5);

      // Ensure that the map can still be iterated after a removal.
      addr.erase(1);
      addr.erase(3);

      
      i = 0;
      found = 0;
      for (addressed_vector<string>::iterator it = addr.begin(); it != addr.end(); it++) {
        if (addr.find(i) != addr.end()) {
          TS_ASSERT_EQUALS(*it,*addr.find(i));
          found++;
        }
        i++;
      }
      TS_ASSERT_EQUALS(i,addr.capacity());
      TS_ASSERT_EQUALS(found,3);

    }

    // It should be able to clear all content from the map.
    void testClear() {
      addressed_vector<string> addr;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      addr.insert(0,str2);
      addr.insert(1,str3);
      addr.insert(2,str1);
        
      addr.clear();

      TS_ASSERT(addr.find(0)==addr.end());
      TS_ASSERT(addr.find(1)==addr.end());
      TS_ASSERT(addr.find(2)==addr.end());
    }

    // It should be able to perform inserts with many entries.
    void testStressKey(void) {
      addressed_vector<int> addr;

      // Insert many entries into the map.
      for (int key=-100000;key<key-1000; key++) {
        addr.insert(key,key*10);
      }
      for (int key=10000; key < 300000; key++) {
        addr.insert(key,key*10);
      }
      for (int key=-20;key<100;key++) {
        addr.insert(key,key*10);
      }
      for (int key=-300000;key>-400000;key--) {
        addr.insert(key,key*10);
      }

      // Verify that all the inserted keys can be found.
      for (int key=-100000;key<key-1000; key++) {
        TS_ASSERT_EQUALS(*addr.find(key),key*10);
      }
      for (int key=10000; key < 300000; key++) {
        TS_ASSERT_EQUALS(*addr.find(key),key*10);
      }
      for (int key=-20;key<100;key++) {
        TS_ASSERT_EQUALS(*addr.find(key),key*10);
      }
      for (int key=-300000;key>-400000;key--) {
        TS_ASSERT_EQUALS(*addr.find(key),key*10);
      }

      // Verify that all the unused keys return 0
      TS_ASSERT(addr.find(-400001) == addr.end());
      for (int key=-299999;key < -100000; key++) {
        TS_ASSERT(addr.find(key) == addr.end());
      }
      for (int key=-999;key < -20; key++) {
        TS_ASSERT(addr.find(key) == addr.end());
      }
      for (int key=101; key < 10000; key++) {
        TS_ASSERT(addr.find(key) == addr.end());
      }
      TS_ASSERT(addr.find(300001) == addr.end());
    }
};
