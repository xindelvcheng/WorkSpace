#include<iostream>
using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>class Vector
{
private:
    Rank _size;int _capacity;T* _elem;
    void copyFrom(T* const,Rank lo,Rank hi);
    void expand();
public:
    Vector(int c = DEFAULT_CAPACITY);
    ~Vector();
    T& operator[](Rank r)const {return _elem};
}