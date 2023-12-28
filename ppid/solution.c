#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<dlfcn.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	char buf[512], *instr;
	int pid = getpid();	
	//printf("pid = %d", pid);
	int ppid = getppid();
	FILE *fd = fopen("/proc/self/stat", "ro");
	if (!fd)
	{
		printf("file not found");
		exit(-1);
	}

	fgets(buf, 512,fd);
	instr = strtok(buf, " ");
	instr = strtok(0, " ");
	instr = strtok(0, " ");
	instr = strtok(0, " ");
	printf("%s\n", instr);
	return 0;
}
