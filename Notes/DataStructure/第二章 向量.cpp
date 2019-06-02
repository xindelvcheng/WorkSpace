#include<iostream>

using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3


template <typename T> class Vector
{
private:
	Rank _size;int _capacity;T* _elem;
    void copyFrom(T* const A,Rank lo,Rank hi);
    void expand();
public:
	Vector(int c = DEFAULT_CAPACITY);
	~Vector();
	T& operator[](Rank r)const { return _elem };

	Rank insert(Rank r, T const& e);
	int remove(Rank lo, Rank hi);
	int remove(Rank r);
};

Vector::Vector(int c = DEFAULT_CAPACITY)
{
    _elem = new T[_capacity=c];
    _size = 0;
}

Vector::~Vector()
{
}


//将数组A从lo到hi的区间的元素拷贝给Vector
template <typename T>
void Vector<T>::copyFrom(T* const A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)]; //默认区间是左闭右开的即[lo,hi),这样hi-lo就是区间的长度
	_size = 0;
	while (lo < hi) {
		_elem[_size++] = A[lo++];
	}
}

template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity)return;
	_capacity = max(_capacity, DEFAULT_CAPACITY);
	T* oldElem = _elem; _elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

//像数组那样使用A[r]的方式访问
template <typename T> //0 <= r < _size
T& Vector<T>::operator[](Rank r)const { return _elem };


template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; i--) {
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e; _size++;
	return r;
}


//删除n个元素，即是把包括hi内所有元素整体向前移动hi-lo个位置
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)return 0;//退化的情况
	while (hi < _size)_elem[lo++] = _elem[hi++];
	_size = lo; // _size = hi-(hi-lo)
	//shrink() 如果需要
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T>
Rank Vector<T>::find(T const&e,Rank lo,Rank hi)const
{
	//从后向前扫描，因为重复元素需要返回Rank最大者
	while((lo < hi--) && e != _elem[hi]; // hi--不会被lo<hi的结果短路
	return hi; //如果成功返回的是命中的元素下标，否则返回的是lo-1(lo<hi表示失败)
}

template <typename T>
int Vector<T>::deduplicate(){//繁琐版 O(n^2)
	int oldSize = _size;
	int i = 1;
	while(i < _size){
		(find(_elem[i],0,i) < 0) ? i++ :remove(i);
	}
	return oldSize - _size;
}

//遍历
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit)//函数对象
{
	for(int i = 0;i < _size;i++)visit(_elem[i]);
}
template <typename T>
struct Increase{//函数对象：通过重载操作符"()"实现
	virtual void operator()(T &e){ e++; }
}
template <typename T>
void increase(Vector<T> & V){
	V.traverse(Increase <T>());
}



int main() {
	cout << "Hello!" << endl;
	system("pause");
}


