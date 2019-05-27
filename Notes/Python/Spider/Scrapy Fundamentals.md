# Scrapy框架
 
[TOC]
 
## 入门
### 1.建立爬虫框架
生成项目
```
$ scrapy startproject ScrapyDemo
项目结构：
├── ScrapyDemo
│   ├── scrapy.cfg
│   └── ScrapyDemo
│       ├── __init__.py
│       ├── items.py
│       ├── middlewares.py
│       ├── pipelines.py
│       ├── __pycache__
│       │   ├── __init__.cpython-36.pyc
│       │   └── settings.cpython-36.pyc
│       ├── settings.py
│       └── spiders
│           ├── __init__.py
│           └── __pycache__
│               └── __init__.cpython-36.pyc
```
生成爬虫demo.py指定其爬去www.baidu.com
```bash
$ cd ScrapyDemo/
$ scrapy genspider demo www.baidu.com
```
### 2.编写爬虫
 
demo.py内容
 
```python
# -*- coding: utf-8 -*-
import scrapy
 
 
class DemoSpider(scrapy.Spider):
    name = 'demo'
    start_urls = ['http://www.itcast.cn/channel/teacher.shtml']
 
    def parse(self, response):
        li_list = response.xpath("//div[@class='tea_con']//li")
        for li in li_list:
            item = {}
            item["name"] = li.xpath(".//h3/text()").extract_first()  # 拿不到时返回None而不会报错
            item["title"] = li.xpath(".//h4/text()").extract_first()
            yield item # 使用yield而不是返回整个字典是防止内存占用过高
```
### 3.开启爬虫
 
```bash
$ scrapy crawl demo
```
### 4.编写管道pipelines.py处理数据
```python
class ScrapydemoPipeline(object):
    def process_item(self, item, spider):
        item["A"] = "A"
        return item # 让item在不同的pipeline中传递
    def open_spider(self,spider):
        """回调函数，用于数据库连接初始化"""
        pass
    def close_spder(self,spider):
        """回调函数，数据库断开连接"""
        pass
 
 
class ScrapydemoPipeline1(object):
    def process_item(self, item, spider):
        print(item)
        return item
```
>pipeline的作用：可以定义多个pipeline负责处理和存储；多个爬虫爬回的数据加上come_from字段,每个pipeline通过if各自处理一个网站的数据。或者本身def process_item(self, item, spider)也会将spider对象传过去，可以判断它的name属性
### 4. 配置文件
在settings.py中
```python
USER_AGENT = 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36'
 
 
# 只显示WARNING等级以上的日志
LOG_LEVEL = "WARNING"
 
# 开启pipeline
ITEM_PIPELINES = {
   'ScrapyDemo.pipelines.ScrapydemoPipeline': 300, #优先级，越小优先级越高（距离引擎的远近），可以定义多个pipeline
      'ScrapyDemo.pipelines.ScrapydemoPipeline1': 301,
}
 
# 不遵守robots协议
ROBOTSTXT_OBEY = False
```
> 将整个项目的设置集合起来放在settings.py中，使用时直接`from project_name.settings import config_name `或使用scrapy提供spider类中的类字典self.settings取
 
### 5. 日志
 
#### （1）程序中输出日志
 
settings.py中添加
 
```python
logger = logging.getLogger(__name__)
logger.warning(item)
```
#### （2）输出日志文件
 
settings.py中添加
 
```python
LOG_FILE = "./log.log"
```
#### （3）在普通的Python项目中使用logging模块
 
```python
import logging
logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s %(thread)d %(threadName)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename=logfile_path,
                    filemode='w')
```
然后使用`logger = logging.getLogger(__name__);logger.warning(item)`输出log
### 6. 翻页
在爬虫中构造Request对象并返回指定下一页url，如果下一页url是通过js生成的，往往通过在响应的js脚本中有pagecount和currentPage字段来判断是否继续翻页
```python
# -*- coding: utf-8 -*-
import scrapy
 
class DemoSpider(scrapy.Spider):
    name = 'demo'
    start_urls = ['http://www.itcast.cn/channel/teacher.shtml']
 
    def parse(self, response):
        for i in range(10):
            item = {}
            item["come_from"] = "itcast"
            yield item
        next_url = response.xpath("//a[@id='next']/@href").extract_first()
        if next_url != "javascript:;":
            next_url = "http://xxx.com/index/" + next_url
            yield scrapy.Request(
                next_url,
                callback=self.parse1,
                meta={"item":item},#实现parse函数之间数据传输
                dont_filter=True #不重复请求url
            )
    def parse1(self,response):
        print(response.meta["item"])
```
>Request对象还有method='GET',headers,cookies,body等可选参数。meta主要用于在多个parse函数中传递Item对象
 
