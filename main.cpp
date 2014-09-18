#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <stdio.h>
#include <addressed_map>
#include <object_pool.h>

#include <sstream>
#include <iostream>


class Foo {
  public:
  int id;
  std::string name;

  Foo(void) {}
  ~Foo(void){}
};


int main(int argc, char** argv) {
  object_pool<Foo> pool(1);
  try{
  pool.allocate();
  pool.allocate();
  }
  catch(exception& e){
    printf("We caught that pesky exception: %s\n",e.what());
  }
  return 0;
}

