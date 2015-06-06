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
#include <unistd.h>

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

  sock = socket (AF_INET, SOCK_RAW, AF_PACKET);

  strncpy (ethreq.ifr_name, "eth0", IFNAMSIZ);
  ioctl(sock, SIOCGIFFLAGS, &ethreq);
  ethreq.ifr_flags |= IFF_PROMISC;
  ioctl(sock, SIOCSIFFLAGS, &ethreq);

  while (1)
    {
      n = recv(sock, packet, sizeof(packet), 0);
      printf("------------------------------\n");
      printf("n[%d]\n", n);
      for (i=0; i<n; i++) {
        printf("%02x ", ((unsigned int)(packet[i])&0xff));
        if (i % 16 == 15) printf("\n");
      }
      printf("\n");
    }
  close (sock);

  return 0;
}
