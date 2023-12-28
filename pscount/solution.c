#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	char buf[512], filename[512];
	DIR *dir = opendir("/proc");
	struct dirent *entry;
	int count=0;
	if (!dir)
	{
		printf("dir not found");
		exit(-1);
	}
	while((entry = readdir(dir)))
	{
		//printf("%s\n",entry->d_name);
		sprintf(filename, "/proc/%s/comm", entry->d_name);
		FILE *file = fopen(filename, "ro");
		if(!file)
			;//printf("file %s not found\n", filename); //not pid
		else
		{
			fgets(buf, 512, file);
			if (!strcmp("genenv\n", buf)) count++;
			//printf("%s\n",buf);
			fclose(file);
		}
	}
	printf("%d\n",count);
	return 0;
}
