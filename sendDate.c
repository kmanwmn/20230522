#include<pipe_test.h>

int sendDate(Msg aa,char* name){//发送数据
int fd=open(name,O_WRONLY);
//fd应该是从管道的
//int flag=fcntl(fd,F_GETFL);//传出文件描述符
//flag|=O_NONBLOCK;
//fcntl(fd,F_SETFL,flag);//设置非阻塞

if((write(fd,&aa,sizeof(aa)))<0){
close(fd);
return 0;
}else{
close(fd);
return 1;
}
}

