// ./a.out -li 
#include <stdio.h>

#define  L_FLAG   1
#define  I_FLAG   2

int main( int argc, char **argv )
{
	int ret;
	int flag = 0;
	
	while( (ret = getopt( argc, argv, "li" )) != -1 )
	{
		switch( ret )
		{
			case 'l' : flag |= L_FLAG;  break;
			case 'i' : flag |= I_FLAG;  break;
		}
	}

	if( flag & L_FLAG )
		printf("L option\n"); 

	if( flag & I_FLAG )
		printf("I option\n"); 
	return 0;
}
