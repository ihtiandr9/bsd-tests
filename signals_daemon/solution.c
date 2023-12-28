#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>

void hSigterm(int signo)
{
if (SIGURG == signo)
	raise(9);
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
		signal(SIGURG, hSigterm);
		fclose(stdin);
		fclose(stderr);
		while(1)
		sleep(2000000);
	}
	
	return 0;
}
