#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    unsigned int	status;
    unsigned int	first_sector;
    unsigned int	attr;
    unsigned long	date;
    unsigned long	size;
    char	name[44];
} DIRENTRY_T;

int main(void)
{

	printf("### 1 Byte = 8 bit ###\n");
	printf("int : %d byte\n",sizeof(int));
	printf("unsigned int : %d byte\n",sizeof(unsigned int));
	printf("long int : %d byte\n",sizeof(long int));
	printf("unsigned long int : %d byte\n",sizeof(unsigned long int));
	printf("long long int : %d byte\n",sizeof(long long int));
	printf("float : %d byte\n",sizeof(float));
	printf("double : %d byte\n",sizeof(double));
	printf("long double : %d byte\n",sizeof(long double));
	printf("(void *) : %d byte\n",sizeof(void *));
	printf("\n");
	printf("INT_MAX = %d\n", INT_MAX);
	printf("UINT_MAX = %ud\n", UINT_MAX);
	printf("LONG_MAX = %ld\n", LONG_MAX);
	printf("ULONG_MAX = %lud\n", ULONG_MAX);

	printf("DRIENTRY_T [%ld]\n", sizeof (DIRENTRY_T));
	printf("dword [%d]\n", sizeof(DWORD));
	return 0;

}

//http://danamoni.tistory.com/entry/struct%EC%9D%98-size-%EA%B0%92%EC%9D%80
//struct의-size-값은
