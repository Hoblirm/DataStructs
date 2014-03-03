#include <cxxtest/TestSuite.h>

#include "addressed_map.h"
#include <string>

using namespace std;

class addressed_map_test : public CxxTest::TestSuite {
  public:

    // It should be able to perform a simple insert and find.
    void testZeroBasedKey(void) {
      addressed_map<string> list;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      list.insert(0,str1);
      list.insert(1,str2);
      list.insert(2,str3);

      TS_ASSERT(*list.find(1) == "Banana");
      TS_ASSERT(*list.find(0) == "Apple");
      TS_ASSERT(*list.find(2) == "Carrot");
    }

    // It should be able to perform inserts on negative keys.
    void testNegativeKey(void) {
      addressed_map<std::string> list;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      list.insert(-2,str1);
      list.insert(-1,str2);
      list.insert(-3,str3);

      TS_ASSERT(*list.find(-2) == "Apple");
      TS_ASSERT(*list.find(-1) == "Banana");
      TS_ASSERT(*list.find(-3) == "Carrot");
    }

    // It should be able to perform inserts on sparse keys.
    void testSparseKey(void) {
      addressed_map<string> list;
     
      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");

      list.insert(10,str1);
      list.insert(-128,str2);
      list.insert(512,str3);

      TS_ASSERT(*list.find(-128) == "Banana");
      TS_ASSERT(*list.find(10) == "Apple");
      TS_ASSERT(*list.find(512) == "Carrot");
    }

    // It should be able to perform inserts with many entries.
    void testStressKey(void) {
      addressed_map<int> list;

      // Insert many entries into the map.
      for (int key=-100000;key<key-1000; key++) {
        list.insert(key,key*10);
      }
      for (int key=10000; key < 300000; key++) {
        list.insert(key,key*10);
      }
      for (int key=-20;key<100;key++) {
        list.insert(key,key*10);
      }
      for (int key=-300000;key>-400000;key--) {
        list.insert(key,key*10);
      }

      // Verify that all the inserted keys can be found.
      for (int key=-100000;key<key-1000; key++) {
        TS_ASSERT_EQUALS(*list.find(key),key*10);
      }
      for (int key=10000; key < 300000; key++) {
        TS_ASSERT_EQUALS(*list.find(key),key*10);
      }
      for (int key=-20;key<100;key++) {
        TS_ASSERT_EQUALS(*list.find(key),key*10);
      }
      for (int key=-300000;key>-400000;key--) {
        TS_ASSERT_EQUALS(*list.find(key),key*10);
      }

      // Verify that all the unused keys return 0
      TS_ASSERT(list.find(-400001) == 0);
      for (int key=-299999;key < -100000; key++) {
        TS_ASSERT(list.find(key) == 0);
      }
      for (int key=-999;key < -20; key++) {
        TS_ASSERT(list.find(key) == 0);
      }
      for (int key=101; key < 10000; key++) {
        TS_ASSERT(list.find(key) == 0);
      }
      TS_ASSERT(list.find(300001) == 0);
    }

    // It should return 0 for an invalid key.
    void testInvalidKey(void) {
      addressed_map<string> list;

      string str1("Apple");
      string str2("Banana");
      string str3("Carrot");     

      list.insert(0,str1);
      list.insert(1,str2);
      list.insert(2,str3);

      TS_ASSERT(list.find(3) == 0);
      TS_ASSERT(list.find(-1) == 0);
    }

    // It should be able to remove entries by key.
    void testKeyRemoval(void) {
       addressed_map<string> list;

       string str1("Apple");
       string str2("Banana");
       string str3("Carrot");

       list.insert(0,str1);
       list.insert(1,str2);
       list.insert(2,str3);

       // Verify everything was properly inserted.
       TS_ASSERT(*list.find(0) == "Apple");
       TS_ASSERT(*list.find(1) == "Banana");
       TS_ASSERT(*list.find(2) == "Carrot");
       TS_ASSERT_EQUALS(list.size(),3);
       //TS_ASSERT_EQUALS(list.content_size(),3);

       // Remove the middle entry.
       list.erase(1);

       // Ensure that the middle entry was removed.
       //TS_ASSERT_EQUALS(*str_ptr,"Banana");
       TS_ASSERT_EQUALS(list.size(),2);
//       TS_ASSERT_EQUALS(list.content_size(),2);
       TS_ASSERT(list.find(-1) == 0);
       TS_ASSERT_EQUALS(*list.find(0), "Apple");
       TS_ASSERT(list.find(1) == 0);
       TS_ASSERT_EQUALS(*list.find(2), "Carrot");
       TS_ASSERT(list.find(4) == 0);
    }

};
