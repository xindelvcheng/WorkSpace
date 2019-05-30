# Android新特性
## Fragment
可以理解为Activity的一部分
### 1.Fragment入门
#### （1）自定义类继承Fragment
```
public class MyFragment1 extends Fragment {
    @Override
    //当系统画UI的时候调用，可以让Fragment显示自己的布局
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment1,null);
        return view;
    }
}
```
>不能在Fragment里通过添加onclick()属性绑定按钮点击事件，应该通过id获得这个按钮然后通过代码绑定事件
#### （2）创建Fragment的布局文件
#### （3）在Activity的布局文件中的布局下添加<fragment/>节点
```
<fragment
    android:name="com.xindelvcheng.appdemo1.MyFragment1"
    android:layout_width="wrap_content"
    android:layout_height="match_parent"
    android:id="@+id/fg1" />
```
### 2.动态加载Fragment
```
FragmentManager fragmentManager = getFragmentManager();
FragmentTransaction beginTransaction = fragmentManager.beginTransaction();
beginTransaction.replace(android.R.id.content/*代表当前窗体，可以改成自定义布局的id*/, new MyFragment1());
beginTransaction.commit();
```
### 3.低版本兼容
用`android.support.v4.app.Fragment`包，要继承v4包下的FragmentActivity，获取FragmentManager的方法变为`getSupportFragmentManager()`
### 4.Fragment通信
使用Fragment时
```
fragmentTransaction.replace(R.id.ll, new WechatFragment(),"f1");
```
在Fragment中
```
Fragment f1 = getActivity().getFragmentManager().findFragmentByTag("f1");
```
>Fragment依附于Activity，Activity是Fragment沟通的桥梁
### 5.防止重复加载的Fragment（兼容写法）
```
fragmentManager = getSupportFragmentManager();
FragmentTransaction beginTransaction = fragmentManager.beginTransaction();
BaseFragment lastFragment = mBaseFragement.get(lastPosition);
BaseFragment fragment = mBaseFragement.get(postion);
if (!fragment.isAdded()) {
    beginTransaction.add(R.id.fl_content,fragment);
}
if (lastPosition != postion) {
    beginTransaction.hide(lastFragment);
}
beginTransaction.show(fragment);
beginTransaction.commit();
```
在AndroidManifest.xml中配置屏蔽横竖屏切换，键盘隐藏，屏幕大小改变等事件带来的Activity重新创建影响
```
<activity android:name=".MainActivity" android:configChanges="orientation|keyboardHidden|screenSize"></activity>
```