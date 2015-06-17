#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disk_driver.h"
#include "fs.h"

#define FALSE	0
#define TRUE	1

/* Write semaphore function for your OS and machine */
#define	SM_P();	;
#define	SM_V();	;
#define	INIT_SM();	;
#define	FREE_SM();	;
#define	QUERY_SM_INIT()  (TRUE)	// test whether sm is created already
/* Semaphore Definition End */

/* Internal Functions */

#define SIGNATURE	0x3f238ce6
#define MAX_OPEN_FILE	32
#define FILE_NAME		44

/* status in  DIRENTRY_T has one of 3 values in the following */
#define	DELETED	0
#define	FILE	1
#define	DIR	2
//#pragma pack(4)

typedef struct {
    unsigned long	signature;
    unsigned int	no_of_sectors;
    unsigned int	FAT_start_sector;		/* FAT start sector */
    unsigned int	num_of_FAT_sectors;
    unsigned int	root_start;	/* root_start sector */
} BOOTRECORD_T; 	/* boot record */

BOOTRECORD_T	br;	/* boot record */

typedef struct {
    unsigned int	status;
    unsigned int	first_sector;
    unsigned int	attr;
    unsigned long	date;
    unsigned long	size;
    char	name[FILE_NAME];
} DIRENTRY_T;

static struct {
    unsigned short	status;
    unsigned int	first_sector;
    unsigned int	attr;
    unsigned long	date;
    unsigned long	size;
    char	name[FILE_NAME];

    int	used;
    int	rwoffset;
} open_file_table[MAX_OPEN_FILE];

static char	buf[512];
static unsigned short FAT[NO_OF_SECTORS];

int cur_dir;

int fillbyte(char *buf, char c, int size)
{
	for (; size > 0; size--) *(buf++) = c;
}

int write_FAT(int fat_start, int fat_sectors)
{
	int	i;
	char	*p;
	
	p = (char *) FAT;
	
	for (i = 0; i < fat_sectors; i++) {
		Disk_WriteSector(fat_start+i, p);
		p += 512;
	}	
}

int read_FAT(int fat_start, int fat_sectors)
{
	int	i;
	char	*p;
	
	p = (char *) FAT;
	
	for (i = 0; i < fat_sectors; i++) {
		Disk_ReadSector(fat_start+i, p);
		p += 512;
	}	
}

int fs_format()
{

	int	i, sectors, FAT_start, num_FAT_sectors, root_start;
	BOOTRECORD_T	*tmp_br;
	DIRENTRY_T		*ep;
	
	if (sizeof(DIRENTRY_T) % 64) {
		printf("DIR_ENTRY should be fit in 64 byte boundary, cur size = %ld\n", sizeof(DIRENTRY_T));
		exit(1);
	}

	SM_P();

	sectors = Disk_Stat();
	FAT_start = 1;
	num_FAT_sectors = (sectors * sizeof(ushort)) / 512;
	if ((sectors * sizeof(ushort)) % 512) num_FAT_sectors++;
	root_start = FAT_start + num_FAT_sectors;

	for (i = 0; i <= root_start; i++) FAT[i] = 0;
	for (; i < NO_OF_SECTORS; i++) FAT[i] = ~0;

	write_FAT(FAT_start, num_FAT_sectors);
	
	fillbyte(buf, '\0', 512);
	ep = (DIRENTRY_T *) buf;
	ep->status = DIR;
	ep->size = 2;	/* root dir has 2 entry, one is for "." and the other is for ".." */
	ep->first_sector = root_start;	/* it points itself */
	strncpy(ep->name, ".", FILE_NAME);
	ep++;
	ep->status = DIR;
	ep->first_sector = root_start;
	strncpy(ep->name, "..", FILE_NAME);
	
	Disk_WriteSector(root_start, buf);		/* Write root directory */

	fillbyte(buf, '\0', 512);
	tmp_br = (BOOTRECORD_T *) buf;

	tmp_br->signature = SIGNATURE;
	tmp_br->no_of_sectors = sectors;;
	tmp_br->num_of_FAT_sectors = num_FAT_sectors;
	tmp_br->FAT_start_sector = FAT_start;
	tmp_br->root_start = root_start;
	
	Disk_WriteSector(0, buf);		/* Write Boot record to sector 0 */

	SM_V();
	return(FS_SUCCESS);
}


