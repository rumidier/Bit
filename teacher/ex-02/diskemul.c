#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "disk_driver.h"


char	ram_disk[512 * NO_OF_SECTORS];

int disk_delay(int millisecond)	/* Emulate disk read/rite delay */
{
	int	i, j;
	
	for (i = j = 0; i < 5000000; i++) {
		j += i;
		j -= i;
	}
}

int Disk_Stat()
{
	return(NO_OF_SECTORS);
}

int Disk_Open()
{
	return(DISK_SUCCESS);
}

int Disk_Close()
{
	return(DISK_SUCCESS);
}

int Disk_ReadSector(int sector, char *buf)
{
	int	i;
	char	*p;

	if ((sector < 0) 	&& (sector >= NO_OF_SECTORS))
		return(DISK_FAIL);
	p = ram_disk + (512 * sector);
	for (i = 0; i < 512; i++) {
		*(buf++) = *(p++);
	}
	disk_delay(1);
	return(DISK_SUCCESS);
}

int Disk_WriteSector(int sector, char *buf)
{
	int	i;
	char *p;

	if ((sector < 0) 	&& (sector >= NO_OF_SECTORS))
		return(DISK_FAIL);
	p = ram_disk + (512 * sector);
	for (i = 0; i < 512; i++) {
		*(p++) = *(buf++);
	}
	disk_delay(1);
	return(DISK_SUCCESS);
}


