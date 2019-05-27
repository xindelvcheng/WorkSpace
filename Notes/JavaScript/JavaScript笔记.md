# JavaScript笔记
 
[TOC]
 
## 入门
 
### 1. 书写位置
 
`<script>`标签可以放在任意位置，但要注意执行顺序，如果在html的上面，没有执行到DOM就获取元素是获取不到的
 
### 2. 运算符
 
- 使用`a= +"123"`的方式进行类型转换，按照字面值，如果字面值不是数字则转为NaN,NaN和任何数运算都是NaA
- 比较运算符可以对字符串使用，按照字典顺序依次比较。如果运算的变量类型不同，转为数字再比较。所以`"123" == 123`为true，但`"123" === 123`为false
- `0`和`NaN`转false，其他数字转true；`""`转false,其他字符串转true；`null`和`undefined`为false，所有对象都为true。所以js中可以`if(obj){}`判空
 
### 3. 特殊语法
 
js一个语句结束可以不使用`;`，定义变量可以不适用var但是不建议
 
### 4. 对象
 
#### (1). Function对象
 
定义函数
 
```js
function fun(a,b){
    return a+b;
}
var fun2 = function(a,b){
    return a+b;
}
```
 
> fun和fun2就是对象，是有属性的，如`fun.length`输出fun的参数数量
 
调用函数
 
```javascript
fun(1,2)
```
 
<font color='red'>JavaScript中函数的调用只和函数名有关，和参数列表无关</font>，如对于`function fun(a,b){return a}`调用使用`fun()`,`fun(1,2)`,`fun(1)`,`fun(1,2,3)`都可以。实际上方法对象封装了一个arguments数组，包含所有参数，如
 
```js
function fun(){
    res = 0
    for(var i = 0;i<arguments.length;i++){
        res+=arguments[i]
    }
    return res}
```
 
#### (2). Array对象
 
##### 1.创建
 
```js
var arr = [1,2,3]
var arr = new Array(1,2,3)
var arr = new Array(3)
```
 
> JavaScript中的数组类型和长度可变，和python中list用法一样。但下标越界自动填充undefined不会报异常
 
```js
var arr = [1,2,3]
arr[10] = 9
for(var i = 0;i < arr.length;i++){
    alert(arr[i])
}
```
 
##### 2.方法
 
push
 
```js
//和python中列表的append一样
arr.push(4)
```
 
 
 
join
 
```js
//和python中字符串的join功能相同，但使用对象相反
str = arr.join("")
```
 
#### (3). Date对象
 
```js
var data = new Date()
console.log(data.toLocaleString())
console.log(data.getTime())
```
 
#### (4). Math对象
 
内置对象。
 
```js
Math.random() //产生0~1之间的随机数
ceil/floor/rount //向上取整/向下取整/四舍五入
```
 
#### (5). RegExp对象
 
正则表达式对象
 
##### 1.规则
 
- 单个字符:[]
  - \d [0-9]
  - \w [a-zA-Z0-9]
- 量词符号:
  - ?：出现0次或1次
  - *：出现0次或多次
  - +：出现1次或多次
  - {m,n}：出现[m,n]次
    - {,n}：出现最多n次
    - {m,}：最少m次
- 开始和结束符号
  - ^：开始
  - $：结束
 
##### 2.使用
 
- 创建
 
  ```js
  var reg = /"正则表达式"/
  var reg = new RegExp("正则表达式")
  ```
 
- 方法
 
  ```js
  var flag = reg.test("待测试字符串") //检测刺符传是否满足正则表达式
  ```
 
  #### (4). Global对象
 
  Global中封装的方法不需要对象直接使用函数名就可以使用
 
  ```js
  encodeURI("你好"); //URL编码
  decodeURI("%E4%BD%A0%E5%A5%BD") //URI解码
 
  //将://等都进行编码
  encodeURIComponent("https://www.baidu.com/s?ie=UTF-8&wd=locale")
  decodeURIComponent("")
 
  var num = parseInt("123abc") //num=123,注意检查是否是数字，将前面的数字部分转为number
 
  isNaN() //NaN和NaN比较也是false
 
  eval() //将字符串转为代码执行
 
 
  ```
 
 
 
## BOM
 
Browser Object Model 浏览器对象模型
 
- Navigator：浏览器对象
- **Window：窗口对象**
- Location：地址栏对象
- History：历史记录对象
- Screen：显示器屏幕
 
### 1. Window对象
 
#### (1). 创建
 
    不需要创建，使用window，window也可以使用，直接`方法名()`
 
#### (2). 方法
 
##### 1. 弹出框
 
- alert()
- confirm() //确定返回true，取消返回false
- prompt() //返回输入的值
 
##### 2. 与打开关闭有关的方法
 
- `var newWindow = open("https://www.baidu.com")`
- close() //谁调用关谁`newWindow.close()`
 
##### 3. 与定时器有关的方法
 
- setTimeout()
 
  （1）只会执行一次
 
  （2）参数：1.代码片段或方法对象 2. 延迟时间毫秒值
 
  `var id = setTimeout(fun,1000)`
 
