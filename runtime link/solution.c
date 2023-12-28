#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dlfcn.h>

static const char aUsage[]=	"Usage: \n \t " \
							"./solution libShared.so someSecretFunction param\n";

int main(int argc, char *argv[])
{
	void *hdl;
	int (*dlfunc)(char*);

	if( argc < 4)
	{
		printf("%s", aUsage);
	}

	hdl = dlopen(argv[1], RTLD_LAZY);
	if(!hdl)
	{
		printf("So not found");
		exit(-1);
	}
		
	dlfunc = (int (*)(char*)) dlsym(hdl, argv[2]);
	if(!dlfunc)
	{
		printf("function not found");
		exit(-1);
	}		
	printf("%d\n",dlfunc(argv[3]));	
	return 0;
}
