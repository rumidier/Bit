#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

unsigned short in_cksum(unsigned short *addr, int len);

int
main (int argc,
      char *argv[])
{
	int sock, optval;
	char *packet, *buffer;

	struct icmphdr *icmp;

	struct sockaddr_in peer;
	struct iphdr *ip;

	ip     = (struct iphdr *) malloc (sizeof(struct iphdr));
	icmp   = (struct icmphdr *) malloc (sizeof(struct icmphdr));
	packet = (char *) malloc (sizeof(struct iphdr) + sizeof(struct icmphdr));
	buffer = (char *) malloc (sizeof(struct iphdr) + sizeof(struct icmphdr));

	ip   = (struct iphdr *) packet;
	icmp = (struct icmphdr *) (packet + sizeof(struct iphdr));

	ip->ihl      = 5;
	ip->version  = 4;
	ip->tos      = 0;
	ip->tot_len  = sizeof(struct iphdr) + sizeof(struct icmphdr);
	ip->id       = htons (getuid());
	ip->ttl      = 255;
	ip->protocol = IPPROTO_ICMP;
	ip->saddr    = inet_addr ("203.240.200.31");
	ip->daddr    = inet_addr ("203.240.200.1");

	sock = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP);
	setsockopt (sock, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int));
	icmp->type             = ICMP_ECHO;
	icmp->code             = 0;
	icmp->un.echo.id       = 0;
	icmp->un.echo.sequence = 0;
	icmp->checksum         = 0;

	icmp->checksum = in_cksum ( (unsigned short *)icmp, sizeof(struct icmphdr) );
	ip->check      = in_cksum ( (unsigned short *)ip,   sizeof(struct iphdr) );

	peer.sin_family      = AF_INET;
	peer.sin_addr.s_addr = inet_addr("203.240.200.1");
	sendto ( sock, packet, ip->tot_len, 0, (struct sockaddr *)&peer, sizeof(struct sockaddr) );

	recv (sock, buffer, sizeof(struct iphdr) + sizeof(struct icmphdr), 0);
	printf("Received the ECHO REPLU\n");

	close(sock);

	return 0;
}

unsigned short in_cksum (unsigned short *addr, int len)
{
	register int sum    = 0;
	u_short answer      = 0;
	register u_short *w = addr;
	register int nleft  = len;

	while (nleft > 1)
	{
		sum   += *w++;
		nleft -= 2;
	}

	if (nleft == 1) {
		*(u_char *)(&answer) = *(u_char *) w;
		sum += answer;
	}

	sum = (sum >> 16) + (sum &0xffff);
	answer = ~sum;

	return (answer);
}
