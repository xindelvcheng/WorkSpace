# Android中的服务
## Android中的进程
当应用程序运行时，系统会创建一个Linux进程和一个主线程，四大组件全都运行在主线程上
### 进程的优先级
决定进程被保留和被杀死的优先级，从高往低依次有五个等级：
-   Foreground process  
前台进程，如调用`onResume()`的Activity，正在和用户交互，优先级最高
-   Visible process  
可视进程，如失去焦点已执行`OnPause()`的Activity
-   Service process  
开启了服务的进程，如播放音乐，下载文件
-   Background process  
Activity已执行`OnStop()`，但是并没有销毁
-   Empty process  
不维持任何组件运行，Activity已销毁，优先级最低，最容易被杀死，但是可能保留以加速下次打开
>Android中在app中按返回主页是使其变成后台进程，多次按返回是使其变成空进程
## Service入门
定义四大组件的形式都是一样的。
### 定义一个Service类
```
public class DemoService extends Service {
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return super.onStartCommand(intent, flags, startId);
    }
    
    @Override
    public void onDestroy() {
        super.onDestroy();
    }
}
```
### 在AndroidManifest.xml中配置
```
<service android:name=".DemoService" />
```
>从继承关系上看，Service是Activity的大伯
### 开启Service
```
startService(new Intent(this, DemoService.class));
```
>Intent是安卓四大组件的纽带
### 停止Service
```
stopService(new Intent(this, DemoService.class));
```
### Start方式开启服务总结：
1. 服务第一次开启会调用`onCreate()`和`onStartCommand()`，之后开启只会调用`onStartCommand()`
2. 服务会在后台长期运行，除非手动停止
3. 能在设置“正在运行”中找到
>服务和在Activity中开启子线程的区别就是这里，子线程容易在Activity销毁后被回收。
## 案例 电话窃听器
### 通话状态监控模板代码
通过`getSystemService()`获取TelephonyManager对象，调用`listen()`注册监听事件
```
TelephonyManager tm = (TelephonyManager) getSystemService(TELEPHONY_SERVICE);
tm.listen(new PhoneStateListener() {
    @Override
    public void onCallStateChanged(int state, String phoneNumber) {
        switch (state) {
            case TelephonyManager.CALL_STATE_IDLE:
                break;
            case TelephonyManager.CALL_STATE_OFFHOOK:
                System.out.println("接听");
                break;
            case TelephonyManager.CALL_STATE_RINGING:
                System.out.println("响铃中");
                break;
        }
    }
}, PhoneStateListener.LISTEN_CALL_STATE);
```
### MediaRecorder示例代码
```
MediaRecorder recorder = new MediaRecorder();
recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
recorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
recorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
recorder.setOutputFile(PATH_NAME);
recorder.prepare();
recorder.start();   // Recording is now started
...
recorder.stop();
recorder.reset();   // You can reuse the object by going back to setAudioSource() step
recorder.release(); // Now the object cannot be reused
```
### 需要的权限
```
<uses-permission android:name="android.permission.READ_PHONE_STATE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.RECORD_AUDIO" />
```
### 可以通过广播接收者让手机启动时开启服务
#### AndroidManifest.xml中配置
-   权限
```
<uses-permission android:name="android.permission.RECEIVE_BOOT_COMPLETED" />
```
-   广播接收者
```
<receiver android:name=".BootReceiver">
    <intent-filter>
        <action android:name="android.intent.action.BOOT_COMPLETED" />
    </intent-filter>
</receiver>
```
## 使用Service注册特殊广播接收者
完整代码
```
public class DemoService extends Service {


    private BroadcastReceiver receiver;

    @Override
    public void onCreate() {
        super.onCreate();
        receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                if (Objects.equals(intent.getAction(), "android.intent.action.SCREEN_OFF")) {
                    System.out.println("锁屏");
                } else if (Objects.equals/*用这个方法不会空指针*/(intent.getAction(), "android.intent.action.SCREEN_ON")) {
                    System.out.println("解锁");
                }
            }
        };
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("android.intent.action.SCREEN_OFF");
        intentFilter.addAction("android.intent.action.SCREEN_ON");
        registerReceiver(receiver, intentFilter);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        unregisterReceiver(receiver);
    }
}
```
## 使用bindService方式绑定服务
### 绑定服务
```
public void bindService(View view) {
    Intent intent = new Intent(this,DemoService.class);
    conn = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {System.out.println("服务连接");}
        @Override
        public void onServiceDisconnected(ComponentName name) {System.out.println("服务断连");}
    };
    bindService(intent, conn, BIND_AUTO_CREATE);
}
```
### 解绑服务
```
unbindService(conn);
```
### bind方式绑定服务特点
-   绑定服务的Activity销毁时，服务也销毁
-   当服务的`onBind()`方法返回值为null时，onServiceConnected方法不执行
-   Activity不能一个服务绑定两次，也不能解绑多次（解绑多次会报错）
-   不能在设置“正在运行”中找到
### 为什么需要bindService？
如果想要调用Service类中的方法，是不能够通过`new Service().method()`的方式来调用的，这样的对象是没有上下文的，如调用`                Toast.makeText(getApplicationContext(), "", Toast.LENGTH_SHORT).show();
`会报空指针异常，因为`getApplicationContext()`获取上下文是null
### 调用服务内的方法
Service的`onBind()`会返回一个IBinder，在Service类中自定义Binder（IBinder默认实现子类）扩展自己需要外面调用的方法，服务的绑定者可以在`onServiceConnected()`回调中获得这个Binder对象，并使用其中的方法。
#### 1.自定义类继承Binder，调用Service的方法
```
public class MyBinder extends Binder{
    public void callMethod(){
        DemoService.this.method();
    }
}
```
#### 2.返回MyBinder对象
```
@Override
public IBinder onBind(Intent intent) {
    return new MyBinder();//返回null则onServiceConnected不执行
}
```
#### 3.在回调方法中获得这个MyBinder对象
```
@Override
public void onServiceConnected(ComponentName name, IBinder service) {
    System.out.println("服务连接");
    MyBinder myBinder = (MyBinder) service;
    myBinder.callMethod();
}
```
### 通过接口调用服务内的方法
由于返回的是IBinder对象，接受者可以调用对象里的所有方法，不符合封装性，通过接口可以暴露想暴露的方法，隐藏不想暴露的成员。
#### 定义接口，声明想暴露的方法
```
public interface IService {
    public void publicMethod();
}
```
#### 自定义Binder
```
public class MyBinder extends Binder implements IService{
    @Override
    public void publicMethod() {
        System.out.println("Public Method");
    }
    
    //不会被返回的IService对象调用
    public void privateMethod(){
        System.out.println("Private Method");
    }
}
```
#### 接受Binder（声明为IService，多态）
```
@Override
public void onServiceConnected(ComponentName name, IBinder service) {
    System.out.println("服务连接");
    IService myBinder = (IService) service;
    myBinder.publicMethod();
  //myBinder.privateMethod(); 报错
}
```
### 混合方式开启服务
需求：既需要服务在后台长期运行，又要调用其中的方法。
1. 先调用startService开启服务，能保证服务在后台长期运行
2. 通过bindService获取Binder，调用其中的方法
3. 调用unbindService解绑服务（服务并不会销毁）
## aidl介绍
aidl:安卓接口定义语言，用于解决进程间通信的问题
### 本地服务和远程服务
-   本地服务：运行在自己应用里的服务
-   远程服务：运行在其他应用里的服务
</br>
### 通过aidl完成进程间通信IPC
#### 1. 将IService.java改名为IService.aidl
-   去掉public（aidl就是为了数据共享）
-   系统会自动生成IService.java文件
#### 2.要调用IService中方法的应用要copy一份IService.aidl，同时要先创建一个包，保证IService在两个应用的全路径一致
#### 3.定义的中间人对象直接继承Stub
#### 4.在客服端获取中间人对象
```
IMyAidlInterface.Stub.asInterface(service);
```
### 应用场景
调用支付宝支付接口