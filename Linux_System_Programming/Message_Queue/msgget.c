#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int CreateMQ(key)
long key;
{
	return (msgget(key, IPC_CREAT | 0777) );
}

int OpenMQ(key)
	long key;



