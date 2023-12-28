#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

// Эта функция будет вызвана перед тем как вызывать myalloc и myfree
// используйте ее чтобы инициализировать ваш аллокатор перед началом
// работы.
//
// buf - указатель на участок логической памяти, который ваш аллокатор
//       должен распределять, все возвращаемые указатели должны быть
//       либо равны NULL, либо быть из этого участка памяти
// size - размер участка памяти, на который указывает buf

struct memblock
{
	struct memblock *next;
	size_t size;
	void *data;
};

#define BLOCK_SIZE (16+sizeof(struct memblock))

static struct memblock *freemem = 0;

void free_block(void *block)
{
	struct memblock *cur = (struct memblock *)block;
	struct memblock *prev;
	for(prev = freemem; prev && (size_t)(prev->next) > (size_t)cur; prev=prev->next);
	if((size_t)(prev) > (size_t)cur)
	{
		cur->next = prev->next;
		prev->next = cur;
	}		
	else
	{
		cur->next = freemem;
		freemem = cur;
	}
}

void free_range(void *start, size_t numblocks)
{
	for (int i = 0; i < numblocks; i++)
	{
		printf("freeing block %lx\n", (unsigned long)((char *)start + i * BLOCK_SIZE));
		free_block((char *)start + i * BLOCK_SIZE);
	}
}
struct memblock *memblock_alloc(size_t num)
{
	const int requested_blocks = num;
	struct memblock *range_addr = 0, *tmp = 0;
	for (range_addr = freemem; range_addr; range_addr = range_addr->next)
	{
		if (!tmp || ((char *)tmp - (char *)range_addr) > BLOCK_SIZE || 0 > ((char *)tmp - (char *)range_addr))
			num = requested_blocks;
		tmp = range_addr;
		num--;
		if (!num)
			break;
	}
	if (num)
		range_addr = 0;
	if (range_addr)
	{
		// for (tmp = freemem; tmp->next != range_addr + requested_blocks * BLOCK_SIZE; tmp = tmp->next)
		for (tmp = freemem; (void *)tmp->next != (void *)range_addr + (requested_blocks - 1) * BLOCK_SIZE; tmp = tmp->next)
			if (!tmp->next)
				break;
		if (!tmp->next)
			freemem = range_addr->next;
		else
			tmp->next = range_addr->next;
	}
	return range_addr;
}

void mysetup(void *buf, size_t size)
{
	int numblocks = size / BLOCK_SIZE;
	printf("buf = 0x%lx size = %d blocks (512)\n", (unsigned long)buf, numblocks);
	free_range(buf, numblocks);
}

// Функция аллокации
void *myalloc(size_t size)
{
	void *res = 0;
	size_t blocks = (size + sizeof(struct memblock)) / BLOCK_SIZE + 1;
	struct memblock *allocated = memblock_alloc(blocks);
	if (allocated)
	{
		allocated->size = blocks;
		res = (void *)(&allocated->data);
	}
	printf("allocated block = 0x%lx size = %lu blocks (512)\n", (unsigned long)allocated, blocks);
	return res;
}

// Функция освобождения
void myfree(void *p)
{
	if(!p)
		return;
	struct memblock *start = (struct memblock *)((char *)p - (char *)&(((struct memblock *)0)->data));
	size_t allocated = start->size;
	free_range(start, allocated);
}
void mymemstat()
{
	int count = 0;
	for (struct memblock *i = freemem; i; i = i->next)
	{
		printf("block: 0x%p\n", (void*)i);
		count++;
	}
	printf("%d free blocks\n", count);
}
int main(int argc, char *argv[])
{
	static char buf[4 * BLOCK_SIZE];
	mysetup(buf, 4 * BLOCK_SIZE);
	mymemstat();
	void *tmp1 = myalloc(10);
	printf("%p allocated\n", (void*)tmp1);
	void *tmp2 = myalloc(10);
	printf("%p allocated\n", (void*)tmp2);
	void *tmp3 = myalloc(20);
	printf("%p allocated\n", (void*)tmp3);
	mymemstat();
	myfree(tmp1);
	myfree(tmp2);
	myfree(tmp3);
	mymemstat();
	tmp1 = myalloc(50);
	printf("%p allocated\n", (void*)tmp1);
	mymemstat();
	return 0;
}
