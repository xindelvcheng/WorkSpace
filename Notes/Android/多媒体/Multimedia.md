# Android 多媒体
Android中保存图片格式默认为png，通道为ARGB，每个像素占4个byte，图片文件大小=像素总数*每个像素占用大小
## ImageView显示图片
```
ImageView iv = findViewById(R.id.iv1);
BitmapFactory.Options options = new BitmapFactory.Options();
options.inJustDecodeBounds = true;
BitmapFactory.decodeFile("mnt/sdcard/pic.png",options);

WindowManager wm = (WindowManager) getSystemService(WINDOW_SERVICE);
int x = wm.getDefaultDisplay().getHeight();
int y = wm.getDefaultDisplay().getWidth();

options.inSampleSize = options.outHeight/x > options.outWidth/y ? options.outHeight/x : options.outWidth/y;

options.inJustDecodeBounds = false;
Bitmap bitmap2 = BitmapFactory.decodeFile("mnt/sdcard/pic.png", options);

iv.setImageBitmap(bitmap2);
```
>读取的原图片是不能修改的，调用`bitmap_copy.setPixel(x,y,Color.RED);`会报错
## 安卓中的图像绘制
### 1.创建一个空白图片，往上面画一个图片
```
Bitmap bitmap_copy = Bitmap.createBitmap(bitmap_src.getWidth(), bitmap_src.getHeight(), bitmap_src.getConfig());
Paint paint = new Paint();//画笔
Canvas canvas = new Canvas(bitmap_copy);//画布
canvas.drawBitmap(bitmap_src,new Matrix(),paint);//绘画
iv2.setImageBitmap(bitmap_copy);
```
### 2.案例：画画板
```
public class MainActivity extends AppCompatActivity {


    private ImageView iv;
    private Bitmap bitmap;
    private Paint paint;
    private Canvas canvas;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        iv = findViewById(R.id.iv1);
        Bitmap bitmap_src = BitmapFactory.decodeResource(getResources(), R.drawable.ic_launcher_background);
        this.bitmap = Bitmap.createBitmap(160,240,bitmap_src.getConfig());
        paint = new Paint();
        canvas = new Canvas(this.bitmap);
        canvas.drawBitmap(bitmap_src,new Matrix(),paint);

        iv.setOnTouchListener(new View.OnTouchListener() {
            int x_start = -1;
            int y_start = -1;
            int x_end = -1;
            int y_end = -1;
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        x_start = (int) event.getX();
                        y_start = (int) event.getY();
                        break;
                    case MotionEvent.ACTION_MOVE:
                        x_end = (int) event.getX();
                        y_end = (int) event.getY();
                        canvas.drawLine(x_start,y_start,x_end,y_end, paint);
                        iv.setImageBitmap(MainActivity.this.bitmap);
                        x_start = x_end;
                        y_start = y_end;
                        break;
                    case MotionEvent.ACTION_UP:
                        x_end = (int) event.getX();
                        y_end = (int) event.getY();
                        canvas.drawLine(x_start,y_start,x_end,y_end, paint);
                        iv.setImageBitmap(MainActivity.this.bitmap);
                }
                return true;
            }
        });
        iv.setImageBitmap(this.bitmap);
    }
    public void clear(View view) {paint.setColor(Color.RED);}
    public void bold(View view) {paint.setStrokeWidth(15);}
    public void save(View view) {
        OutputStream os = null;
        try {
            os = openFileOutput("painted.png",MODE_PRIVATE);
            bitmap.compress(Bitmap.CompressFormat.PNG,100,os);
        } catch (Exception e) {e.printStackTrace();}
    }
}
```
## 播放音频
### 1.MediaPlayer 
#### 播放本地音乐
```
MediaPlayer player = new MediaPlayer();
player.setDataSource("/sdcard/ASSUMED SOUNDS - 剣巫.mp3");
player.prepare();
player.start();
```
#### 播放网络音乐
```
MediaPlayer player = new MediaPlayer();
player.setDataSource("http://www.music.com/ASSUMED SOUNDS - 剣巫.mp3");
player.prepareAsync();

player.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
    @Override
    public void onPrepared(MediaPlayer mp) {
        player.start();
    }
});
```
>MediaPlayer常见方法
```
player.start();             //播放
player.getDuration();       //获取总时长
player.getCurrentPosition() //获取当前播放位置
player.seekTo(position);    //设置播放位置
player.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
    @Override
    public void onCompletion(MediaPlayer mp) {
        System.out.println("歌曲播放完成");
    }
});                         //设置事件监听
```
MediaPlayer的同步和异步
-   同步一般用于播放本地音频
-   异步一般应用播放网络音频，不用开子线程（调用的是native方法，在c语言中实现过了）
## 播放视频
MediaPlayer只能播放mp4或3gp格式
#### 1.使用SurfaceView
比较麻烦，SurfaceView是一个重量级的控件，不能立即初始化好，可以开启子线程等待一段时间再播放或者在SurfaceView生命周期函数中播放
```
SurfaceView sfv = findViewById(R.id.sfv);
SurfaceHolder holder = sfv.getHolder();
holder.addCallback(new SurfaceHolder.Callback() {
    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        try {
            player = new MediaPlayer();
            player.setDisplay(holder);
            player.prepare();
            player.start();
            player.seekTo(position);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        if (player!=null&&player.isPlaying())
        position = player.getCurrentPosition();
    }
});
```
### 2.使用VideoView
VideoView是对SurfaceView和MediaPlayer的封装
```
VideoView vv = findViewById(R.id.vv);
vv.setVideoPath("/sdcard/xxx.mp4");
vv.start();
```
>VideoView和Surfaceview一样都只能播放MP4（移动设备）和3gp格式的视频
### 3.使用开源框架
建议
## 照相和录像
### 使用隐示意图开启系统的照相机
#### 照相
```
Intent intent = new Intent();
intent.setAction(MediaStore.ACTION_IMAGE_CAPTURE);
intent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(new File(Environment.getExternalStorageDirectory().getPath(), "test.png")));
startActivityForResult(intent,1);
```
#### 录像
```
intent.setAction(MediaStore.ACTION_VIDEO_CAPTURE);
```