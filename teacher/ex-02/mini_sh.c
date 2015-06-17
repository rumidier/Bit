#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "fs.h"

#define FALSE	0
#define TRUE	1

#define EOL	1
#define ARG	2


char		*input;
static char	tokens[512];
char		*ptr, *tok;

main()
{
    	char	combuf[256];

	printf("msh # ");
	input = combuf;
	while (gets(input)) {
		parse_and_execute(input);
		printf("msh # ");
	}
}


int get_token(char **outptr)
{
	int	type;

	*outptr = tok;
	while ((*ptr == ' ') || (*ptr == '\t')) ptr++;

	*tok++ = *ptr;

	switch (*ptr++) {
		case '\0' : type = EOL; break;
		default : type = ARG;
			while ((*ptr != ' ') && (*ptr != '&') &&
				(*ptr != '\t') && (*ptr != '\0'))
				*tok++ = *ptr++;
	}
	*tok++ = '\0';
	return(type);
}

int execute(char **comm)
{
	int	pid;

	if ((pid = fork()) < 0) {
		fprintf(stderr, "minish : fork error\n");
		return(-1);
	}
	else if (pid == 0) {
		execl("/bin/sh", "sh", "-c", input, (char *) 0);
//		execvp(*comm, comm);
		fprintf(stderr, "minish : command not found\n");
		exit(127);
	}
	while (waitpid(pid, NULL, 0) < 0)
		if (errno != EINTR) return -1;
	return 0;
}


int parse_and_execute(char *input)
{
	char	*arg[512];
	int	type;
	int	quit = FALSE;
	int	narg = 0;
	int	finished;

	ptr = input;
	tok = tokens;
	for (finished = 0; !finished; ) {
		switch (type = get_token(&arg[narg])) {
		case ARG :
			narg++;
			break;
		case EOL :
			if (!strcmp(arg[0], "quit")) exit(1);
			else if (!strcmp(arg[0], "exit")) exit(1);
			else if (!strcmp(arg[0], "format")) fs_format();
			else if (!strcmp(arg[0], "mount")) {
				int	err;
				
				err = fs_mount();
				if (err != FS_SUCCESS) printf("mount error, error code = %d\n", err);
			}
			else if (!strcmp(arg[0], "umount")) fs_unmount();
			else if (!strcmp(arg[0], "dir")) fs_dir();
			else if (!strcmp(arg[0], "del")) {
				if (narg > 1)
					fs_removefile(arg[1]);
			}
			else if (!strcmp(arg[0], "mkfile")) {
				if (narg > 2) makefile(arg[1], atoi(arg[2]));
			}
			else if (!strcmp(arg[0], "type")) {
				if (narg > 1) {
					int	i, fid;
					int	readcount;
					char	buf[512];
					
					fid = fs_openfile(arg[1]);
					if (fid >= 0) {
						readcount = fs_readfile(buf, 512);
						while (readcount > 0) {
							for (i = 0; i < readcount; i++)
								putchar(buf[i]);
							readcount = fs_readfile(buf, 512);
						}
					}
				}
			}
			else if (!strcmp(arg[0], "mkdir")) fs_mkdir(arg[1]);
			else if (!strcmp(arg[0], "rmdir")) fs_rmdir(arg[1]);
			else if (!strcmp(arg[0], "cd")) fs_cd(arg[1]);
			else if (strcmp(arg[0], "")) printf("Invalid Command\n");

			narg = 0;
			finished = 1;
			break;
		}
	}
}


int makefile(char *fname, int size)
{
	int	i, fid, wrcount, written;
	char	buf[512];

	for (i = 0; i < 512; i++) buf[i] = 'a' + (i % ('z'-'a'));
	fid = fs_createfile(fname);
	if (fid < 0) {
		printf("Flash file create error code = %d\n", fid);
		return;
	}
	while (size > 0) {
	    	wrcount = (size >= 512) ? 512 : size;
		written = fs_writefile(fid, buf, wrcount);
		if (written != wrcount) {
			printf("Flash File write error\n");
			break;
		}
		size -= 512;
	}
	fs_closefile(fid);
	return;
}
