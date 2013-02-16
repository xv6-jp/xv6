/*:md
# cat.c
ファイルをコンソールに表示させたり、連結させたりする場合のコマンド

## ヘッダ部分
```c:cat.c 
md:*/
#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
/*:md
```
## cat機能本体
* 引数
    * fd:int 読み込み先のファイルディスクリプタ

    readシステムコールを用いて
    fdからbufサイズ分のデータを読み込み
    fd 1に対して上記のデータを書き込む

```c:cat.c
md:*/

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
/*:md
```
### メイン関数
```c:cat.c
md:*/

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit();
  }

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
/*:md
```
md:*/
