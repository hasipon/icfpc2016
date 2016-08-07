問題の入力画像をgnuplotでいい感じに表示するよ

（[/watanabe-yuya/plot](https://github.com/hasipon/icfpc2016/tree/master/watanabe-yuya/plot) がベース）

## usage:
* 全生成
```sh
$ make
$ make run
```
* problem_id を指定して生成
```
$ make
$ make run ID='<problem_id1> <problem_id2>'
```
生成用のファイルは `tmp/*` ，画像は `img/*` に出力されるよ．
