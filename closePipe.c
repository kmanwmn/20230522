#include<pipe_test.h>

int closePipe(char* name){//关闭管道
char cp_name [15];
printf("closePipe is runnning\n");
sprintf(cp_name,"./%s",name);
if(0==unlink(cp_name))
return 1;
else
return 0;

}