### 7. 定义实体
items.py
```python
import scrapy
 
 
class ScrapydemoItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    come_from = scrapy.Field()
 
```
爬虫中
```python
# -*- coding: utf-8 -*-
import scrapy
from ScrapyDemo.items import ScrapydemoItem # 绝对路径，执行程序是在Scrapy文件夹下
 
class DemoSpider(scrapy.Spider):
    name = 'demo'
    start_urls = ['http://www.itcast.cn/channel/teacher.shtml']
 
    def parse(self, response):
        for i in range(10):
            item = ScrapydemoItem
            item["come_from"] = "itcast" # Item重写了__getitem__和__setitem__方法，是一个类字典
            yield item
```
这样在pipline中获得的item是一个类字典要用dict(item)将其强转为字典才能插入MongoDB中
 
## 提取数据的方法
 
### 1. xpath
 
使用`response.xpath("//div[@class='div_name']/div[1]/text()").extract_first()`这样的方法提取，如果页面中匹配的元素不止一个使用`extract()`因为xpath返回是一个选择器列表，而不会是单个字符串或字符串列表。
 
#### xpath常用语法
 
（1）取标签包裹的文本：`//text()`
 
（2）取标签属性：`//img[@class="BDE_Image"]/@src`
 
（3）属性字符串匹配：`//a[text()="下一页"]/@href`,`//div[contains(@class,l)]`
 
> 提取网页中的图片时常提取其src属性，而不是下载这张图片
 
### 2.re 正则表达式
 
```python
import re
 
re.findall("profix(.*?)suffix",text)[0]最小分组匹配任意长度任意字符.
```
 
#### 正则表达式常用语法
 
（1）网址中常有`.`，`?`这样的字符需要使用`\`转义，`"`,`'`也要转义
 
（2）`\d+` 匹配任意长度大于1 的数字串，如`r'https://www\.smzdm\.com/p/\d+/'`匹配网址
 
（3）`{}`匹配指定长度，如`re.findall("20\d{2}/\d{2}/\d{2}",data)`匹配日期
 
## CrawlSpider
 
用于简化翻页和跳转页面的代码
 
### 1. 创建
 
```bash
$ scrapy genspider -t crawl smzdm_crawl smzdm.com
```
 
### 2. 编写爬虫文件
 
```python
# -*- coding: utf-8 -*-
import scrapy
from scrapy.linkextractors import LinkExtractor
from scrapy.spiders import CrawlSpider, Rule
import re
 
 
class SmzdmCrawlSpider(CrawlSpider):
    name = 'smzdm_crawl'
    allowed_domains = ['smzdm.com']
    start_urls = ['https://search.smzdm.com/?c=home&s=%E6%89%8B%E6%9C%BA&v=b']
 
    # url提取规则
    rules = (
        # LinkExtractor：使用正则表达式提取url返回给parse函数发送请求，所以CrawlSpider不能重写parse方法,allow:re方式,restrict_xpaths:xpath方式，deny：re方式拒绝地址，优先级高于allow
        # callback：处理response，详情页使用
        # follow：当前url的响应能够进入rules，列表页使用
        Rule(LinkExtractor(allow=r'https://www\.smzdm\.com/p/\d+/'), callback='parse_item'),
        Rule(LinkExtractor(allow=r'https://search\.smzdm\.com/\?c=home&s=%E6%89%8B%E6%9C%BA&v=b&p=\d+'), follow=True),
    )
 
    def parse_item(self, response):
        item = {}
        item["good_name"] = response.xpath("//span[@class='main-title']/em/text()").extract_first()
        yield item
 
```
 
> 1. 可以在parse_item()中`yield scrapy.Request()`并指定回调的parse_item2()，适用于一部分数据在目录，一部分数据在详情页的情况
> 2. crawl_spider会自动补全不完整的请求地址，如果在普通的爬虫文件中需要补全url，可以使用` urllib.parse.urljoin(url,url_part)`
 
### 3. 开启爬虫
 
```bash
$ scrapy crawl smzdm_crawl
```
 
## 多线程
 
某些情况由于多线程情况下item被多次重写，得到重复的结构，需要使用深拷贝
 
```python
from copy import deepcopy
 
 
def parse(self,response):
    item = deepcopy(response["meta"])
```
 
## Cookie与模拟登录
 
### 1. 手动使用cookie登录
 
