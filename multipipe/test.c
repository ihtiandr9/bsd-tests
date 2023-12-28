#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>


int main(int argc, char argv[])
{
	int fd = open("in1",O_WRONLY| O_NONBLOCK);
	if (fd<0)
	{
		printf("error opening fifo\n");
		exit(-1);
	}else
	{
		fd_set writeset;
		FD_ZERO(&writeset);
		FD_SET(fd, &writeset);
		int n = select(fd + 1, 0, &writeset, 0,0);
		if(n>0 && FD_ISSET(fd,&writeset))
			write(fd, "23",2);

		n = select(fd + 1, 0, &writeset, 0,0);
		if(n>0 && FD_ISSET(fd,&writeset))
			write(fd, "32",2);
		close(fd);
	}
	fd = open("in2",O_WRONLY| O_NONBLOCK);
	if (fd<0)
	{
		printf("error opening fifo\n");
		exit(-1);
	}else
	{
		fd_set writeset;
		FD_ZERO(&writeset);
		FD_SET(fd, &writeset);
		int n = select(fd + 1, 0, &writeset, 0,0);
		if(n>0 && FD_ISSET(fd,&writeset))
			write(fd, "45",2);
		close(fd);
	}
	return 0;
}
