#include <stdlib.h>
#include <stdio.h>

#include <cstddef>

#include <string>
#include <iostream>
#include <fstream>

#include <string.h>

#include <map>

#include "timer.h"

#include <fnv_1a_hash.h>
#include <murmur3_hash.h>
#include <murmur3_cui_hash.h>

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

const int CUI_LIST_SIZE = 100000;
int main(int argc, char** argv) {
  char str1[17] = "123456789ABCDEF0";
  char str2[17] = "123456789ABCDEF0";
  char** cui_list;

  cui_list = new char*[CUI_LIST_SIZE];
  for (int i=0;i<CUI_LIST_SIZE;i++){
    cui_list[i] = new char[17];
  }
  int number_of_cuis = 0;
  std::string line;
  std::ifstream myfile ("./data/all_cuis.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      strcpy(cui_list[number_of_cuis],line.c_str());
      number_of_cuis++;
    }
    myfile.close();
    std::cout << "Read " << number_of_cuis << " CUIs\n";
  }
  else std::cout << "Unable to open file"; 

  FNV1aHash<const char*> fnv;
  Murmur3CharHash mur;
  Murmur3CuiHash mur_cui;

  if (fnv(str1) == fnv(str2))
  {
    printf("FNV successfully hashed string.\n");
  }
  else
  {
    printf("FNV failed to hash string.\n");
  }

  if (mur(str1) == mur(str2))
  {
    printf("Murmur3 successfully hashed string.\n");
  }
  else
  {
    printf("Murmur3 failed to hash string.\n");
  }

  if (mur_cui(str1) == mur_cui(str2))
  {
    printf("Murmur3Cui successfully hashed string.\n");
  }
  else
  {
    printf("Murmur3b failed to hash string.\n");
  }

  if (mur_cui(str1) == mur(str1)) {
    printf("Murmur3Cui hash matches Murmur3.\n");
  }
  else {
    printf("Murmur3b hash doesn't match.\n");
  }

  std::map<size_t,bool> collision_map;
  int collision_count = 0;
  size_t h;
  for (int i=0;i < number_of_cuis; i++){
    h = fnv(cui_list[i]) % (number_of_cuis * 4);
    if (collision_map.count(h) == 0) {
      collision_map[h] = true;
    }
    else {
      collision_count++;
    }
  }
  std::cout << "The FNV collsion count was " << collision_count << ".\n";

  collision_map.clear();
  collision_count = 0;
  for (int i=0;i < number_of_cuis; i++){
    h = mur(cui_list[i]) % (number_of_cuis * 4);
    if (collision_map.count(h) == 0) {
      collision_map[h] = true;
    }
    else {
      collision_count++;
    }
  }
  std::cout << "The Murmur3 collsion count was " << collision_count << ".\n";

  Timer t;
  double ms;
  t.start();
  size_t results[number_of_cuis];
  for (int i=0;i < number_of_cuis; i++){
    fnv(cui_list[i]);
  }
  ms = t.stop();
  std::cout << "The FNV hash time was: " << ms << "\n";

  t.start();
  for (int i=0;i < number_of_cuis; i++){
    mur(cui_list[i]);
  }
  ms = t.stop();
  std::cout << "The Murmur3 hash time was: " << ms << "\n";

  t.start();
  for (int i=0;i < number_of_cuis; i++){
    mur_cui(cui_list[i]);
  }
  ms = t.stop();
  std::cout << "The Murmur3Cui hash time was: " << ms << "\n";

  for (int i=0; i < CUI_LIST_SIZE; i++){
    delete[] cui_list[i];
  }
  delete[] cui_list;

  return 0;
}

