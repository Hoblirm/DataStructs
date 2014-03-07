#ifndef ADDRESSED_MAP_H
#define ADDRESSED_MAP_H

template <class K, typename V> 
class addressed_map {

  public:
  addressed_map();
  ~addressed_map();

  typedef std::pair<K,V>* iterator;

  std::pair<K,V>* insert(const std::pair<K,V>& obj);
  V& operator[](const K& key);

  std::pair<K,V>* find(const K& key);
  void erase(const K& key);
  void clear();

  std::pair<K,V>* begin();
  std::pair<K,V>* end();

  int size();
  int capacity();
  int count(const K& key);

  private:
  std::pair<K,V>** mPtrAry;
  std::pair<K,V>* mObjAry;

  int mSize;
  int mPtrCapacity;
  int mObjCapacity;
  int mMinAddr;
  bool mMinAddrAssigned;
  void shift_ptr_ary(int addr);
  void grow_ptr_ary(int addr); 
  void grow_obj_ary();
  void shift_obj_ary(std::pair<K,V>* it);
};

template <typename K, typename V> 
addressed_map<K, V>::addressed_map() {
  mSize = 0;
  mMinAddrAssigned = false;
  mPtrCapacity = mObjCapacity = 8;
  mPtrAry = new std::pair<K,V>*[mPtrCapacity]();
  mObjAry = new std::pair<K,V>[mObjCapacity];
}

template <typename K, typename V> 
addressed_map<K, V>::~addressed_map() {
   delete [] mPtrAry;
   delete [] mObjAry;
}

template <typename K, typename V> 
void addressed_map<K, V>::clear() {
  mSize = 0;
  mPtrCapacity = mObjCapacity = 8;
  mMinAddrAssigned = false;
  delete [] mPtrAry;
  delete [] mObjAry;
  mPtrAry = new std::pair<K,V>*[mPtrCapacity]();
  mObjAry = new std::pair<K,V>[mObjCapacity];
}

template <typename K, typename V>
std::pair<K,V>* addressed_map<K, V>::begin() {
  return mObjAry;
}

template <typename K, typename V>
std::pair<K,V>* addressed_map<K, V>::end() {
  return mObjAry+mSize;
}

template <typename K, typename V> 
std::pair<K,V>* addressed_map<K, V>::insert(const std::pair<K,V>& obj) {
  K key = obj.first;
  if (!mMinAddrAssigned) {
    mMinAddr = key; 
    mMinAddrAssigned = true;
  }

  if (key < mMinAddr) {
    shift_ptr_ary(key);
  } else if ( (key - mMinAddr) >= mPtrCapacity) {
    grow_ptr_ary(key);
  }

  if (mSize >= mObjCapacity) {
    grow_obj_ary();
  }

  mObjAry[mSize] = obj;
  mPtrAry[key - mMinAddr] = &mObjAry[mSize];
  ++mSize;
  return mPtrAry[key - mMinAddr];
}

template <typename K, typename V> 
V& addressed_map<K, V>::operator[](const K& key) {
  std::pair<K,V>* it = find(key);
  if (it != end()) {
    return it->second;
  }
  else {
    return insert(std::pair<K,V>(key,V()))->second;
  }
}

template <typename K, typename V> 
std::pair<K,V>* addressed_map<K, V>::find(const K& key) {
  if ( (key < mMinAddr) || ((key - mMinAddr) >= mPtrCapacity) ) { 
    return end();
  }
  else if (mPtrAry[key - mMinAddr]) {
    return mPtrAry[key - mMinAddr];
  }
  else { 
    return end();
  }
}

template <typename K, typename V> 
void addressed_map<K, V>::erase(const K& key) {
  std::pair<K,V>* it = find(key);

  if (it != end()){
    shift_obj_ary(it);
    mPtrAry[key - mMinAddr] = 0;
    --mSize;
  } 
}

template <typename K, typename V> 
int addressed_map<K, V>::size() { return mSize;}

template <typename K, typename V> 
int addressed_map<K, V>::capacity() { return mPtrCapacity;}

template <typename K, typename V> 
int addressed_map<K, V>::count(const K& key) {
  if ( (key < mMinAddr) || ((key - mMinAddr) >= mPtrCapacity) ) {
    return 0;
  }
  else if (mPtrAry[key - mMinAddr]) {
    return 1;
  }
  else {
    return 0;
  }
}

template <typename K, typename V> 
void addressed_map<K, V>::shift_ptr_ary(int addr) {
  int prevCapacity = mPtrCapacity;
  while (addr< mMinAddr) {
    mMinAddr -= mPtrCapacity;
    mPtrCapacity *= 2;
  }

  std::pair<K,V>** tmpAry = new std::pair<K,V>*[mPtrCapacity]();
  for (int i=0; i < prevCapacity; i++) {
     tmpAry[i+mPtrCapacity-prevCapacity] = mPtrAry[i];
  }

  delete [] mPtrAry;
  mPtrAry = tmpAry;
}

template <typename K, typename V> 
void addressed_map<K, V>::grow_ptr_ary(int addr) {
  int prevCapacity = mPtrCapacity;
  while ( (addr - mMinAddr) >= mPtrCapacity ) {
    mPtrCapacity *=2;
  }

  std::pair<K,V>** tmpAry = new std::pair<K,V>*[mPtrCapacity]();
  for (int i=0; i < prevCapacity; i++) {
     tmpAry[i] = mPtrAry[i];
  }

  delete [] mPtrAry;
  mPtrAry = tmpAry;
}

template <typename K, typename V> 
void addressed_map<K, V>::grow_obj_ary() {
  int prevObjCapacity = mObjCapacity;
  mObjCapacity *=2;

  std::pair<K,V>* tmpObjAry = new std::pair<K,V>[mObjCapacity];
  for (int i=0; i < prevObjCapacity; i++) {
     tmpObjAry[i] = mObjAry[i];
     mPtrAry[tmpObjAry[i].first - mMinAddr] = &tmpObjAry[i];
  }

  delete [] mObjAry;
  mObjAry = tmpObjAry;
}

template <typename K, typename V>
void addressed_map<K, V>::shift_obj_ary(std::pair<K,V>* it) {
  std::pair<K,V>* last = end() - 1;
  while (it != last) {
    *it = *(it+1);
    mPtrAry[it->first - mMinAddr] = it;
    ++it;
  }
}

#endif /* ADDRESSED_MAP_H */
