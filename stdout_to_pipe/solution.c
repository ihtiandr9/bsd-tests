#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (3 > argc)
	{
		printf("Usge:\n"
			   "	./solution someprog param");
		exit(-1);
	}
	const char *someprog = argv[1];
	const char *param = argv[2];
	char buf[512], cmdline[512];
	FILE *fpipe;
	int st;

	sprintf(cmdline, "%s %s", someprog, param);
	if (!(fpipe = popen(cmdline, "r")))
	{
		printf("error creating pipe");
		exit(-1);
	}
	int zeroes = 0;
	char *instr = 0;
	while (fgets(buf, 512, fpipe))
	{
		for (instr = buf; ((size_t)instr - (size_t)buf) < strlen(buf); instr++)
		{
			if ('0' == *instr)
				zeroes++;
		}
	}
	printf("%d\n", zeroes);

	return 0;
}
