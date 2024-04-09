#include <pipe_test.h>

char all_name[1024];

int main(){

//创建共有管道
mkfifo("comPipe",0664);

printf("main is running\n");

//阻塞读，阻塞写
int fd;
if((fd=open("comPipe",O_RDONLY))==-1){
perror("open comPipe failed");
exit(0);
}
char buf[1024];
int size=0;


//int flag=fcntl(fd,F_GETFL);//传出文件描述符
//flag|=O_NONBLOCK;
//fcntl(fd,F_SETFL,flag);//设置非阻塞


while(1){
size=read(fd,buf,sizeof(buf)); //2
if(size>0){
dealDate(&buf);//处理数据  //2
sleep(1);
printf("main is running\n");
}else{
sleep(1);
printf("main is running\n");
}



}
return 0;
}


