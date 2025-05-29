#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

struct option opts[] = 
{
	{"query", required_argument, 0, 'q'},
	{"longinformationrequest", no_argument, 0, 'i'},
	{"version", no_argument, 0, 'v'},
	{0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
    int query = 0;
    int argerr = 0;
    int rez;

    while( -1 != (rez = getopt_long(argc, argv, "q:iv", opts, &optind)))
    {
        switch (rez)
        {
            case 'i':
                printf("found argument \"i\".\n");
                break;
            case 'q':
                printf("found argument \"q\".\n");
                query = atoi(optarg);
                if (!query) argerr = 1;
                break;
            case 'v':
                printf("found argument \"v\".\n");
                break;
            default:
                argerr = 1;
        }
    }

    if(argerr) printf("-"); else printf("+");
    return 0;
}
