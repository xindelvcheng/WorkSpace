- ### <font color="red">C++编译器是如何管理类的？</font>
![image](https://s1.ax1x.com/2018/05/13/CDEDFx.png)

- ### const修饰的是什么？
```
class Test{

    void Op(int a,int b) const
    {
        
    }     
}
```
const写在void前面，Op前面也没问题，因为只要写了const，C++编译器就认为它修饰的是隐藏的this指针`Test const *this`==>`const Test const *this`
>把成员函数转成全局函数实际就是多了一个参数this指针

 