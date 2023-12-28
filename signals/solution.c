#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>

void hSigterm(int signo)
{
printf("signal %d recieved", signo);
return;
}

int main(int argc, char *argv[])
{
	int pid = fork();
	if(pid)
	{
		printf("%d\n",pid);
	}
	else{
		setsid();
		signal(SIGTERM, hSigterm);
		fclose(stdin);
		fclose(stderr);
		while(1)
		sleep(20);
	}
	
	return 0;
}
