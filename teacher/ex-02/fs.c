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

	/* 현재 디렉토리에서 name을 가진 파일 찾기 */
	/* 실패하면 오류(FS_ERROR) 리턴 */
	
/*	fid = allocate_open_file_table(); */
	
	/* 해당 파일의 DIRENTRY를 읽어 open_file_table[fid] 에 채우기 */
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

	/* 이 디렉토리의 첫번째 엔트리 "." 이름을 가진 엔트리의
	   size는 이 디렉토리에 존재하는 파일의 개수를 가지고 있다. */
	Disk_ReadSector(first_sector, buf);
	files_in_dir = ep->size;	/* 현재 이 디렉토리에 존재하는 파일의 개수 */

	/* 현재 디렉토리에서 name을 가진 파일이 이미 존재하면 오류(FS_ERROR) 리턴 */	
	/* 현재 디렉토리에서 같은 이름을 가진 파일이 있는지를 모두 검사해야 한다 */
	/* fs_dir() 함수를 보고 작성할 것 */


	/* last_sector = 이 디렉토리의 맨 마지막 섹터 */
	last_sector = first_sector;
	while (FAT[last_sector] != (unsigned short) ~0) {
		last_sector = FAT[last_sector];
	}
	/* 만약 이 디렉토리에 파일 엔트리가 모두 차 있으면 */
	/* 새로운 섹터를 할당받아 디렉토리를 확장해야 한다 */
	if (((ep->size * sizeof(DIRENTRY_T)) % 512) == 0) {
		/* FAT를 보고 사요되지 않는 새로운 섹터를 할당 받는다 */
/*		new_sector = allocate_new_sector(); */
		/* 이 디레토리(cur_dir) 다음에 새로운 섹터가 연결되도록 FAT를 변경 */
/*		FAT[last_sector] = new_sector; */
/*		FAT[new_sector] = 0; */
/*		last_sector = new_sector; */
	}
	
	/* 이 디렉토리의 맨 마지막 엔트리에 새로운 파일을 기록한다 */
	/* last_sector = 이 디렉토리의 맨 마지막 섹터 */
	/* offset = last_sector에서 맨 마지막 엔트리가 존재하는 위치 */
	/* 0 <= offset <= 512-sizeof(DIRENTRY_T) */
	Disk_ReadSector(last_sector, buf);
	ep = (DIRENTRY_T *) (buf+offset);
	
	strncpy(ep->name, name, FILE_NAME);
	ep->size = 0;
	ep->status = FILE;
	ep->first_sector = 0;
	
	Disk_WriteSector(last_sector, buf);
	
	/* 이 디렉토리의 첫번째 엔트리 "." 이름을 가진 엔트리의
	   size는 이 디렉토리에 존재하는 파일의 개수를 가지고 있다.
	   이를 하나 증가시킨다 */

	ep = (DIRENTRY_T	*)buf;
	first_sector = cur_dir;	

	Disk_ReadSector(first_sector, buf);
	ep->size++;
	
	Disk_WriteSector(first_sector, buf);

/* 이제 디스크에 파일 생성이 끝났으면, open_file_table을 할당하고 디스크에서
   엔트리 정보를 읽어 이곳으로 복사한다. */
/*	fid = allocate_open_file_table(); */

	open_file_table[fid].used = TRUE;

	/* 해당 파일의 DIRENTRY를 읽어 open_file_table[fid] 에 채우기 */
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

	/* open_file_table[fid].rwoffset 위치부터 size 만큼 파일 데이타를 읽어서
	r_buf로 복사한다 */
	/* 읽기가 끝나면 rwoffset을 증가시킨다 */
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

	/* open_file_table[fid].rwoffset 위치부터 size 만큼 w_buf에서 읽어서
	기록한다 */
	
	/* 쓰기가 끝나면 rwoffset을 증가시킨다 */
	open_file_table[fid].rwoffset += size;

	
	SM_V();
	return(write_count);
}

int fs_closefile(int fid)
{
	SM_P();

	if (open_file_table[fid].used != TRUE) {
		/* 오류 리턴 */
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

	/* 현재 디렉토리에서 name을 가지는 파일을 찾는다 */
	/* 존재하지 않으면 오류 리턴 */
	/* 존재하면 디렉토리 엔트리를 지운다 */	

	/* 이 디렉토리의 첫번째 엔트리 "." 이름을 가진 엔트리의
	   size는 이 디렉토리에 존재하는 파일의 개수를 가지고 있다.
	   이를 하나 감소시킨다 */

	/* 만약 이 파일이 디렉토리의 맨 마지막에 위치하고 있으면
	   아무것도 할 필요 없이 리턴 */
	/* 아니면 맨 마지막 엔트리를 방금 지운 엔트리로
	   복사한다. (디렉토리 압축) */
	/* 맨 마지막 엔트리를 지운다 */
	/* 맨 마지막 엔트리가 디렉토리의 맨 마지막 섹터에서 offset 0이면
	   디렉토리의 맨 마지막 섹터를 반환한다 */
	/* FAT 를 적절히 변경한다 */

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

