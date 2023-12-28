#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dlfcn.h>

static const char aUsage[]=	"Usage: \n \t " \
							"./solution libShared.so someSecretFunction param\n";

int strStat(char *__str)
{
	return strlen(__str);
}
