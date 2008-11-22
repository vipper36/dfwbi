#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAXLINE 1024
typedef struct socket_addr SA;
int
udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp)
{
	int				sockfd, n;
	struct addrinfo	hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
	{
		printf("udp_client error for %s, %s: %s\n",
				 host, serv, gai_strerror(n));
		exit(0);
	}
	ressave = res;

	do {
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd >= 0)
			break;		/* success */
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL)	/* errno set from final socket() */
	{
		printf("udp_client error for %s, %s\n", host, serv);
		exit(0);
	}

	*saptr = (SA*)malloc(res->ai_addrlen);
	memcpy(*saptr, res->ai_addr, res->ai_addrlen);
	*lenp = res->ai_addrlen;

	freeaddrinfo(ressave);

	return(sockfd);
}

void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	while (fgets(sendline, MAXLINE, fp) != NULL) {

		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		recvline[n] = 0;	/* null terminate */
		fputs(recvline, stdout);
	}
}

int
main(int argc, char **argv)
{
	int					sockfd;
	socklen_t			salen;
	struct sockaddr		*sa;

	if (argc != 3)
	{
		printf("usage: udpcli02 <hostname> <service>\n");
		exit(0);
	}

	sockfd = udp_client(argv[1], argv[2], (void **) &sa, &salen);

	dg_cli(stdin, sockfd, sa, salen);

	exit(0);
}
