#include<pipe_test.h>

void dealDate(char* date){//处理数据
//拆包
Msg meage=*(Msg*)date;
extern char all_name[1024];

char m_name [15];

       //对比字符串，因为是联合体，所以只能有一个数值
	if ((strncmp(meage.msg.login,"Login:name",6))==0) {
//主端为其创建管道，并保存私有管道名 到一个字符数组里，用“：”分割
		printf("login = %s\n", meage.msg.login);
		char*date=strtok(meage.msg.date,":");
		char*p1=strtok(NULL,":");
		int fd=createPipe(p1);//创建管道

		if (0==strcmp(all_name,"")) { //把私有管道的名字存在一个字符数组里并用":"分割
			strcat(all_name, (char*)meage.name);
		}
		else {
			strcat(all_name, ":");
			strcat(all_name, (char*)meage.name);
		}

		printf("create pipe success\n");

	}
	else if ((strcmp(meage.msg.all, "all")) == 0) {
//主端反馈所有有效用户
		printf("all is running\n");
		sprintf(m_name,"./%s",meage.name);
		int fd=open(m_name,O_WRONLY);

			//发送所有有效用户给从端
		if(-1==write(fd,all_name,sizeof(all_name))){  //11 2
		//if(-1==write(fd,&m_name,sizeof(m_name))){
		perror("write failed");
		close(fd);
		exit(-6);
		}
		close(fd);

	}
	else if ((strcmp(meage.msg.quit, "quit")) == 0) {
//主端关闭对应私有管道
		printf("close pipe is running\n");
		if(0==closePipe(meage.name)){
		perror("close failed");
		exit(-5);		
		}
	}
	else {
//printf("date deal is running\n");
//主端处理数据(谁要发给谁)，然后转发
		if ((strchr(meage.msg.date, ':')) != NULL) 
		//if(sizeof(meage)>0);
		{
		printf("date deal is running\n");
		//printf("%s\n",meage.msg.date);
		//判断数据格式是否符合要求(截取：前的名字与保存的名字对比，不同就返回)
		char*p1=strtok(meage.msg.date,":");
		char*date=strtok(NULL,":");
	     	//在保存有 私有管道名 的all_name里查找是否有 p1指针指向的名字
		

		//if(0==Check_name(all_name, 0, p1)){
		//printf("check name not exist\n");
		//exit(-4);
		//}
		//发送数据给p2
		Msg to_p2;
		//char* m_p1 = meage.name;
		//strcpy(to_p2.name, meage.name);
		sprintf(to_p2.msg.date, "%s:%s", meage.name,date);
		printf("%s", to_p2.msg.date);
				
		if(0==sendDate(to_p2, p1)){
		perror("sendTop2 failed");
		exit(-3);
		}

		}
		


	}


//strtok分割字符串，并存储起来（用链表存储有效用户）



//判断字符串，创建管道 | 关闭管道 | 发送数据 （结构体|有效用户）

return;


}
