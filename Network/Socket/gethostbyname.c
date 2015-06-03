#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int
main (int argc,
      char *argv[])
{
  char *ptr, **pptr;
  char str[20], temp[20];
  struct hostent *hptr;
  struct sockaddr_in ip_addr;
  const u_char *p;
  int i;

  if ( (hptr = gethostbyname(argv[1])) == NULL) {
    printf("gethosbyname error\n");
    exit(1);
  }

  printf("official hostname: %s\n", hptr->h_name);

  for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
    printf("\talias: %s\n", *pptr);

  printf("Address Length: %d\n", hptr->h_length);

  for (pptr=hptr->h_addr_list, i=0; *pptr !=NULL; pptr++, i++) {
    // p = (const u_char *)hptr->h_addr_list[i];
    /*
     p = (const u_char *)*pptr;
     sprintf("temp, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
     printf("address: %s\n", temp);
     */
    ip_addr.sin_addr.s_addr = *(unsigned long *)hptr->h_addr_list[i];
    printf("address: %s\n", inet_ntoa(ip_addr.sin_addr));
  }

  return 0;
}