- clearTimeout()
 
  `clearTimtout(id)`
 
- setInterval()
 
- clearInterval()
 
#### (3). 属性
 
##### 1. 获取其他BOM对象
 
history
 
location
 
Navigator
 
Screen
 
##### 2. 获取DOM对象
 
document
 
> document.getElementById() 即window.document.getElementById()
 
### 2. Location对象
 
#### (1). 创建
 
window.location
 
location
 
#### (2). 方法
 
reload() //属性
 
#### (3). 属性
 
href //设置或返回完整的url
 
> `href="javascript:void(0);"`a标签不跳转
 
### 3. History对象
#### (1). 创建
 
window.history
 
history
 
#### (2). 方法
 
back()
 
forward()
 
go(1) //加载历史记录中的某个页面1，-1
 
#### (3). 属性
 
length //当前窗口历史列表中的URL数量
 
## DOM
 
Document Object Model文档对象模型
 
访问和操作HTML文档
 
### 1. 核心DOM模型
 
#### (1). Document对象
 
##### 方法
 
获取Element对象
 
- getElementById()
- getElementsByTagName()
- getElementsByClassName()
- getElementsByName()
 
创建元素
 
- createElement("table")
 
#### (2). Element对象
 
##### 方法
 
- setAttribute()
 
- removeAttribute()
 
 
 
#### (3). Node对象
 
所有DOM对象都可以被认为是一个节点
 
##### 方法
 
- appendChild()
- removeChild()
- replaceChild()
 
可以createElement()创建一个元素，setAttribute() 设置一个id，通过css id选择器给一个样式，然后appendChild()添加到父节点
 
##### 属性
 
- parentNode 获取父节点
 
### 2. HTML DOM
 
#### (1). innerHTML
 
=
 
+=
 
#### (2). 属性
 
div.style.border = "1px solid red"
 
#### (3).控制样式
 
1. 定义好类选择器css
2. div.className = "d1"
 
## 事件
 
#### (1). 常见事件
 
| 属性                                                         | 此事件发生在何时...                  | 常见用法                   |
| :----------------------------------------------------------- | :----------------------------------- | -------------------------- |
| [onabort](http://www.w3school.com.cn/jsref/event_onabort.asp) | 图像的加载被中断。                   |                            |
| [onblur](http://www.w3school.com.cn/jsref/event_onblur.asp)  | 元素失去焦点。                       | 表单校验                   |
| [onchange](http://www.w3school.com.cn/jsref/event_onchange.asp) | 域的内容被改变。                     |                            |
| [onclick](http://www.w3school.com.cn/jsref/event_onclick.asp) | 当用户点击某个对象时调用的事件句柄。 |                            |
| [ondblclick](http://www.w3school.com.cn/jsref/event_ondblclick.asp) | 当用户双击某个对象时调用的事件句柄。 |                            |
| [onerror](http://www.w3school.com.cn/jsref/event_onerror.asp) | 在加载文档或图像时发生错误。         |                            |
| [onfocus](http://www.w3school.com.cn/jsref/event_onfocus.asp) | 元素获得焦点。                       |                            |
| [onkeydown](http://www.w3school.com.cn/jsref/event_onkeydown.asp) | 某个键盘按键被按下。                 |                            |
| [onkeypress](http://www.w3school.com.cn/jsref/event_onkeypress.asp) | 某个键盘按键被按下并松开。           |                            |
| [onkeyup](http://www.w3school.com.cn/jsref/event_onkeyup.asp) | 某个键盘按键被松开。                 |                            |
| [onload](http://www.w3school.com.cn/jsref/event_onload.asp)  | 一张页面或一幅图像完成加载。         | window.onload=function(){} |
| [onmousedown](http://www.w3school.com.cn/jsref/event_onmousedown.asp) | 鼠标按钮被按下。                     |                            |
| [onmousemove](http://www.w3school.com.cn/jsref/event_onmousemove.asp) | 鼠标被移动。                         |                            |
| [onmouseout](http://www.w3school.com.cn/jsref/event_onmouseout.asp) | 鼠标从某元素移开。                   |                            |
| [onmouseover](http://www.w3school.com.cn/jsref/event_onmouseover.asp) | 鼠标移到某元素之上。                 |                            |
| [onmouseup](http://www.w3school.com.cn/jsref/event_onmouseup.asp) | 鼠标按键被松开。                     |                            |
| [onreset](http://www.w3school.com.cn/jsref/event_onreset.asp) | 重置按钮被点击。                     |                            |
| [onresize](http://www.w3school.com.cn/jsref/event_onresize.asp) | 窗口或框架被重新调整大小。           |                            |
| [onselect](http://www.w3school.com.cn/jsref/event_onselect.asp) | 文本被选中。                         |                            |
| [onsubmit](http://www.w3school.com.cn/jsref/event_onsubmit.asp) | 确认按钮被点击。                     |                            |
| [onunload](http://www.w3school.com.cn/jsref/event_onunload.asp) | 用户退出页面。                       |                            |
 
```js
button = document.findElementById("su")
button.onclick = function(event){
    alert("Hello!")
}
```
 