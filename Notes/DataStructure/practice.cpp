#include<iosteam>
using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>class Vector
{
private:
    Rank _size;int _capacity;T *_elem;
    void copyFrom(T* const A,Rank lo,Rank hi);
    void expand();
public:
    Vector(int c = DEFAULT_CAPACITY){_elem = new T[_capacity = c];_size=0;};
    ~Vector();
    T& operator[](Rank r)const {return _elem};
    Rank insert(Rank r,T const &e);
    int remove(Rank lo,Rank hi);
    T remove(Rank r);
};

template <typename T>
void Vector<T>::copyFrom(T* const A,Rank lo,Rank hi){
    _elem = new [_capacity = 2*(hi-lo)];
    _size = 0;
    while(lo < hi){
        _elem[_size++] = A[lo++];
    }
}

template <typaname T>
void Vector<T>::expand(){
    if(_size < _capacity)return;
    _capacity = max(_capacity,DEFAULT_CAPACITY);
    _oldElem = _elem;_elem = new T[_capacity<<=1];
    for(int i = 0;i < _size;i++){
        _elem[i] = _oldElem[i];
    }
    delete [] oldElem;
}

template <typename T>
Rank Vector<T>::insert(Rank r,T &const e){
    expand();
    for(int i = _size;i>r;i--){
        _elem[i] = _elem[i--];
    }
    _elem[r] = e;_size++;
    return r;
}

template <typename T>
int remove(Rank lo,Rank hi){
    if(lo == hi)return 0;
    while(hi < _size)_elem[lo++] = _elem[hi++];
    _size = lo; //逻辑上的丢失了
    return hi-lo;
}