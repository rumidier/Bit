#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<string.h>

#define fnd_dev	"/dev/segment"
unsigned char FND_DATA_TBL[]={
		0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,
		0x83,0xC6,0xA1,0x86,0x8E,0xC0,0xF9,0xA4,0xB0,0x99,0x89
};
unsigned char fnd_num[4] = {0,};

void init_FND(void)
{
	int i;
	for(i=0;i<4;i++)
		fnd_num[i] = 0xff;
}

int sec_1(void)
{
	static int n = 0;
	fnd_num[3] = FND_DATA_TBL[n%10];
	
	return (n++);
}
void sec_2(int num)
{
	static int n = 0;
	fnd_num[2] = FND_DATA_TBL[n%6];

	if(!(num%10) && num)
		n++;
}

int FNDTest(char a, char b, char c, char d){

	fnd_num[0] = FND_DATA_TBL[a];
	fnd_num[1] = FND_DATA_TBL[b];
	fnd_num[2] = FND_DATA_TBL[c];
	fnd_num[3] = FND_DATA_TBL[d];

}

void main()
{

	int i;
	int k = 1;
	int fnd_fd = 0;


/*	for(i=0; i<9; i++){
		FNDTest(i,i,i,i);
		sleep(1);
	}
*/
	init_FND();
//	printf("exit : 0\n");
	while(k)	
	{
		
		sec_2(sec_1() + 1);
		fnd_fd = open(fnd_dev, O_RDWR);
	
		if(fnd_fd <0){
			printf("Can't Open Device\n");
		}
		write(fnd_fd, &fnd_num, sizeof(fnd_num));
		sleep(1);
//		scanf("%d", &k);	fflush(stdin);
	}

}
/*	eoF	*/
