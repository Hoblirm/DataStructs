#ifndef ADDRESSED_MAP_H
#define ADDRESSED_MAP_H

template <class T> 
class addressed_map {

  public:
  addressed_map();
  ~addressed_map();

  typedef T* iterator;

  T* insert(int key, const T& obj);
  T& operator[](int key);

  T* find(int key);
  void erase(int key);
  void clear();

  T* begin();
  T* end();

  int size();
  int capacity();
  int count(int key);

  private:
  T** mPtrAry;
  T* mObjAry;

  int mSize;
  int mPtrCapacity;
  int mObjCapacity;
  int mMinKey;
  bool mMinKeyAssigned;
  void shift_ptr_ary(int key);
  void grow_ptr_ary(int key); 
  void grow_obj_ary();
  void shift_obj_ary(T* it);
};

template <class T> 
addressed_map<T>::addressed_map() {
  mSize = 0;
  mMinKeyAssigned = false;
  mPtrCapacity = mObjCapacity = 8;
  mPtrAry = new T*[mPtrCapacity]();
  mObjAry = new T[mObjCapacity];
}

template <class T> 
addressed_map<T>::~addressed_map() {
   delete [] mPtrAry;
   delete [] mObjAry;
}

template <class T> 
void addressed_map<T>::clear() {
  mSize = 0;
  mPtrCapacity = mObjCapacity = 8;
  mMinKeyAssigned = false;
  delete [] mPtrAry;
  delete [] mObjAry;
  mPtrAry = new T*[mPtrCapacity]();
  mObjAry = new T[mObjCapacity];
}

template <class T>
T* addressed_map<T>::begin() {
  return mObjAry;
}

template <class T>
T* addressed_map<T>::end() {
  return mObjAry+mSize;
}

template <class T> 
T* addressed_map<T>::insert(int key, const T& obj) {
  if (!mMinKeyAssigned) {
    mMinKey = key; 
    mMinKeyAssigned = true;
  }

  if (key < mMinKey) {
    shift_ptr_ary(key);
  } else if ( (key - mMinKey) >= mPtrCapacity) {
    grow_ptr_ary(key);
  }

  if (mSize >= mObjCapacity) {
    grow_obj_ary();
  }

  mObjAry[mSize] = obj;
  mPtrAry[key - mMinKey] = &mObjAry[mSize];
  ++mSize;
  return mPtrAry[key - mMinKey];
}

template <class T> 
T& addressed_map<T>::operator[](int key) {
  T* it = find(key);
  if (it != end()) {
    return *it;
  }
  else {
    return *insert(key,T());
  }
}

template <class T> 
T* addressed_map<T>::find(int key) {
  if ( (key < mMinKey) || ((key - mMinKey) >= mPtrCapacity) ) { 
    return end();
  }
  else if (mPtrAry[key - mMinKey]) {
    return mPtrAry[key - mMinKey];
  }
  else { 
    return end();
  }
}

template <class T> 
void addressed_map<T>::erase(int key) {
  T* it = find(key);

  if (it != end()){
    shift_obj_ary(it);
    mPtrAry[key - mMinKey] = 0;
    --mSize;
  } 
}

template <class T> 
int addressed_map<T>::size() { return mSize;}

template <class T> 
int addressed_map<T>::capacity() { return mPtrCapacity;}

template <class T> 
int addressed_map<T>::count(int key) {
  if ( (key < mMinKey) || ((key - mMinKey) >= mPtrCapacity) ) {
    return 0;
  }
  else if (mPtrAry[key - mMinKey]) {
    return 1;
  }
  else {
    return 0;
  }
}

template <class T> 
void addressed_map<T>::shift_ptr_ary(int key) {
  int prevCapacity = mPtrCapacity;
  while (key < mMinKey) {
    mMinKey -= mPtrCapacity;
    mPtrCapacity *= 2;
  }

  T** tmpAry = new T*[mPtrCapacity]();
  for (int i=0; i < prevCapacity; i++) {
     tmpAry[i+mPtrCapacity-prevCapacity] = mPtrAry[i];
  }

  delete [] mPtrAry;
  mPtrAry = tmpAry;
}

template <class T> 
void addressed_map<T>::grow_ptr_ary(int key) {
  int prevCapacity = mPtrCapacity;
  while ( (key - mMinKey) >= mPtrCapacity ) {
    mPtrCapacity *=2;
  }

  T** tmpAry = new T*[mPtrCapacity]();
  for (int i=0; i < prevCapacity; i++) {
     tmpAry[i] = mPtrAry[i];
  }

  delete [] mPtrAry;
  mPtrAry = tmpAry;
}

template <class T> 
void addressed_map<T>::grow_obj_ary() {
  int prevObjCapacity = mObjCapacity;
  mObjCapacity *=2;

  T* tmpObjAry = new T[mObjCapacity];
  for (int i=0; i < prevObjCapacity; i++) {
     tmpObjAry[i] = mObjAry[i];
  }
  for (int i=0; i < mPtrCapacity; i++) {
    if (mPtrAry[i]) {
      mPtrAry[i] = tmpObjAry + (mPtrAry[i] - mObjAry);
    }
  }

  delete [] mObjAry;
  mObjAry = tmpObjAry;
}

template <class T>
void addressed_map<T>::shift_obj_ary(T* it) {
  for (int i=0;i < mPtrCapacity;i++) {
    if (mPtrAry[i]) {
      if (mPtrAry[i] > it) {
        --mPtrAry[i];
      }
    }
  }

  T* last = end() - 1;
  while (it != last) {
    *it = *(it+1);
    ++it;
  }
}

#endif /* ADDRESSED_MAP_H */
