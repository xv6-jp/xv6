
# cat.c
ファイルをコンソールに表示させたり、連結させたりする場合のコマンド

## ヘッダ部分
```c:cat.c 

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

```
## cat機能本体
* 引数
    * fd:int 読み込み先のファイルディスクリプタ

    readシステムコールを用いて
    fdからbufサイズ分のデータを読み込み
    fd 1に対して上記のデータを書き込む

```c:cat.c


void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0)
    write(1, buf, n);
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

```
### メイン関数
```c:cat.c


int
main(int argc, char *argv[])
{
  int fd, i;

```
    引数が与えられなかった場合
    fd 0に対して上記のcat関数を実行する
    exitシステムコールを発行
```c:cat.c


  if(argc <= 1){
    cat(0);
    exit();
  }

```
    引数が与えられた場合
    すべての引数に対して openシステムコールを発行し、fdを取得
    その各fdに対して 上記cat関数を実行
    その後fdをcloseする
    すべてのファイル分作業が完了したらexitシステムコールを発行
```c:cat.c


  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);
  }
  exit();
}

```

