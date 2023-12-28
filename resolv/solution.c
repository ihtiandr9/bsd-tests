#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		exit(-1);
	struct hostent h = *gethostbyname(argv[1]);
	//printf("%s\n", h.h_name);
	for (int i = 0; h.h_addr_list[i]; i++)
		printf("%s\n", inet_ntoa(*(struct in_addr *)h.h_addr_list[i]));
	return 0;
}
