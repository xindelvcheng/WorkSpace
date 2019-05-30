在`C:\Windows\System32\drivers\etc\hosts`文件中添加以下两句

```
151.101.76.249 http://global-ssl.fastly.net
192.30.255.112 github.com
```

然后刷新DNS缓存

```bash
ipconfig /flushdns
```

