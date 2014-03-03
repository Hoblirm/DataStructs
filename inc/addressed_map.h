#ifndef ADDRESSED_MAP_H
#define ADDRESSED_MAP_H

#include <list>

template <class T> class addressed_map {

  public:
  addressed_map();
  ~addressed_map();

  typedef typename std::list<T>::iterator iterator;

  void insert(int key, const T& obj);
  iterator find(int key);
  iterator erase(int key);
  iterator end();

  size_t size();
  size_t content_size();
  size_t capacity();

  private:
  iterator* mAddressList;
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
  mAddressList = new iterator[mCapacity];
  for (int i=0;i<mCapacity;i++){
     mAddressList[i] = end();
  }
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

  mAddressList[key - mMinKey] = mContent.insert(mContent.end(),obj);
  mSize++;
}

template <class T> typename std::list<T>::iterator addressed_map<T>::find(int key) {
  if ( (key < mMinKey) || ((key - mMinKey) >= mCapacity) ) {
    return end();
  } else {
    return mAddressList[key - mMinKey];
  }
}

template <class T> typename std::list<T>::iterator addressed_map<T>::erase(int key) {
   iterator it = find(key);

   if (it != end()){
      mContent.erase(it);
      mAddressList[key - mMinKey] = end();
      mSize--;
   }
      
   return it;
}

template <class T> typename std::list<T>::iterator addressed_map<T>::end() {
   return mContent.end();
}

template <class T> size_t addressed_map<T>::size() { return mSize;}
template <class T> size_t addressed_map<T>::content_size() { return mContent.size();}
template <class T> size_t addressed_map<T>::capacity() { return mCapacity;}

template <class T> void addressed_map<T>::readdress_list(int key) {
  int prevCapacity = mCapacity;
  while (key < mMinKey) {
    mMinKey -= mCapacity;
    mCapacity *= 2;
  }

  iterator* tmpList = new iterator[mCapacity];
  for (int i=0;i<mCapacity;i++){
         tmpList[i] = end();
  }
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

  iterator* tmpList = new iterator[mCapacity];
  for (int i=0;i<mCapacity;i++){
    tmpList[i] = end();
  }
  for (int i=0; i < prevCapacity; i++) {
    tmpList[i] = mAddressList[i];
  }
  
  delete [] mAddressList;
  mAddressList = tmpList;
}
#endif /* ADDRESSED_MAP_H */
