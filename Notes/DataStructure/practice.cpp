<<<<<<< HEAD
#include <iostream>
=======
#include<iostream>
>>>>>>> ab1b7cfb54b611b3e4530d51cdd44f31a4b80ea8
using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>class Vector
{
private:
    Rank _size;int _capacity;T* _elem;
<<<<<<< HEAD
    void copyFrom(T* const A,Rank lo,Rank hi);
=======
    void copyFrom(T* const,Rank lo,Rank hi);
>>>>>>> ab1b7cfb54b611b3e4530d51cdd44f31a4b80ea8
    void expand();
public:
    Vector(int c = DEFAULT_CAPACITY);
    ~Vector();
<<<<<<< HEAD
    T& operator[](Rank r)const{return _elem[r]};

    Rank insert(Rank r,T const&e);
    int remove(Rank lo,Rank hi);
    int remove(Rank r);
}

template <typename T>
Vector<T>::Vector(int c = DEFAULT_CAPACITY)
{
    _elem = new T[_capacity=c];
    _size = 0;
}

template <typename T>
void Vector<T>::copyFrom(T * const A,Rank lo,Rank hi){
    _elem = new T[_capacity = 2*(hi-lo)];
    _size = 0;
    while(lo < hi){
        _elem[_size++] = A[lo++];
    }
}

template <typename T>
void Vector<T>::expand(){
    if(_size < _capacity)return;
    _capacity = max(_capactiy,DEFAULT_CAPACITY);
    T* oldElem = _elem;_elem = new T[_capacity<<=1];
    for(int i = 0;i< _size;i++)
        _elem[i] = _oldElem[i];
    delete [] _oldElem;
}

template <typename T>
Rank Vector<T>::insert(Rank r,T const &e){
    for(int i = _size;i>r;i--){
        _elem[i] = _elem[i-1];
    }
    _elem[r] = e;
    _size++;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo,Rank hi)
{
    if(lo < hi)return 0;
    while(hi < _size){
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    return hi-lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r,r+1);
    return e;
}

template <typename T>
Rank Vector<T>::find(T const &e,Rank lo,Rank hi)const
{
    while((lo < hi--)&&e!=_elem[hi]);
    return hi;
}

template <typename T>
int Vector<T>::deduplicate(){
    int oldSize = _size;
    int i = 0;
    while(i < _size){
        (find(_elem[i],0,i) < 0) ? i++:remove(i);
    }
    return oldElem - _size;
}

template <typename T>template <typename VST>
void Vector<T>::traverse(VST & visit)
{
    for(int i = 0;i<_size;i++)visit(_elem[i]);
}
template<typename T>
struct Increase{
    virtual void operator()(T& e){e++;};
}
void increase(Vector<T> &V){
    V.traverse(Increase<T>());
}
//原理和python中重写__call__方法类似
=======
    T& operator[](Rank r)const {return _elem};
}
>>>>>>> ab1b7cfb54b611b3e4530d51cdd44f31a4b80ea8