int fs_mount()
{
	int	i;
	BOOTRECORD_T	*tmp_br;
	char	*p;
	
	SM_P();
	
	/* Mount Here */

	for (i = 0; i < MAX_OPEN_FILE; i++) {
		open_file_table[i].used = FALSE;
	}

	Disk_ReadSector(0, buf);

	tmp_br = (BOOTRECORD_T *) buf;
	if (tmp_br->signature != SIGNATURE) {
		SM_V();
		return(FS_FORMATERR);
	}

	br.signature = tmp_br->signature;
	br.no_of_sectors = tmp_br->no_of_sectors;
	br.FAT_start_sector = tmp_br->FAT_start_sector;
	br.num_of_FAT_sectors = tmp_br->num_of_FAT_sectors;
	br.root_start = tmp_br->root_start;	

	/* Now read FAT sectors from disk into FAT array */
	
	read_FAT(br.FAT_start_sector, br.num_of_FAT_sectors);
	
	/* Set current directory to root directory */
	cur_dir = br.root_start;
		
	SM_V();
	return(FS_SUCCESS);
}

int fs_unmount()
{
	SM_P();
	
	br.signature = 0L;
		
	SM_V();
	return(FS_SUCCESS);
}


int fs_openfile(char *name)
{
	int	fid = -1;

	SM_P();

	/* ���� ���丮���� name�� ���� ���� ã�� */
	/* �����ϸ� ����(FS_ERROR) ���� */
	
/*	fid = allocate_open_file_table(); */
	
	/* �ش� ������ DIRENTRY�� �о� open_file_table[fid] �� ä��� */
	/* rwoffset = 0 */

	SM_V();
	return(fid);	/* return open file id */
}

int fs_createfile(char *name)
{
	int	fid = -1;
	int	i, first_sector, last_sector, offset, files_in_dir;
	DIRENTRY_T	*ep;

	SM_P();

	ep = (DIRENTRY_T	*)buf;
	first_sector = cur_dir;	

	/* �� ���丮�� ù��° ��Ʈ�� "." �̸��� ���� ��Ʈ����
	   size�� �� ���丮�� �����ϴ� ������ ������ ������ �ִ�. */
	Disk_ReadSector(first_sector, buf);
	files_in_dir = ep->size;	/* ���� �� ���丮�� �����ϴ� ������ ���� */

	/* ���� ���丮���� name�� ���� ������ �̹� �����ϸ� ����(FS_ERROR) ���� */	
	/* ���� ���丮���� ���� �̸��� ���� ������ �ִ����� ��� �˻��ؾ� �Ѵ� */
	/* fs_dir() �Լ��� ���� �ۼ��� �� */


	/* last_sector = �� ���丮�� �� ������ ���� */
	last_sector = first_sector;
	while (FAT[last_sector] != (unsigned short) ~0) {
		last_sector = FAT[last_sector];
	}
	/* ���� �� ���丮�� ���� ��Ʈ���� ��� �� ������ */
	/* ���ο� ���͸� �Ҵ�޾� ���丮�� Ȯ���ؾ� �Ѵ� */
	if (((ep->size * sizeof(DIRENTRY_T)) % 512) == 0) {
		/* FAT�� ���� ������ �ʴ� ���ο� ���͸� �Ҵ� �޴´� */
/*		new_sector = allocate_new_sector(); */
		/* �� ���丮(cur_dir) ������ ���ο� ���Ͱ� ����ǵ��� FAT�� ���� */
/*		FAT[last_sector] = new_sector; */
/*		FAT[new_sector] = 0; */
/*		last_sector = new_sector; */
	}
	
	/* �� ���丮�� �� ������ ��Ʈ���� ���ο� ������ ����Ѵ� */
	/* last_sector = �� ���丮�� �� ������ ���� */
	/* offset = last_sector���� �� ������ ��Ʈ���� �����ϴ� ��ġ */
	/* 0 <= offset <= 512-sizeof(DIRENTRY_T) */
	Disk_ReadSector(last_sector, buf);
	ep = (DIRENTRY_T *) (buf+offset);
	
	strncpy(ep->name, name, FILE_NAME);
	ep->size = 0;
	ep->status = FILE;
	ep->first_sector = 0;
	
	Disk_WriteSector(last_sector, buf);
	
	/* �� ���丮�� ù��° ��Ʈ�� "." �̸��� ���� ��Ʈ����
	   size�� �� ���丮�� �����ϴ� ������ ������ ������ �ִ�.
	   �̸� �ϳ� ������Ų�� */

	ep = (DIRENTRY_T	*)buf;
	first_sector = cur_dir;	

	Disk_ReadSector(first_sector, buf);
	ep->size++;
	
	Disk_WriteSector(first_sector, buf);

/* ���� ��ũ�� ���� ������ ��������, open_file_table�� �Ҵ��ϰ� ��ũ����
   ��Ʈ�� ������ �о� �̰����� �����Ѵ�. */
/*	fid = allocate_open_file_table(); */

	open_file_table[fid].used = TRUE;

	/* �ش� ������ DIRENTRY�� �о� open_file_table[fid] �� ä��� */
	/* open_file_table[fid].rwoffset = 0 */

	
	SM_V();
	return(fid);	/* return created and then opened file id */
}

