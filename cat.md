/*
```c:cat.c 
## ヘッダ部分
*/
#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
/*
```
```c:cat.c
## cat機能本体
-引数
-- fd:int 読み込み先のファイルディスクリプタ

readシステムコールを用いて
fdからbufサイズ分のデータを読み込み
fd 1に対して上記のデータを書き込む

```c:cat.c
*/

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
/*
```
### メイン関数
```c:cat.c
*/

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
/*
```
*/
