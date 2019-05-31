### Clone

git clone 默认会下载项目的完整历史版本，如果你只关心最新版的代码，而不关心之前的历史信息，可以使用 git 的浅复制功能，如

```bash
$ git clone --depth=1 https://github.com/xxx.git  
```

--depth=1 表示只下载最近一次的版本，使用浅复制可以大大减少下载的数据量。

### Commit

```bash
提交所有变化
$ git commit -A

提交所有变化不包括删除
$ git commit .

提交所有变化不包括新建文件
$ git commit -u
```

### 冲突

```bash
$ git stash
$ git pull
$ git stash pop
...(add,commit and push local modifies)
```

或直接覆盖本地修改

```bash
git reset --hard
git pull
```
