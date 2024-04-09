#include<pipe_test.h>

int Check_name(char all_name[],int b,char *name) {
	char* p11 = strtok(all_name, ":");
	while (p11 != NULL) {

		if (0 == strcmp(name, "p1")) {
			return 1;
		}
		p11 = strtok(NULL, ":");
	}
	return 0;
}
