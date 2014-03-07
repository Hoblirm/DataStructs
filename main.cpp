#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <stdio.h>
#include <map>
#include <addressed_map>

#include <sstream>
#include <iostream>

#include <functional>

#define SIZE 200000
#define MIN -100000

static struct timeval now;
static double start_time, stop_time;

class Telem_t {
  public:
  int id;
  std::string name;

  Telem_t(void) {}
  ~Telem_t(void){}
};

bool operator< (const Telem_t& lhs, const Telem_t& rhs)
{
       return (lhs.id < rhs.id);
}

typedef struct ObjMap {
  ObjMap() : id(0) {}
  int id;
  Telem_t* telem;
  std::string desc;
} ObjMap_t;

bool operator==(const ObjMap_t& lhs, const ObjMap_t& rhs) {return lhs.id == rhs.id;};

// Character compare functor.
struct CmpFunc {

  bool operator()(const ObjMap_t& obj1, const ObjMap_t& obj2) const {
    return obj1.telem->id == obj2.telem->id;
  }
};

// Hash functor.
struct HashFunc {

  size_t operator()(const ObjMap_t& obj) const {
    return obj.telem->id;//hasher(obj.telem->id);
  }
};

void start_test(std::string str = "") {
  gettimeofday(&now, NULL);
  start_time = (now.tv_sec*1000.0)+(now.tv_usec/1000.0);
  std::cout << "======== Start Test " << str << " ========\n";
}

void stop_test() {
  gettimeofday(&now, NULL);
  stop_time = (now.tv_sec*1000.0)+(now.tv_usec/1000.0);  
  printf("%lf milliseconds elapsed\n", stop_time-start_time);
  printf("============================\n");
}

int main(int argc, char** argv) {
  Telem_t telem[SIZE];
  ObjMap_t objMap[SIZE];
  std::map<Telem_t,std::string> ordered_list;
  addressed_map<int, ObjMap_t> addressed_list;
  for (int i=0;i<SIZE;i++){
    std::stringstream ss;
    telem[i].id = i+MIN;
    ss << "Object#" << i;
    telem[i].name = ss.str();
    
    objMap[i].telem = &telem[i];
    std::stringstream ss2;
    ss2 << "Desc#" << i;
    objMap[i].desc = ss2.str();
    objMap[i].id = i+MIN;

    ordered_list.insert(std::pair<Telem_t,std::string>(telem[i],objMap[i].desc));
    addressed_list.insert(std::pair<int,ObjMap_t>(i+MIN,objMap[i]));
  }

  start_test("Addressed List");
  for (int i=0;i<SIZE;i++){
    addressed_list.find(i)->second;
  }
  stop_test();

  start_test("Ordered List");
  for (int i=0;i<SIZE;i++){
    ordered_list.find(telem[i]);
  } 
  stop_test();

  addressed_map<int,ObjMap_t>::iterator a = addressed_list.find(17);

  std::cout << "The value for addressed is:\n";
  std::cout << "  " << a->second.telem->id << "\n";
  std::cout << "  " << a->second.telem->name << "\n";
  std::cout << "  " << a->second.desc << "\n";
  
  Telem_t tel;
  ObjMap_t obj;
  obj.telem = &tel;
  obj.telem->id = -10;
  
  std::cout << "Trying to find 300000\n";
  if (addressed_list.find(300000)==addressed_list.end()) {
    std::cout << "  NOT FOUND\n";
  } else {
    std::cout << "  FOUND\n";
  }

  std::cout << "Trying to find 1000\n";
  if (addressed_list.find(1000)==addressed_list.end()) {
    std::cout << "  NOT FOUND\n";
  } else {
    std::cout << "  FOUND\n";
  }

  return 0;
}

