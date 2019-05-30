## 一. 项目目录结构
-   AndroidManifest.xml
安卓的清单文件，定义四大组件
-   src
源代码
-   gen
自动生成文件
    -   R.java
    自动生成的文件，包含id，用于索引
        ```
        //在*.java中索引
        EditText num_edit = (EditText) findViewById(R.id.editText1);
        //在*.xml中索引,@代表R文件
        @drawable/ic_launcher
        ```
-   assets
资源文件，不会打包
-   bin
打包完成的文件，包括apk文件和dex文件
-   res
资源文件，打包并生成R文件内容
    -   drawable-hdpi等
    图片资源
    -   layout
    布局资源
    -   values字符串
## 二. 入门案例：电话拨号器
>就像Qt中所有控件都是Widget，安卓中所有控件都是View
###   按钮点击事件
1.匿名内部类
```
call_button.setOnClickListener(new OnClickListener() {
    @Override
    public void onClick(View v) {
    }
}
```
2.让MainActivity实现OnclickListener重写方法，传入参数this：`call_button.setOnClickListener(this);`。当界面中有多个同功能按钮比较方便  
3.像xaml一样添加
```
//activity_main.xml中添加
android:onClick="click"
...
//MainActivity.java中添加
@Override
public void click(View v){
    switch(v.getId()){
        case R.id.A:
            break;
        case R.id.B:
            break;
    };
    ...
}
```
>click的签名要注意。它是反射实现的（`getMethod(handlerName,View.class)`），所以参数要写View v
-   使用Intent实现拨号功能
```
Intent intent = new Intent();
intent.setAction(Intent.ACTION_CALL);
intent.setData(Uri.parse("tel:"+number));
startActivity(intent);
```
###   添加权限
在AndroidManifest.xml中添加`<uses-permission android:name="android.permission.CALL_PHONE"/>`
###   Toast  
显示少量信息的提示
>如何看文档？1. 看类的简介 2.看类的构造方法 3. 看类的方法
```
Toast.makeText(MainActivity.this, "号码不能为空", Toast.LENGTH_LONG).show();
```
>mskText()为静态方法，直接调用；不能忘记show();
## 布局
在layout文件夹下新建布局文件，新建AndroidXmlFile选择RootElemnt为LinearLayout
### LinearLayout
线性布局,相当于panelstack之类的,有权重的概念，相对的决定组件占用的长度 
```
android:layout_weight="1"
```
默认是水平布局，可以修改为垂直布局
```
android:orientation="vertical"
```
### RelativeLayout
相对布局
默认的布局，用id指定新的组件和原有组件位置关系(在某个组件的右边、下边等)
```
<EditText
        android:id="@+id/editText1"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_alignLeft="@+id/textView1"
        android:layout_below="@+id/textView1"
        android:ems="10" />

    <Button
        android:id="@+id/button1"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_alignRight="@+id/textView1"
        android:layout_below="@+id/editText1"
        android:layout_marginTop="17dp"
        android:text="拨打" />
```
相对关系指定有以下类型：
-    `android:layout_above="@+id/1"` 指定与某控件的相对位置
-    `android:layout_alignParentRight="true"` 指定与父布局（组件）的关系
-    `android:layout_alignBottom="@+id/2"` 指定与某组件的对齐关系
>线性布局和相对布局是安卓开发用的较多的
### FrameLayout
一层层显示，比如播放视频窗口的播放按钮
### TableLayout
表格布局，相当于Qt的网格布局，不过安卓开发用的少,在TableRow标签中定义组件
### AbsoluteLayout
绝对布局，Qt，WPF，安卓中都用的少
### 通用属性
-   android:layout_gravity="center" 控件居中
-   android:gravity="center" 内容居中
-   android:layout_margin="10dp" 外边距
-   android:padding="10dp" 内边距
### 动态添加删除控件
```
ProgressBar pb = new ProgressBar(this);
pb.setMax(100);
pb.setProgress(50);
ll_1.addView(pb);
ll_1.removeAllViews();
```
>与进度相关的方法都可以在子线程中直接调用，已经封装好了消息机制
## 安卓中的单位
-  dp 常用
-  px 像素，基本不用
-  sp 字体
>AndroidStudio快捷键Ctrl+Alt+F抽取局部变量
## 控件
### ImageView
-   setImageBitmap(Bitmap)
-   setBackgroundResource(R.id.img1);
>src和background的区别在于src是有"padding"的，而背景是完全填充的
### RadioButton
RadioButton要包裹在RadioGroup中使用，在布局文件中：
```
<RadioGroup
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="horizontal">

    <RadioButton
        android:id="@+id/radioButton"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_weight="1"
        android:text="RadioButton" />

    <RadioButton
        android:id="@+id/radioButton2"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_weight="1"
        android:text="RadioButton" />
</RadioGroup>
```
在Java代码中
```
int checkedRadioButtonId = rg1.getCheckedRadioButtonId();
switch (checkedRadioButtonId) {
    case R.id.radioButton:
        Toast.makeText(this, "你选择了1", Toast.LENGTH_SHORT).show();
    case R.id.radioButton2:
        Toast.makeText(this, "你选择了2", Toast.LENGTH_SHORT).show();
}
```
### EditText
```
String content = et.getText().toString();
if (TextUtils.isEmpty(content)) {
    Toast.makeText(getApplicationContext(), content, Toast.LENGTH_SHORT).show();
}
```
### SeekBar
```
sb.setMax(player.getDuration());
sb.setProgress(player.getCurrentPosition());

sb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        //进度改变调用
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {
        //开始拖动调用
    }
    
    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        //拖动停止调用
    }
});
```
### AutoCompleteTextView
布局文件中
```
<AutoCompleteTextView
    android:id="@+id/actv"
    android:layout_width="match_parent"
    android:layout_height="wrap_content"
    android:completionThreshold="1"/>
```
代码中，和ListView一样，需要数据适配器
```
private String[] list = new String[]{"Hello！", "Hi", "Haha","Hehe","Hsldkjflskdf"};

@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    AutoCompleteTextView actv = findViewById(R.id.actv);
    ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,android.R.layout.simple_dropdown_item_1line,list);
    actv.setAdapter(adapter);
}
```

## 其他
```
SystemClock.sleep(1000/*ms*/); //Thread.sleep()
SystemClock.uptimeMillis()  //手机开机时间
```