#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>

void hSigterm(int signo)
{
static volatile int count1, count2;
if(SIGUSR1 == signo){
#ifdef _DEBUG_
	printf("signal %d recieved\n", signo);
#endif
	count1++;
}
if(SIGUSR2 == signo){
#ifdef _DEBUG_
	printf("signal %d recieved\n", signo);
#endif
	count2++;
}
if(SIGTERM == signo){
	printf("%d %d\n", count1 , count2);
	exit(0);
}

}

int main(int argc, char *argv[])
{
	signal(SIGUSR1, hSigterm);
	signal(SIGUSR2, hSigterm);
	signal(SIGTERM, hSigterm);
	while(1) sleep(20000);
	return 0;
}
