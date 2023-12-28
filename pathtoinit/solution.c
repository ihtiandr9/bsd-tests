#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char buf[512], filename[512], *instr;
	int pid = atoi(argv[1]);
	printf("%d\n",pid);
	while (pid != 1)
	{
		sprintf(filename, "/proc/%d/stat", pid);

		FILE *fd = fopen(filename, "ro");
		if (!fd)
		{
			printf("file not found");
			exit(-1);
		}
		fgets(buf, 512, fd);
		instr = strtok(buf, " ");
		instr = strtok(0, " ");
		instr = strtok(0, " ");
		instr = strtok(0, " ");
		printf("%s\n", instr);
		pid = atoi(instr);
	}
	return 0;
}
