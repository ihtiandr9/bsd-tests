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
	int fd = open("/proc/curproc/status", O_RDONLY);
	if (!fd)
	{
		printf("file not found");
		exit(-1);
	}

	read(fd, buf, 512);
	instr = strtok(buf, " ");
	instr = strtok(0, " ");
	instr = strtok(0, " ");
	instr = strtok(0, " ");
	instr = strtok(0, " ");
	printf("%s\n", instr);
	printf("with cmd: %s\n", buf);
	read(0, buf, 5);
	return 0;
}
