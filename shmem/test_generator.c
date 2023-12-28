#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int *src1, *src2;
	key_t keysrc1 = ftok( argv[0], getppid());
	key_t keysrc2 = ftok( argv[0], getppid()+1);

	int src1mem_id = shmget( keysrc1, 1000, IPC_CREAT | 0666 );
	int src2mem_id = shmget( keysrc2, 1000, IPC_CREAT | 0666 );

	src1 = shmat(src1mem_id, 0, 0);
	src2 = shmat(src2mem_id, 0, 0);

	for(int i =0; i<100; i++)
	{
		src1[i]=i;
		src2[i]=i*2;
	}

	//sprintf(dst, "pid = %d\n", getpid());
	shmdt(src1);
	shmdt(src2);

	//fgets(buf, 512,fd);
	printf("%d %d\n",keysrc1, keysrc2 );
	return 0;
}
