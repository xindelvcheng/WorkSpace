# Activity
## Activity入门
### 创建一个类继承android.app.Activity,它就是一个Activity
```
public class TestActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test);//加载布局
    }
}
```
### 在AndroidManifest.xml中配置Activity
```
<!--所有的Activity都要在清单文件中配置，label为图标名，icon为图标（默认为application下的label和icon）-->
<activity android:name=".MainActivity"
    android:icon="@drawable/screenshot_1"
    android:label="一个页面">
    <!--配置程序入口，如果有多个这样声明的<intent-filter>那么会在手机上生成几个应用图标-->
    <intent-filter>
        <action android:name="android.intent.action.MAIN" />

        <category android:name="android.intent.category.LAUNCHER" />
    </intent-filter>
</activity>
```
除了默认生成的入口，其他Activity一般都不需要配置，只要声明
```
<activity android:name=".TestActivity"></activity>
```
### 设置意图跳转到Activity
隐示意图，通过设置一组动作或数据
```
//隐示Intent的设置根据AndroidManifest.xml中的IntentFilter（同一个Activity可以配置多个IntentFilter)
Intent intent = new Intent();
intent.setAction("android.intent.action.Test");
intent.addCategory("android.intent.category.DEFAULT");
intent.setDataAndType(Uri.parse("data:123"), "aa/bb");
startActivity(intent);
```
显示意图，指定Android应用的包名（在AndroidManifest.xml中）和要跳转到的Activity的类的全路径（包名+类名）
```
Intent intent = new Intent();
intent.setClassName("com.xindelvcheng.androidapplicationdemo1", "com.xindelvcheng.androidapplicationdemo1.TestActivity");
startActivity(intent);
```
或者在构造函数中传入上下文和类的.class对象
```
Intent intent = new Intent(this, TestActivity.class);
startActivity(intent);
```
总结
-   一般跳转到自己应用的界面时使用显示意图  
-   跳转到其他应用的界面（往往是系统系统应用）时使用隐示意图
-   显示意图更加安全，如果不指定IntentFilter，其他应用是跳转不过来的
### 通过Intent携带数据跳转
通过谷歌封装的方法，在Intent里封装数据（内部通过Bundle，封装的HashMap）
```
intent.putExtra("name", "zhangsan");
```
然后在跳转到的Activity里获取
```
Intent intent = getIntent();
String name = intent.getStringExtra("name");
//String name = (String) intent.getExtras().get("name");
System.out.println(name);
```
通过隐示意图（没人用），在设置了Intent设置了数据跳转之后在跳转到的Activity可以获取这个Intent和其中的数据
```
Intent intent = getIntent();
Uri data = intent.getData();
System.out.println(data);
```
### 跳转之后返回携带数据的Intent
开启时要使用`startActivityForResult()`
```
startActivityForResult(intent,1);
```
跳转到的那个页面关闭时
```
Intent intent = new Intent();
intent.putExtra("key", value);
setResult(10,intent);
finish() //关闭当前Activity
```
页面返回时开启者`onActivityResult()`被调用，通过resultCode或requestCode判断是从哪一个页面返回
```
@Override
protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
    super.onActivityResult(requestCode, resultCode, data);
}
```
### 案例：短信发送
```
lv1.setOnItemClickListener(new AdapterView.OnItemClickListener() {
    @Override
    public void onItemClick(AdapterView<?> parent/*ListView*/, View view/*Item*/, int position/*被点击条目的位置*/, long id/*谷歌提供，一般不使用*/) {
        String content = objects[position];
        Intent intent = new Intent();
        intent.setAction("android.intent.action.SEND");
        intent.setType("text/plain");
        intent.putExtra("sms_body", content);
        startActivity(intent);
    }
});
```
其实发送短信可以使用谷歌提供的API
```
SmsManager smsManager = SmsManager.getDefault();
smsManager.sendTextMessage(number,null,content,null,null);
```
当短信很长时（中文超过70，英文超过140）
```
SmsManager smsManager = SmsManager.getDefault();
ArrayList<String> sms = smsManager.divideMessage(content);
for (String div : sms) {
    smsManager.sendTextMessage(number,null,div,null,null);
}
```
需要添加权限
```
<uses-permission android:name="android.permission.SEND_SMS" />
```
## Activity生命周期
### onCreate()
Activity第一次被创建的时候
### onDestroy()
Activity被销毁时调用
### onStart()
当Activity可视
### onStop()
当Activity不可视
### onResume()
当Activity获得焦点
### onPause()
当Activity失去焦点
### onRestart()
当Activity从不可见到可见
### 在AndroidManifest.xml设置Activity横竖屏
```
//竖屏
android:screenOrientation="portrait"
//横屏
android:screenOrientation="landscape"
```
横竖屏切换会销毁Activity然后重新创建。
## 任务栈
用来完成Activity的后退（最先开启的页面后退最多次到）。应用程序的退出是任务栈清空了。
## Activity的启动模式
### Standard
标准模式
### SingleTop
处于任务栈顶端的页面不能跳转到自己。应用：浏览器的书签页，不会重复创建
### singleTask
一个任务栈这个Activity只能有一个。应用：浏览器页面，不会重复申请内存。
### singleInstance
创建Activity自己的任务栈，且那个任务栈中只有一个实例。应用：电话被call页，整个操作系统只会有一个实例。
