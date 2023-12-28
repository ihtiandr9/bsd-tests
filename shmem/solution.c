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
	if (3 > argc)
	{
		printf("\tUsage:\n\t\t ./solution <key1> <key2>");
		exit(-1);
	}

	char buf[512];
	int *src1, *src2, *dst;
	key_t keysrc1 = atoi(argv[1]);
	key_t keysrc2 = atoi(argv[2]);

	int src1mem_id = shmget( keysrc1, 1000, 0 );
	int src2mem_id = shmget( keysrc2, 1000, 0 );

	src1 = shmat(src1mem_id, 0, 0);
	src2 = shmat(src2mem_id, 0, 0);

	key_t keydst = ftok( argv[0], getpid());
	int dstmem_id = shmget( keydst, 1000, IPC_CREAT | 0666 );
	dst = shmat( dstmem_id, 0, 0);

	for(int i =0; i<100; i++)
	{
		*(int*)((long)dst+i*sizeof(int)) =  *(int*)((long)src1 + i*sizeof(int)) + *(int*)((long)src2+i*sizeof(int));
	}

	//sprintf(dst, "pid = %d\n", getpid());
	shmdt(dst);

	//fgets(buf, 512,fd);
	printf("%d\n",keydst);
	return 0;
}
