#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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
		pos = strcmp(buf, "OFF\n");
		if (pos)
		{
			qsort(buf, r, 1, comp);
			write(cs, buf, r);
			//printf("%s\n", buf);
		}
		
		// printf("%d\n", pos);
	}
	close(cs);
	return 0;
}
