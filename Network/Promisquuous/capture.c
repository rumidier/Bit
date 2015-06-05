#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MTU 1500

int
main (int argc,
      char *argv[])
{
	int sock, optval;
	char packet[MTU];

	struct sockaddr_in peer;
	struct iphdr *ip;
	struct ifreq ethreq;
	int n;
	int i;

	sock = socket (AN_INET, SOCK_RAW, AF_PACKET);

	strncpy (etherq.ifr_name, "eth0"

}
