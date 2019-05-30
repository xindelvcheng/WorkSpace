# Android中的动画
## 补间动画
又称view动画
### 1.透明动画
```
ImageView iv = findViewById(R.id.iv);
AlphaAnimation aa = new AlphaAnimation(1.0f, 0.0f);
aa.setDuration(1000);
aa.setRepeatCount(1);
aa.setRepeatMode(Animation.REVERSE);
iv.startAnimation(aa);
```
### 2.旋转动画
```
RotateAnimation ra = new RotateAnimation(0,360,Animation.RELATIVE_TO_SELF,0.5f,Animation.RELATIVE_TO_SELF,0.5f);
ra.setDuration(1000);
ra.setRepeatMode(0);
iv.startAnimation(ra);
```
### 3.缩放动画
```
ScaleAnimation sa = new ScaleAnimation(1.0f,2.0f,1.0f,2.0f,Animation.RELATIVE_TO_SELF,0.5f,Animation.RELATIVE_TO_SELF,0.5f);
sa.setDuration(1000);
iv.startAnimation(sa);
```
### 4.位移动画
```
TranslateAnimation ta = new TranslateAnimation(Animation.RELATIVE_TO_PARENT, 0.0f,Animation.RELATIVE_TO_PARENT, 0.2f,
        Animation.RELATIVE_TO_PARENT, 0.0f,Animation.RELATIVE_TO_PARENT,0.2f);
ta.setDuration(1000);
ta.setFillAfter(true);//设置动画结果保留，空间停在位移后的位置
iv.startAnimation(ta);
```
>补间动画并不会真正改变控件坐标（哪怕看起来改变了位置）
### 5.执行多个动画
```
AnimationSet set = new AnimationSet(true);
set.addAnimation(alphaAnimation);
set.addAnimation(scaleAnimation);
iv.startAnimation(set);
```
### 6.使用xml方式创建补间动画
#### 在res下创建anim文件夹，创建动画文件
```
<?xml version="1.0" encoding="utf-8"?>
<alpha xmlns:android="http://schemas.android.com/apk/res/android"
    android:fromAlpha="1.0"
    android:toAlpha="0.0">
</alpha>
```
#### 在Activity中开启动画
```
Animation animation = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.animation_alpha);
animation.setDuration(1000);
iv.startAnimation(animation);
```
#### 旋转
```
<?xml version="1.0" encoding="utf-8"?>
<rotate xmlns:android="http://schemas.android.com/apk/res/android"
    android:pivotX="50%"        //相对自己50%
    android:pivotY="50%p"       //相对父布局50%
    android:fromDegrees="0"
    android:toDegrees="360">
</rotate>
```
### 组合动画
```
<?xml version="1.0" encoding="utf-8"?>
<set xmlns:android="http://schemas.android.com/apk/res/android">
    <alpha android:fromAlpha="1.0" android:toAlpha="0.0"/>
    <rotate android:fromDegrees="0" android:toDegrees="360" android:pivotX="50%" android:pivotY="50%"/>
</set>
```
## 属性动画
实际开发中用的不多。它会改变控件的真实坐标
```
//iv.setTranslationX(translationX);
ObjectAnimator oa = ObjectAnimator.ofFloat(iv, "translationX", 10, 150, 20/*····*/);
oa.setDuration(1000);
oa.start();
```
>动画组合用AnimatorSet，调用`as.playTogether(oa,oa2,oa3)`或`as.playsequential(oa,oa2,oa3)`然后start()
使用xml方式定义则是res下创建animator目录