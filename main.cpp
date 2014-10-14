#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <cstddef>
#include <string.h>
#include <tr1/unordered_map>
#include <tr1/functional>

#include <fnv_1a_hash.h>

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
    printf("Unordered_map hashes char*\n");
  else
    printf("Unordered_map does NOT hash char*\n");


  if (!(-1)){
    printf("!-1 is true\n");
  }else{
    printf("!-1 is f\n");
  }
  if (!(2)){
         printf("!2 is true\n");
       }else{
           printf("!2 is f\n");
         }

  //Test hash
  char nts1[] = "Test";
  char nts2[] = "Test";
  const char* tmp = (const char*)nts2;
  while (*tmp)
  {
    char t[16];
    t[0] = tmp[0];
    t[1] = '\n';
    t[2] = '\0';
    printf(t);
    ++tmp;
  }

  std::string str1 (nts1);
  std::string str2 (nts2);

  printf("size:%d\n",sizeof(size_t));
  std::tr1::hash<char*> ptr_hash;
  std::tr1::hash<std::string> str_hash;

  std::cout << "same hashes:\n" << std::boolalpha;
  std::cout << "nts1 and nts2: " << (ptr_hash(nts1)==ptr_hash(nts2)) << '\n';
  std::cout << "str1 and str2: " << (str_hash(str1)==str_hash(str2)) << '\n';

  return 0;
}

