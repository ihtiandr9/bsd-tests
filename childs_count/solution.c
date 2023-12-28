#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>

int count_children(int pid)
{
	if (pid < 1)
		return 0;
	int res = 1;
	char childs[512];
	char fpath[512], *instr;
	childs[0] = 0;
	sprintf(fpath, "/proc/%d/task/%d/children", pid, pid);
	FILE *fd = fopen(fpath, "ro");
	if (!fd)
	{
		printf("file %s not found", fpath);
		exit(-1);
	}
	fgets(childs, 512, fd);
	//printf("strlen %ld\n \"%s\"\n", strlen(childs), childs);
	fclose(fd);

	instr = strtok(childs, " ");
	while (instr)
	{
		pid = atoi(instr);
		instr =(char*)( 1 + strlen(instr) + (size_t)instr);
		res += count_children(pid);
		instr = strtok(instr, " ");
	}
	return res;
}

int main(int argc, char *argv[])
{
	if (2 > argc)
	{
		printf("Usage: ./solution pid\n");
		exit(-1);
	}

	//char buf[512];
	int pid = atoi(argv[1]);

	printf("%d\n", count_children(pid));
	return 0;
}
