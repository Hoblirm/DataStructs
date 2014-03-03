#ifndef ADDRESSED_MAP_H
#define ADDRESSED_MAP_H

template <class T> class addressed_map {

  public:
  addressed_map();
  ~addressed_map();

  void insert(int key, const T& obj);
  T* find(int key);
  T* erase(int key);
  void clear();

  size_t size();
  size_t capacity();

  private:
  T** mList;

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
  mCapacity = 8;
  mList = new T*[mCapacity]();
}

template <class T> addressed_map<T>::~addressed_map() {
   clear();
   delete [] mList;
}

template <class T> void addressed_map<T>::clear() {
   for (int i=0;i<mCapacity;i++) {
      if (mList[i]) delete mList[i];
   }
   mSize = 0;
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

  mList[key - mMinKey] = new T(obj);
  mSize++;
}

template <class T> T* addressed_map<T>::find(int key) {
   if ( (key < mMinKey) || ((key - mMinKey) >= mCapacity) ) {
      return 0;
   } else {
      return mList[key - mMinKey];
   }
}

template <class T> T* addressed_map<T>::erase(int key) {
   T* ptr = find(key);

   if (ptr){
      delete mList[key - mMinKey];
      mList[key - mMinKey] = 0;
      mSize--;
   }

   return ptr;
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
     tmpList[i+mCapacity-prevCapacity] = mList[i];
  }

  delete [] mList;
  mList = tmpList;
}

template <class T> void addressed_map<T>::grow_list(int key) {
  int prevCapacity = mCapacity;
  while ( (key - mMinKey) >= mCapacity ) {
    mCapacity *=2;
  }

  T** tmpList = new T*[mCapacity]();
  for (int i=0; i < prevCapacity; i++) {
     tmpList[i] = mList[i];
  }

  delete [] mList;
  mList = tmpList;
}
#endif /* ADDRESSED_MAP_H */
