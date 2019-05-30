# ffmpeg入门

ffmpeg主要有三个可执行程序

- ffmpeg 视频处理
- ffplay 简单的音视频播放器，注意不是ffmplay，按q退出播放，左右快进快退，f全屏，p暂停
- ffprobe 视频信息查看

## 入门使用

### 1. 转码

音视频的编码实际就是压缩

```bash
$ ffmpeg -i input.avi output.mp4 # -i 指定输入文件
```

#### 音频转码

```bash
# a：audio ；codec：编解码器（有输出后缀名时不用指定）；r：rate 采样率；b：bit 比特率；c：channel，通道数，2为双声道；不指定默认值为和原音频相同
$ ffmpeg -i in.flac -acodec libmp3lame -ar 44100 -ab 320k -ac 2 out.mp3
```

