#if 1
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void my_ls( char *dname )
{
	DIR *dp;
	struct dirent *p;
	struct stat buf;
	chdir(dname);
	dp = opendir(".");
	printf("%s : ", dname );
	while( p = readdir( dp ))
	{
		printf("%s ", p->d_name );
	}
	printf("\n");

	rewinddir(dp);
	while( p = readdir( dp ))
	{
		lstat(p->d_name, &buf);
		if( S_ISDIR(buf.st_mode) )
		{
			if( strcmp( p->d_name, "." ) && strcmp( p->d_name, ".." ) )
				my_ls(p->d_name);
		}
	}
	closedir(dp);
	chdir("..");
}

int main()
{
	my_ls(".");
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


void my_ls( char *dname )
{
	DIR *dp;
	struct dirent *p;
	struct stat buf;
	chdir(dname);
	dp = opendir(".");
	while( p = readdir( dp ))
	{
		lstat(p->d_name, &buf);
		printf("%s\n", p->d_name );

		if( S_ISDIR(buf.st_mode) )
		{
			if( strcmp( p->d_name, "." ) && strcmp( p->d_name, ".." ) )
				my_ls(p->d_name);
		}
	}
	closedir(dp);
	chdir("..");
}

int main()
{
	my_ls(".");
	return 0;
}
#endif


#if 0
#include <stdio.h>
#include <dirent.h>

void my_ls( char *dname )
{
	DIR *dp;
	struct dirent *p;
	chdir(dname);
	dp = opendir(".");
	while( p = readdir( dp ))
		printf("%s\n", p->d_name );
	closedir(dp);
	chdir("..");
}

int main()
{
	my_ls(".");
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <dirent.h>

int main()
{
	DIR *dp;
	struct dirent *p;
	dp = opendir(".");
	while( p = readdir( dp ))
		printf("%s\n", p->d_name );
	closedir(dp);
	return 0;
}
#endif
