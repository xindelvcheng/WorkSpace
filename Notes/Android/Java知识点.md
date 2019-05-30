# Java知识点
## 语法
-   内部类只能访问外部final成员
-   Java中没有像Python中那样的函数默认值参数，但是可以通过重载完成同样的效果
-   static代码段
    ```
    static
    {
        sURIMatcher.addURI("com.xindelvcheng.provider", "query", QUERYSUCCESS);
    }
    ```
    会在类加载的时候执行，且只会被执行一次
## 多线程
### 返回代码段正在被哪个线程调用的信息
```
Thread.currentThread().Id()
```
## 文件读写
### 流转换为字符串
内存输出流 ByteArrayOutputStream
```
ByteArrayOutputStream baos = new ByteArrayOutputStream();
int len = -1;
byte[] buffer = new byte[1024];
while ((len = in.read(buffer)) != -1) {
    baos.write(buffer, 0, len);
}
in.close();
System.out.println("haha");
return new String(baos.toByteArray());
```
>使用`new String()`而不是直接`baos.toString()`是因为`new String()`可以指定编码为"utf-8"
### 随机读写
RandomAccessFile，在任意位置读写文件，并提供不写入磁盘缓存直接立即与存储体同步的方法
```
raf.seek(pos);
raf.write(buffer,0,len);
```
>HTTP协议中通过添加请求头`Range`来返回一段数据，请求成功的状态码为206,与RandomAccessFile配合完成断点续传
## 面向对象
### 创建一个静态内部类
```
AlertDialog.Builder builder = new AlertDialog.Builder(this);
```
## 程序的健壮性
-   使用`Objects.equals(A,B)`代替`A.equals(B)`来防止空指针异常