int fs_readfile(int fid, char *r_buf, int size)
{
	int	read_count = 0;
	
	SM_P();

	if (open_file_table[fid].used != TRUE) {
		SM_V();
		return(FS_ERROR);
	}

	/* open_file_table[fid].rwoffset ��ġ���� size ��ŭ ���� ����Ÿ�� �о
	r_buf�� �����Ѵ� */
	/* �бⰡ ������ rwoffset�� ������Ų�� */
	open_file_table[fid].rwoffset += size;

	SM_V();
	return(read_count);
}

int fs_writefile(int fid, char *w_buf, int size)
{
	int	write_count = 0;
	
	SM_P();

	if (open_file_table[fid].used != TRUE) {
		SM_V();
		return(FS_ERROR);
	}

	/* open_file_table[fid].rwoffset ��ġ���� size ��ŭ w_buf���� �о
	����Ѵ� */
	
	/* ���Ⱑ ������ rwoffset�� ������Ų�� */
	open_file_table[fid].rwoffset += size;

	
	SM_V();
	return(write_count);
}

int fs_closefile(int fid)
{
	SM_P();

	if (open_file_table[fid].used != TRUE) {
		/* ���� ���� */
		SM_V();
		return(FS_ERROR);
	}
	open_file_table[fid].used = FALSE;
	
	SM_V();
	return(FS_SUCCESS);
}

int fs_removefile(char *name)
{
	SM_P();

	/* ���� ���丮���� name�� ������ ������ ã�´� */
	/* �������� ������ ���� ���� */
	/* �����ϸ� ���丮 ��Ʈ���� ����� */	

	/* �� ���丮�� ù��° ��Ʈ�� "." �̸��� ���� ��Ʈ����
	   size�� �� ���丮�� �����ϴ� ������ ������ ������ �ִ�.
	   �̸� �ϳ� ���ҽ�Ų�� */

	/* ���� �� ������ ���丮�� �� �������� ��ġ�ϰ� ������
	   �ƹ��͵� �� �ʿ� ���� ���� */
	/* �ƴϸ� �� ������ ��Ʈ���� ��� ���� ��Ʈ����
	   �����Ѵ�. (���丮 ����) */
	/* �� ������ ��Ʈ���� ����� */
	/* �� ������ ��Ʈ���� ���丮�� �� ������ ���Ϳ��� offset 0�̸�
	   ���丮�� �� ������ ���͸� ��ȯ�Ѵ� */
	/* FAT �� ������ �����Ѵ� */

	SM_V();
	return(FS_SUCCESS);
}

int fs_mkdir(char *name)
{
	SM_P();
	
	SM_V();
	return(FS_SUCCESS);
}

int fs_rmdir(char *name)
{
	SM_P();
	
	SM_V();
	return(FS_SUCCESS);
}

int fs_cd(char *name)
{
	SM_P();
	
	SM_V();
	return(FS_SUCCESS);
}

int	fs_dir()
{
	int	i, sector, offset, files_in_dir;
	DIRENTRY_T	*ep;
	
	SM_P();
	ep = (DIRENTRY_T	*)buf;
	sector = cur_dir;	
	offset = 0;

	Disk_ReadSector(sector, buf);
	files_in_dir = ep->size;

	for (i = 0; i < files_in_dir; i++) {
		Disk_ReadSector(sector, buf);
		ep = (DIRENTRY_T *) (buf+offset);
		if (ep->status == DIR) printf("  %14s/ %ld", ep->name, ep->size);
		else printf("  14%s  %ld", ep->name, ep->size);	/* ep->status == FILE */
		offset += sizeof(DIRENTRY_T);
		if (offset == 512) {
			sector = FAT[sector];
			offset = 0;
		}
		if (!((i+1) % 4)) printf("\n");
	}
	printf("\n");

	SM_V();
	return(FS_SUCCESS);
}

