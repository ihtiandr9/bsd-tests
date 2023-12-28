#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int inforeq = 0;
int query = 0;
int version = 0;
int optindex;
int argerr = 0;
extern int opterr;


struct option opts[] = 
{
	{"query", required_argument, 0, 'q'},
	{"longinformationrequest", no_argument, 0, 'i'},
	{"version", no_argument, 0, 'v'},
	{0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
  opterr = 0;
  /*if (argc < 2)
  {
    printf("-");
    exit(-1);
  }
*/
  int rez;
  while( -1 != (rez = getopt_long(argc, argv, "q:iv", opts, &optindex )))
  {
    switch (rez)
    {
    case 'i':
      //printf("found argument \"i\".\n");
      // printf("+");
      break;
    case 'q':
      query = atoi(optarg);
      if (!query) argerr = 1;
      break;
    case 'v':
      break;
    default:
      argerr = 1;
    } // switch
  }   // for

if(argerr) printf("-"); else printf("+");
  return 0;
}
