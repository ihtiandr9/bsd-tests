#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>
int read_num(int *fd)
{
	char buf[256], *instr;
	int n = read(*fd, buf, 256);
	if (n > 0)
	#ifdef _DEBUG_
		printf("recv %d bytes data from fifo %d\n", n, *fd);
	#else
	;
	#endif
	else
	{
		buf[0] = 0;
		*fd = -1;
	}
	instr = strtok(buf, " ");
	if (!instr)
		instr = buf;
	return atoi(instr);
}

int main(int argc, char *argv[])
{
	char buf[512];
	int fpipes[2];
	fd_set read_watch;
	int res = 0;

	fpipes[0] = open("in1", O_RDONLY | O_NONBLOCK);
	fpipes[1] = open("in2", O_RDONLY | O_NONBLOCK);

	int max_fd = fpipes[0];
	if(max_fd< fpipes[1])
	max_fd = fpipes[1];

	if (!((fpipes[0] > 0) && (fpipes[1] > 0)))
	{
		printf("not all pipes is opened\n");
		exit(-1);
	}

	int sizeofset = 2;
#ifdef _DEBUG_
	printf("Descriptors %d  %d  ready to read\n", fpipes[0], fpipes[1]);
#endif
	while (sizeofset)
	{
		FD_ZERO(&read_watch);
		sizeofset = 0;
		if (fpipes[0] > 0)
		{
			FD_SET(fpipes[0], &read_watch);
			sizeofset++;
		}
		if (fpipes[1] > 0)
		{
			FD_SET(fpipes[1], &read_watch);
			sizeofset++;
		}

		int st;
		if (sizeofset)
			st = select(max_fd + 1, &read_watch, 0, 0, 0);
		if (st > 0)
		{
			for (int i = 0; i < 2; i++)
			{
				if (FD_ISSET(fpipes[i], &read_watch))
					res += read_num(&fpipes[i]);
			}
		}
	}
	printf("%d\n",res);
	return 0;
}
