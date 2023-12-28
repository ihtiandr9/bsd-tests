/*
   Program opens tcp socket and recieve string 
   with '\n' at the end, sort chars in string by code
   and send it back. Will exit if recive 'OFF' string
 */
#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int comp(const void *elem1, const void *elem2)
{
	char f = *((char *)elem1);
	char s = *((char *)elem2);
	if (f < s)
		return 1;
	if (f > s)
		return -1;
	return 0;
}

int main(int argc, char *argv[])
{
	int ss = socket(AF_INET, SOCK_STREAM, 0);
	int cs;

        assert(argv[1]);
	struct sockaddr_in addr;
	inet_aton("127.0.0.1", &addr.sin_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));

	bind(ss, (struct sockaddr *)&addr, sizeof(addr));
	listen(ss, 5);

	cs = accept(ss, 0, 0);

	char buf[512];

	int pos = 1;
	buf[0] = 0;
	while (pos)
	{
		int r = read(cs, buf, 512);
		buf[r] = 0;
		pos = strncmp(buf, "OFF", 3);
		if (pos)
		{
			qsort(buf, r, 1, comp);
			write(cs, buf, r);
			//printf("%s\n", buf);
		}
                memset(buf, 0, 512);
		// printf("%d\n", pos);
	}
	close(cs);
	return 0;
}
