#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main()
{
    struct passwd *lpwd;
    printf("UID    : %d\n",getuid());
    printf("EUID   : %d\n" ,geteuid());

    lpwd = getpwuid(getuid());
    printf("UNAME  : %s\n", lpwd->pw_name);

    lpwd = getpwuid(geteuid());
    printf("EUNAME : %s\n", lpwd->pw_name);

}