```python
# -*- coding: utf-8 -*-
import scrapy
import re
 
 
class BaiduSpider(scrapy.Spider):
    name = 'baidu'
    allowed_domains = ['baidu.com']
    start_urls = ['https://pan.baidu.com/disk/home?errno=0&errmsg=Auth%20Login%20Sucess&&bduss=&ssnerror=0&traceid=#/all?path=%2F&vmode=list']
 
    # 请求第一个网址时调用
    def start_requests(self):
        cookies = "-------------------*************-------------------"
        cookies = {cookie.split("=")[0]: cookie.split("=")[1] for cookie in cookies.split("; ")}
 
        yield scrapy.Request(
            self.start_urls[0],
            callback=self.parse,
            cookies=cookies
        )
 
    def parse(self, response):
        print(re.findall("全部文件", response.body.decode()))
```
 
> Scrapy默认是开始Cookie的，之后的每一次请求都会带上这个Cookie。在Settings.py中使用`COOKIE_DEBUG=True`来详细观察
 
### 2. 发送post请求
 
使用FormRequest，指定formdata。**网站往往不会直接post用户名和密码，可以使用Chrome的search功能查找token的位置，有可能在响应文件中，也可能js生成。**
 
```python
# -*- coding: utf-8 -*-
import scrapy
import re
 
class GitubSpider(scrapy.Spider):
    name = 'github'
    allowed_domains = ['github.com']
    start_urls = ['https://github.com/login']
 
    def parse(self, response):
        authenticity_token = response.xpath('//input[@name="authenticity_token"]/@value').extract_first()
        utf8 = response.xpath('//input[@name="utf8"]/@value').extract_first()
        commit = response.xpath('//input[@name="commit"]/@value').extract_first()
 
        post_data = dict(
                commit = commit,
                utf8 = utf8,
                authenticity_token = authenticity_token,
                login = "xindelvcheng",
                password = "*********"
            )
 
        yield scrapy.FormRequest(
                "https://github.com/session",
                formdata = post_data,
                callback = self.parseLogin
            )
 
    def parseLogin(self,response):
        print(re.findall("ImageSpliter",response.body.decode()))
```
 
> 使用`scrapy.Request（）`也可以发送POST请求，指定method和body即可
 
对于网页中form表单有action（而不是出发js事件）的情况，可以只提交用户名和密码，通过Scrapy提供的方法FormRequest.from_response()自动从网页中寻找form表单的action地址
 
```python
# -*- coding: utf-8 -*-
import scrapy
import re
 
class GitubSpider(scrapy.Spider):
    name = 'gitub'
    allowed_domains = ['github.com']
    start_urls = ['https://github.com/login']
 
    def parse(self, response):
 
        post_data = dict(
                authenticity_token = authenticity_token,
                login = "xindelvcheng",
                password = "*******"
            )
 
        yield scrapy.FormRequest.from_response(
                response,
                formdata = post_data,
                callback = self.parseLogin
            )
 
    def parseLogin(self,response):
        print(re.findall("ImageSpliter",response.body.decode()))
```
 
> 如果返回的页面中存在多个form表单，可以通过FormRequest的一些构造方法参数来指定Form表单
 
## 中间件
 
###  1. 下载中间件
 
在引擎和下载器之间，可以重写`process_request(self, request, spider)`从来处理一些反爬的措施。和管道一样，使用中间件需要在settings.py中开启。
 
#### 随机UserAgent
 
（1）在Settings.py中添加UserAgent列表并开启中间件
 
```python
USER_AGENTS = ["Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.121 Safari/537.36","Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/30.0.1599.101 Safari/537.36"]
 
DOWNLOADER_MIDDLEWARES = {
   'SMZDM.middlewares.SmzdmDownloaderMiddleware': 543,
}
```
 
（2）编写middlewares.py
 
```python
import random
 
class SmzdmDownloaderMiddleware(object):
    def process_request(self, request, spider):
        ua = random.choice(spider.settings.get("USER_AGENTS"))
        request.headers["User-Agent"] = ua
        return None
 
    def process_response(selfl,request,response,spider):
        print(request.headers["User-Agent"])
        return response # 如果返回request会交给调度器，如果返回response会交给爬虫
```
 
> 和pipline一样，midware可以定义多个，并指定优先级
 
### 2. 设置代理
 
```python
class ProxMiddleWare(object):
    def process_request(self,request,spider):
        request.meta["proxy"] = "http:xxx.xxx.xxx:1080"
        return None
```
 
> 实际使用时应该使用一个程序检测ip是否可用（如使用requests发送请求）