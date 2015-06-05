#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/ip.h>
#include <linux/udp.h>

unsigned short in_cksum(unsigned short *addr, int len);

int
main (int argc,
      char *argv[])
{
	int sock, optval;
	char *packet, *buffer;

	struct udphdr *udp;
	struct pseudohdr {
		unsigned long saddr;
		unsigned long daddr;
		char useless;
		unsigned char protocol;
		unsigned short length;
	} pseudo;
	struct sockaddr_in peer;
	struct iphdr *ip;

	ip     = (struct iphdr *) malloc(sizeof(struct iphdr));
	udp    = (struct udphdr *) malloc(sizeof(struct udphdr));
	packet = (char *) malloc(sizeof(struct iphdr) + sizeof(struct udphdr) + 12);
	buffer = (char *) malloc(sizeof(struct iphdr) + sizeof(struct udphdr) + 12);

	ip  = (struct iphdr *) packet;
	udp = (struct udphdr *) (packet + sizeof(struct iphdr));

	ip->ihl      = 5;
	ip->version  = 4;
	ip->tos      = 0;
	ip->tot_len  = sizeof(struct iphdr) + sizeof(struct udphdr) + 12;
	ip->id       = htons(getuid());
	ip->ttl      = 255;
	ip->protocol = IPPROTO_UDP;
	ip->saddr    = inet_addr("127.0.0.1");
	ip->daddr    = inet_addr("127.0.0.1");
	sock         = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int));

	pseudo.saddr    = inet_addr("127.0.0.1");
	pseudo.daddr    = inet_addr("127.0.0.1");
	pseudo.useless  = htons(0);
	pseudo.protocol = IPPROTO_UDP;
	pseudo.length   = sizeof(struct udphdr) + 12;

	udp->source = htons(5000);
	udp->dest   = htons(7);
	udp->len    = htons(sizeof(struct udphdr) + 12);
	udp->check  = in_cksum((unsigned short *)&pseudo, sizeof(struct udphdr) + sizeof(struct pseudohdr) + 12);
	ip->check   = in_cksum((unsigned short *)ip, sizeof(struct iphdr));

	strcpy((packet+sizeof(struct iphdr) + sizeof(struct udphdr)), "Hello World");
	peer.sin_family      = AF_INET;
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	peer.sin_port        = htons(7);

	sendto(sock, packet, ip->tot_len, 0, (struct sockaddr *)&peer, sizeof(struct sockaddr));

	memset (buffer, 0, (size_t) sizeof(buffer));
	recv(sock, buffer, sizeof(struct iphdr) + sizeof(struct udphdr) + 13, 0);

	buffer += (sizeof(struct iphdr) + sizeof(struct udphdr));
	printf("Reply from Echo server:\t%s\n", buffer);

	close(sock);

	return 0;
}

unsigned short in_cksum(unsigned short *addr, int len)
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
		*(u_char *)(&answer) = *(u_char *)w;
		sum += answer;
	}

	sum   = (sum >> 16) + (sum & 0Xffff);
	sum   += (sum >> 16);
	answer = ~sum;

	return (answer);
}
