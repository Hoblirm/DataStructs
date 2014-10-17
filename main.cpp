#include <stdlib.h>

#ifdef _AIX
  #define __IBMCPP_TR1__ 1
  #include <unordered_map>
#else
  #include <tr1/unordered_map>
#endif

#include <string>
#include <sys/time.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <cstddef>
#include <string.h>

#include <fnv_1a_hash.h>
#include <murmur3_hash.h>

class Foo {
  public:
  int id;
  std::string name;

  Foo(void) {}
  ~Foo(void){}
};

struct CharCmpFunctor{
  bool operator()(const char* str1, const char* str2) const{
    return !strcmp(str1,str2);
  }
};

int main(int argc, char** argv) {
  //Test unordered_map
  std::tr1::unordered_map<const char*, Foo> m;
  Foo f;
  f.id = 1337;
  f.name = "One";
  m.insert(std::pair<const char*,Foo>(f.name.c_str(),f));
  if (m.count("One"))
    printf("Unordered_map hashes char*\n");
  else
    printf("Unordered_map does NOT hash char*\n");

  
  std::tr1::unordered_map<const char*, Foo, FNV1aHash<const char*>, CharCmpFunctor> n;
  n.insert(std::pair<const char*,Foo>(f.name.c_str(),f));
  if (n.count("One"))
    printf("Unordered_map<FVN> hashes char*\n");
  else
    printf("Unordered_map<FVN> does NOT hash char*\n");
  
  std::tr1::unordered_map<const char*, Foo, Murmur3CharHash, CharCmpFunctor> o;
  o.insert(std::pair<const char*,Foo>(f.name.c_str(),f));
  if (o.count("One"))
	  printf("Unordered_map<Murmur3> hashes char*\n");
  else
	  printf("Unordered_map<Murmur3> does NOT hash char*\n");


  //Test hash
  char nts1[] = "Test";
  char nts2[] = "Test";

  std::string str1 (nts1);
  std::string str2 (nts2);

  std::tr1::hash<char*> ptr_hash;
  std::tr1::hash<std::string> str_hash;

  std::cout << "same hashes:\n" << std::boolalpha;
  std::cout << "nts1 and nts2: " << (ptr_hash(nts1)==ptr_hash(nts2)) << '\n';
  std::cout << "str1 and str2: " << (str_hash(str1)==str_hash(str2)) << '\n';

  return 0;
}

