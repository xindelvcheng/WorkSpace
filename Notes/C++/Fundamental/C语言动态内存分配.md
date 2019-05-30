### 传统数组的缺陷
数组在定义时内存长度固定，并且不能由程序员手动释放，只能在函数执行完成之后被自动释放，因此也不能跨函数使用数组

### malloc函数
```
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>	

void fun(int *q) {
	*q = 100;
}

int main() {
	int *p = (int*)malloc(4);//返回是void *类型的指针，不转型是不能使用的实际上是存储了分配内存空间的首地址,转为int*告诉编译器它是一个指向int的指针，*p取值的时候每四个字节当做一个int使用
	fun(p);
	printf("%d\n", *p);

	system("pause");
	return 0;
}
```
### 二级指针
```
#include<iostream>

using namespace std;

struct Teacher {
	char name[64];
	int age;
};

int getTeacher(Teacher** p) {
	Teacher *temp = NULL;
	if (p==NULL)
	{
		return -1;
	}
	temp = (Teacher*)malloc(sizeof(Teacher));
	if (temp==NULL)
	{
		return -2;
	}
	temp->age = 33;
	*p = temp;
}

int main() {
	Teacher *pT1 = NULL;
	getTeacher(&pT1);	//传入一个指针地址，所以函数中需要用二级指针
	cout << pT1->age << endl;
	system("pause");
}
```