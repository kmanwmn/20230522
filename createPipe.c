#include<pipe_test.h>

int createPipe(char*name){// 根据名字 创建私有管道
char m_name[25];
char c_buf[25];
printf("createPipe is running\n");
mkfifo(name,0664);

sprintf(m_name,"./%s",name);

printf("createPipe open 1\n");
int fd=open(m_name,O_WRONLY); 
if(fd<0)printf("createPipe open 2\n");
//int flag=fcntl(fd,F_GETFL);//传出文件描述符
//flag|=O_NONBLOCK;
//fcntl(fd,F_SETFL,flag);//设置非阻塞
sprintf(c_buf,"%s is create",name);
if(-1==write(fd,c_buf,sizeof(c_buf))){
perror("write failed");
close(fd);
exit(-6);
}

//return fd; //返回文件描述符
//close(fd);
return 1;
}
