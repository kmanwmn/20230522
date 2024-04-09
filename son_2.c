#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/mman.h>
#include<string.h>
#include <sys/types.h> 

typedef struct signal{
	union MSG{
		char login[sizeof("Login:name")];
		char date[sizeof(1024)];
		char all[sizeof("all")];
		char quit[sizeof("quit")];
	}msg;
	char name[10];//放自己私有管道的名字
}Msg;


int main(){
Msg meage;
//strcpy(meage.name,"p2");//把从端2命名位p2
int fd;
if(-1==(fd=open("../source/comPipe",O_WRONLY))){
perror("open failed");
exit(-1);
}

//int flag1=fcntl(fd,F_GETFL);//传出文件描述符
//flag1|=O_NONBLOCK;
//fcntl(fd,F_SETFL,flag1);//设置非阻塞

printf("please input your pipe name\n");
char p_name[15];
scanf("%s",&p_name);//输入管道名字
strcpy(meage.name,p_name);
printf("my name is %s\n",meage.name);
sprintf(meage.msg.login,"Login:%s", meage.name);//把Login:name存到结构体的login里
if(-1==(write(fd,&meage,sizeof(meage)))){
perror("p1 write failed");
exit(-2);
}

char m_name[25];
sprintf(m_name,"../source/%s", meage.name);
int fd2;
sleep(2);
if(-1==(fd2=open(m_name,O_RDONLY))){//打开自己的私有管道
//if(-1==(fd2=open("../source/p2",O_RDONLY))){//打开自己的私有管道
perror("open pipe failed");
exit(-1);
}else{
printf("open success\n");
}

int flag=fcntl(fd2,F_GETFL);//传出文件描述符
flag|=O_NONBLOCK;
fcntl(fd2,F_SETFL,flag);//设置非阻塞

int attr = 0;
    
	attr = fcntl(STDIN_FILENO, F_GETFL);
	attr |= O_NONBLOCK;
	fcntl(STDIN_FILENO, F_SETFL, attr);

char buf[100];
Msg tmp;
int size;
while(1){//循环读私有管道，写公共管道
	//if(0<read(fd2,buf,sizeof(buf))){
	size=read(fd2,&buf,sizeof(buf));  //2
	if(size>0){
	tmp=*(Msg*)buf;
	printf("  %s\n",tmp.msg.date);
	memset(&buf,0,sizeof(buf));
	}
	//sleep(1);
//printf("son is running\n");

	if(sizeof(meage)>0){
	if(-1==(write(fd,&meage,sizeof(meage)))){  //2
	perror("p1 write failed");
	exit(-2);
	}
	memset(&meage,0,sizeof(meage));
	sleep(1);
	}
	scanf("%s",&meage.msg.date);
	strcpy(meage.name,p_name); //存入自己的名字
	
}

close(fd);
close(fd2);
return 0;
}
