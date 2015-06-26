/*
 * H-Smart4412TKU IEB Board - FND
 *
 * by yoonmk
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/delay.h>

#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/ioport.h>

#include <asm/io.h>
#include <asm/delay.h>
#include <asm/irq.h>

#include <mach/map.h>
#include <mach/gpio.h>

#include <asm/gpio.h>
#include <mach/regs-gpio.h>

#include <plat/gpio-cfg.h>

// Device Address
#define LED     0x0A
#define FND     0x0B
#define CLCD    0x0C

#define ADDR_PIN_L_0(x)           EXYNOS4212_GPM0(x+1)
#define ADDR_PIN_L_1(x)           EXYNOS4212_GPM1(x)

#define ADDR_PIN_H_1(x)           EXYNOS4212_GPM1(x+1)

#define DATA_PIN_2(x)             EXYNOS4212_GPM2(x)
#define DATA_PIN_3(x)             EXYNOS4212_GPM3(x)
#define DATA_PIN_4(x)             EXYNOS4212_GPM4(x)
#define DATA_PIN_0(x)             EXYNOS4212_GPM0(x)

#define SEL(x)           ADDR_PIN_H_1(x)

#define DEVICE_NAME 	"fnd3"
#define DEVICE_MAJOR    201

#define     MAX_FND  4//우리 FND는 4개이므로

static char disp[MAX_FND] = {0};

static int n = 0;

unsigned char FND_DATA_TBL[]={//데이터핀에 보낼 데이터종류
	//앞에서부터 0,1,2....로 FND에 표현됨
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,
	0x83,0xC6,0xA1,0x86,0x8E,0xC0,0xF9,0xA4,0xB0,0x99,0x89
};

static struct timer_list timer_str;
static void timer_function( unsigned long ptr);
static void init_add_timer(void);
static void remove_timer(void);
//이 함수는 GPIO핀들을할당하고 초기화시켜주는 함수임
//인자 없음
static void gpio_init(void){
	int i;

	//fpga data gpio init - gpm2_0~2
	for(i=0; i<3; i++){
		//이함수는 사용하고자하는 핀을 할당해주는 함수임.
		//첫번째인자 -사용하고자 하는 핀(반복문으로 3번도니까 3개를 할당)
		//두번째인자 -할당된 핀의 레이블(이름정도로 생각하면 될듯)
		gpio_request(DATA_PIN_2(i), "GPM2_0"); 
		
		//이 함수는 핀을 설정하는 함수임.
		//첫번째 인자-설정하고자하는 핀
		//두번째 인자-설정하고하는 값..뭘설정하냐면
		//요즘에는 같은 신호라도 여러의미로 해석이 가능한데
		//신호를 받았을때 어떻게 해석할건지를 설정하는거라고
		//생각하면 됨
		//우리가 쓰는 보드가 S3C6410인데 이 보드에서 핀을 설정하려면
		//아래함수는 쓰는거임.그래서 함수이름이 이럼.s3c의 gpio를 설정
		//두번째인자는 출력과 입력으로 설정하는 값이 들어가는데
		//아래에 보이는 매크로는 결론적으로 출력으로 설정한다는 뜻임
		s3c_gpio_cfgpin(DATA_PIN_2(i), S3C_GPIO_SFN(1));

		//아래함수는 GPIO포트를 출력으로 초기화하면서 초기화값을 두번째인자로
		//맞춰주는 함수임
		//첫번째인자 -출력으로 초기화할 핀
		//두번째인자 -초기화 값(초기화값이 1인건 아무것도 안하겠다는 뜻임)
		//0이면 불들어오니까 ㅋㅋ
		gpio_direction_output(DATA_PIN_2(i), 1);
	}
	//fpga data gpio init - gpm0_0
	for(i=0; i<1; i++){
                gpio_request(DATA_PIN_0(i), "GPM0_0");
        	s3c_gpio_cfgpin(DATA_PIN_0(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_0(i), 1);
        }
	//fpga data gpio init - gpm2_3~4
	for(i=3; i<5; i++){
                gpio_request(DATA_PIN_2(i), "GPM2_3");
        	s3c_gpio_cfgpin(DATA_PIN_2(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_2(i), 1);
        }
	//fpga data gpio init - gpm3_0~7
	for(i=0; i<2; i++){
                gpio_request(DATA_PIN_3(i), "GPM3_0");
        	s3c_gpio_cfgpin(DATA_PIN_3(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_3(i), 1);
        }
	//여기부터 주소핀 설정
	//gpio_set_value함수는 아래에서 자세하게 설명
	//여기서 왜 굳이 초기화를 시키고 0을 또
	//세팅하는지는 모르겠음
	//fpga address gpio init - gpm0_1~7 <= (0~6+1) //add 1
	for(i=0; i<7; i++){
		gpio_request(ADDR_PIN_L_0(i), "GPM0_1");
	        s3c_gpio_cfgpin(ADDR_PIN_L_0(i), S3C_GPIO_SFN(1));
		gpio_direction_output(ADDR_PIN_L_0(i), 0);
		gpio_set_value(ADDR_PIN_L_0(i), 0);
	}
	//fpga address gpio init - gpm1_0~0
        for(i=0; i<1; i++){
                gpio_request(ADDR_PIN_L_1(i), "GPM1_0");
                s3c_gpio_cfgpin(ADDR_PIN_L_1(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_L_1(i), 0);
                gpio_set_value(ADDR_PIN_L_1(i), 0);
        }
	//fpga address gpio init - gpm1_1~6
	for(i=0; i<6; i++){
		gpio_request(ADDR_PIN_H_1(i), "GPM1_1");
		s3c_gpio_cfgpin(ADDR_PIN_H_1(i), S3C_GPIO_SFN(1));
		gpio_direction_output(ADDR_PIN_H_1(i), 0);
		gpio_set_value(ADDR_PIN_H_1(i), 0);
	}

}
//이 함수는 주소핀들을 FND로 찾아가도록 설정하는 함수임
//약간의 설명을 하겠음 조금 어려우니 차근히 읽어보기바람
//위의 GPIO초기화 함수를 보면 어드레스핀이랑 데이터핀을
//따로 초기화시켰음.
//데이터핀의 역할은 우리가 느끼는 실질적인 신호를보내는거임
//데이터핀의 신호에따라 FND에 어떤숫자가 나올지 결정이됨
//어드레스핀은 FND를 찾고 또 FND의 어디로 가서 데이터를 줄지
//결정하는 신호를 보내는거임..즉 시그널을 FND로 보낼건지
//CLCD로 보낼건지등등을 결정하고 그 안에서도 어느부분을 SELECT해서
//신호를 받을건지를 설정하는거임
//우리가 C0라는 데이터신호를 보내면 0이 출력이 되는것은
//어드레스핀이 FND를 잘 찾아가서 가능한거임.
//그래서 아래함수는 인자로 VAL을 받는데
//val은 현재 FND로 디파인된 값을 인자로 받고있음
//FND를 인자로 받아서 어드레스핀을 FND에 맞게 설정해주는 함수임
//아..힘들구만
static void write_addr_l(unsigned char val){
	int i;

	for(i=0; i<7; i++){//val은 1바이트이므로 7번 반복하고 마지막반복은
		//아래에서 따로 해주고있음..이유는 모름
		if(val & (1<<i)){//제일 마지막비트부터 1인지 확인하는거임
			//아래함수는 GPIO포트로 값을 내보내는 함수임.
			//첫번째인자 GPIO핀 
			//두번째인자 내보낼 값
		    	gpio_set_value(ADDR_PIN_L_0(i), 1);
		}
		else{//1이 아닌경우
	        	gpio_set_value(ADDR_PIN_L_0(i), 0);
		}
	}
	if(val & (1 << 7))//이게 마지막비트 확인(왜 따로 했느지는 모름)
		gpio_set_value(ADDR_PIN_L_1(0), 1);
        else
                gpio_set_value(ADDR_PIN_L_1(0), 0);
}
//이건 데이터핀에 데이터를 보내는 함수임
//인자로 val을 받는데 이 인자는 위에 정의된
//FND_DATA_TBL의 값중 하나임 즉 실제 숫자를 표현할 데이터를 인자로받음
void FND_DATA(unsigned char val)
{
//각 비트들을 비교해서 1이면 1보내고
	//0이면 0보냄 별거없음..
	if(val & (1<<0))    gpio_set_value(DATA_PIN_2(0), 1);
    	else         	    gpio_set_value(DATA_PIN_2(0), 0);
    	if(val & (1<<1))    gpio_set_value(DATA_PIN_2(1), 1);
    	else                gpio_set_value(DATA_PIN_2(1), 0);
   	if(val & (1<<2))    gpio_set_value(DATA_PIN_2(2), 1);
    	else                gpio_set_value(DATA_PIN_2(2), 0);
    	
	if(val & (1<<3))    gpio_set_value(DATA_PIN_0(0), 1);
    	else                gpio_set_value(DATA_PIN_0(0), 0);
    	
	if(val & (1<<4))    gpio_set_value(DATA_PIN_2(3), 1);
    	else                gpio_set_value(DATA_PIN_2(3), 0);
 	if(val & (1<<5))    gpio_set_value(DATA_PIN_2(4), 1);
    	else                gpio_set_value(DATA_PIN_2(4), 0);
	
	if(val & (1<<6))    gpio_set_value(DATA_PIN_3(0), 1);
        else                gpio_set_value(DATA_PIN_3(0), 0);
	if(val & (1<<7))    gpio_set_value(DATA_PIN_3(1), 1);
        else                gpio_set_value(DATA_PIN_3(1), 0);
}
//이 함수는 4개의 FND중에 어디에 데이터를 찍을지를
//고르는 함수임
//인자인 val은 FND의 종류를 받는거임.
//끝에 4비트에 의해서 FND가 결정이 됨
//예를 들면 val의 끝에 4비트가 1110이면
//첫번째 FND에 데이터를 찍겠다는 뜻임(끝에부터 첫번째임)
void FND_SEL(unsigned char val)
{
	int i;//반복변수
	for(i=0; i<4; i++){//끝에 4비트만 확인하면 되므로 4번반복
		if(val & (1<<i)){
			//아래의 SEL(i)는 어드레스핀을 디파인한거임
		    	gpio_set_value(SEL(i), 1);
		}
		else{              
		    	gpio_set_value(SEL(i), 0);
		}
	}
}
//이 함수가 실질적으로 핀들에 값을 쓰는 함수임.
//첫번째인자 -FND번호
//두번째인자 -데이터값
//구조를 보면 주소값을 쓰고
//FND번호에 따라 FND선택해주고
//거기에 데이터를 보내는 구조임
void fnd_disp(int num, unsigned char val)
{
	write_addr_l(FND);//FND의 주소값으로 어드레스핀을 설정
	switch(num)//셀렉트할 FND번호 1이 제일 첫번째 FND
	{
		case 1:
			FND_SEL(~0x01);//첫번째 FND에 데이터를 찍겠다
			FND_DATA(val);	//보낼 데이터를 val이다
			break;
		case 2:
			FND_SEL(~0x02);
			FND_DATA(val);	
			break;
		case 3:
			FND_SEL(~0x04);
			FND_DATA(val);	
			break;
		case 4:
			FND_SEL(~0x08);
			FND_DATA(val);	
			break;
		default :   
			FND_SEL(~0x00);
			break;
	}
}
//FND를 초기화시키는 함수
//4개의 FND에 ff를 데이터로 보내므로
//모든FND는 불이 안들어옴
static void fnd_clear(void)
{
	fnd_disp(1, 0xff);
	fnd_disp(2, 0xff);
	fnd_disp(3, 0xff);
	fnd_disp(4, 0xff);
}
//타이머초기화함수

void init_add_timer(void)
{
	//timer_list구조체를 초기화시키는 함수,인자로 저형태로 정의된 변수의 주소를 넣음
	init_timer(&timer_str); // timer_str을 초기화시킴

	timer_str.function = &timer_function;//타이머가 작동시 부를 함수를 넣어줌
	timer_str.data = (unsigned long)n;//함수의 인자값
	timer_str.expires = jiffies + (HZ/100);//설정할 시간
//	timer_str.expires = jiffies + HZ;

	add_timer(&timer_str);//타이머에 등록해줌
}
//등록된 타이머해제
void remove_timer(void)
{
	del_timer(&timer_str);
}
//타이머가 작동할때 부를 함수
void timer_function(unsigned long ptr)
{
	++n;
	if(n>(MAX_FND))
		n=1;
	switch(n)
	{
		case 1: fnd_disp(1,disp[0]); break;
		case 2: fnd_disp(2,disp[1]); break;
		case 3: fnd_disp(3,disp[2]); break;
		case 4: fnd_disp(4,disp[3]); break;
		default : break;
	}
	init_add_timer();

}
//파일오퍼레이션에 넣을 함수

static int fnd_ioctl(struct inode *inode, struct file *file, unsigned int  cmd, unsigned long arg)
{
	switch(cmd)
	{
		case 1:
			{
				break;
			}
		case 2:
			{
				break;
			}
		
		default:
			return 0;
	}

   return 0;
}
//파일오퍼레이션에 넣을 함수

static int fnd_open(struct inode *minode, struct file *mfile)
{
	gpio_init();	

	init_add_timer();

	return 0;
}
//파일오퍼레이션에 넣을 함수

static int fnd_release(struct inode *minode, struct file *mfile)
{
	remove_timer();
	gpio_init();

	fnd_clear();
	return 0;
}
///파일오퍼레이션에 넣을 함수

static ssize_t fnd_write (struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
	write_addr_l(FND);
	memset(disp, 0, 4);
    	copy_from_user(disp, buf, count);
}
//파일오퍼레이션에 넣을 함수
static ssize_t fnd_read (struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
	return 0;
}
//파일오퍼레이션 변수 생성
//각 멤버는 함수포인터로 되어있고
//이름처럼 리드는 리드할때 스이고
//라이트는 라이트할때 쓰이는 함수다.
static struct file_operations fnd_fops = {
   .read       =   fnd_read,
   .write      =   fnd_write,
   .open       =   fnd_open,
   .release    =   fnd_release,
   .unlocked_ioctl      =   fnd_ioctl,
};

static int __init fnd_init(void){
	int result;
	struct class *fnd_class;
  	struct device *dev;
//어래함수는 커널 내부에 케릭터디바이스를 관리하는 배열인 chdev에 하나를 할당받아서
	//등록시켜주는 함수이다.
	//첫번째인자는 디파인된 메이저번호(이게 배열의 인덱스가됨..그러므로 중복x)
	//두번째인자는 디파인된 디바이스네임
	//세번째인자는 파일오퍼레이션구조체의 주소를 줌
	//반환값은 등록에 성공하면 major번호를 받고 실패하면 -EBUSY반납 즉 음수가 반환되면 
	//chdev에 등록실패한거임
	result = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &fnd_fops);
	if (result < 0) {
		printk("unable to register device %s\n", DEVICE_NAME);
		return result;
	}
	printk("H-Smart4412TKU IEB: register device %s\n", DEVICE_NAME);//디바이스 등록했다고 프린트함.
	//로그버퍼에 메세지가 남는다.dmesg를 통해 확인가능
	
	fnd_class = class_create(THIS_MODULE, DEVICE_NAME);//클레스 생성..잘못르겠음 클레스의 개념을
 	//디바이스드라이버를 생성함..dev폴더에 드라이버가 생성됨 앱을 돌릴때 여기에 생성된 드라이버를 참조함.
	dev = device_create(fnd_class, NULL, MKDEV(DEVICE_MAJOR,0), NULL, DEVICE_NAME);
	
	gpio_init();//GPIO들을 초기화시켜줌
	return 0;        
}

static void __exit fnd_exit(void){
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);//캐릭터디바이스를 해제해주는 함수,인자로 전달된 디바이스를 해제한다
//	remove_timer();
	gpio_init();//GPIO를 초기화시켜줌
}
MODULE_LICENSE("GPL");
module_init(fnd_init);//디바이스 등록(초기화)
module_exit(fnd_exit);//디바이스 해제
