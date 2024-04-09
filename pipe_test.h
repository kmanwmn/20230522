#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/mman.h>
#include<string.h>
#include <sys/types.h> 
//#include<MAP.h>

typedef struct signal{
union MSG{
char login[sizeof("Login:name")];
char date[sizeof(1024)];
char all[sizeof("all")];
char quit[sizeof("quit")];
}msg;
char name[10];//放自己私有管道的名字
}Msg;

 

int createPipe(char*name);//创建管道

int closePipe(char*name);//关闭管道

void recvDate();//接收数据

void dealDate(char* date);//处理数据

int sendDate(Msg aa,char* name);//发送数据

int Check_name(char all_name[],int b,char *name);//检查名字是否重复

