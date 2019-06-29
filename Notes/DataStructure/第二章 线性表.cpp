#include <iostream>
#define maxSize 100;

//顺序表的创建
typedef struct
{
    int data[maxSize];
    int length;
}Sqlist;

//顺序表的操作
//查找
int findElem(Sqlist L,int x){
    int i;
    for(int i = 0;i< L.length)
    {
        if(x < L.data[i])
        {
            return i;
        }
    }
    return i;
}

void insertElem(Sqlist &L,int x)
{
    int p,i;
    p = findElem(L,x);
    for(i = L.length-1;i>=p;--i)
        L.data[i+1] = L.data[i];
    L.data[p] = x;
    ++(L.length);
}

//单链表
typedef struct LNode
{
    int data;
    struct LNode *next;
};

//双向链表
typedef struct DLNode
{
    int data;
    struct DLNode *prior;
    struct DLNode *next;
};

//创建节点
LNode *A = (LNode*)malloc(sizeof(LNode));



