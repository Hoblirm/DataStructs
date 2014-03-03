#ifndef ADDRESSED_MAP_H
#define ADDRESSED_MAP_H

#include <list>

template <class T> class addressed_map {

  public:
  addressed_map();
  ~addressed_map();

  void insert(int key, const T& obj);
  T* find(int key);
  T* end();

  size_t size();
  size_t capacity();

  private:
  T** mAddressList;
  std::list<T> mContent;

  int mSize;
  int mCapacity;
  int mMinKey;
  bool mMinKeyAssigned;
  void readdress_list(int key);
  void grow_list(int key); 

};

template <class T> addressed_map<T>::addressed_map() {
  mSize = 0;
  mMinKeyAssigned = false;
  mCapacity = 4;
  mAddressList = new T*[mCapacity]();
}

template <class T> addressed_map<T>::~addressed_map() {
  delete [] mAddressList;
}

template <class T> void addressed_map<T>::insert(int key, const T& obj) {
  if (!mMinKeyAssigned) {
    mMinKey = key; 
    mMinKeyAssigned = true;
  }
  if (key < mMinKey) {
    readdress_list(key);
  } else if ( (key - mMinKey) >= mCapacity) {
    grow_list(key);
  }

  mAddressList[key - mMinKey] = &(*mContent.insert(mContent.end(),obj));
  mSize++;
}

template <class T> T* addressed_map<T>::find(int key) {
  if ( (key < mMinKey) || ((key - mMinKey) >= mCapacity) ) {
    return end();
  } else {

    T* iterator = mAddressList[key - mMinKey];

    if (iterator) { 
      return iterator;
    }
    else {
      return end();
    }
  }
}

template <class T> T* addressed_map<T>::end() {
  return &(*mContent.end());
}

template <class T> size_t addressed_map<T>::size() { return mSize;}
template <class T> size_t addressed_map<T>::capacity() { return mCapacity;}

template <class T> void addressed_map<T>::readdress_list(int key) {
  int prevCapacity = mCapacity;
  while (key < mMinKey) {
    mMinKey -= mCapacity;
    mCapacity *= 2;
  }

  T** tmpList = new T*[mCapacity]();
  for (int i=0; i < prevCapacity; i++) {
    tmpList[i+mCapacity-prevCapacity] = mAddressList[i];
  }

  delete [] mAddressList;
  mAddressList = tmpList;
}

template <class T> void addressed_map<T>::grow_list(int key) {
  int prevCapacity = mCapacity;
  while ( (key - mMinKey) >= mCapacity ) {
    mCapacity *=2;
  }

  T** tmpList = new T*[mCapacity]();
  for (int i=0; i < prevCapacity; i++) {
    tmpList[i] = mAddressList[i];
  }
  
  delete [] mAddressList;
  mAddressList = tmpList;
}
#endif /* ADDRESSED_MAP_H */
