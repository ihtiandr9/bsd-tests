#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (2 > argc)
	{
		printf("Use : %s <port>\n", argv[0]);
		exit(-1);
	}
	int ls = socket(AF_INET, SOCK_DGRAM, 0);
	if (ls < 0)
	{
		printf("socket error");
		exit(-1);
	}
	struct sockaddr_in addr;
	inet_aton("127.0.0.1", &addr.sin_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	char buf[512];
	bind(ls, (struct sockaddr *)&addr, sizeof(addr));
	int pos = 1;
	buf[0] = 0;
	while (pos)
	{
		int r = read(ls, buf, 512);
		buf[r] = 0;
		pos = strcmp(buf, "OFF\n");
		if (pos)
			printf("%s\n", buf);

		// printf("%d\n", pos);
	}
	return 0;
}
