#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<dlfcn.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	int pid = fork();
	if(pid)
	{
		printf("%d\n",pid);
	}
	else{
		setsid();
		fclose(stdout);
		fclose(stdin);
		fclose(stderr);
		while(1)
		sleep(20);
	}
	
	return 0;
}
