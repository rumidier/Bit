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

#define DEVICE_NAME  "dot"
#define DEVICE_MAJOR    232

#define ADDR_PIN_L_0(x)           EXYNOS4212_GPM0(x+1)
#define ADDR_PIN_L_1(x)           EXYNOS4212_GPM1(x)

#define ADDR_PIN_H_1(x)           EXYNOS4212_GPM1(x+1)

#define DATA_PIN_2(x)             EXYNOS4212_GPM2(x)
#define DATA_PIN_3(x)             EXYNOS4212_GPM3(x)
#define DATA_PIN_4(x)             EXYNOS4212_GPM4(x)
#define DATA_PIN_0(x)             EXYNOS4212_GPM0(x)

static struct timer_list timer_str;
static void timer_function( unsigned long ptr);
static void init_add_timer(void);
static void remove_timer(void);

static int n = 0;

unsigned char dot_data[8];
//unsigned char col[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
unsigned char col[9] = { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char clr[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };   //clr
unsigned char row[36][8] ={
	{0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C},   //0
	{0x08, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C},   //1
	{0x1C, 0x22, 0x02, 0x02, 0x1C, 0x20, 0x20, 0x3E},   //2
	{0x1C, 0x22, 0x02, 0x1C, 0x02, 0x02, 0x22, 0x1C},   //3
	{0x04, 0x0C, 0x14, 0x24, 0x44, 0x3E, 0x04, 0x04},   //4
	{0x1E, 0x20, 0x20, 0x1C, 0x02, 0x02, 0x22, 0x1C},   //5
	{0x3C, 0x40, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x3C},   //6
	{0x3E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},   //7
	{0x1C, 0x22, 0x22, 0x1C, 0x22, 0x22, 0x22, 0x1C},   //8
	{0x1C, 0x22, 0x22, 0x22, 0x1E, 0x02, 0x02, 0x02},   //9
	{0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42},   //A
	{0x78, 0x44, 0x44, 0x78, 0x44, 0x44, 0x44, 0x78},   //B
	{0x1C, 0x22, 0x20, 0x20, 0x20, 0x20, 0x22, 0x1C},   //C
	{0x38, 0x44, 0x42, 0x42, 0x42, 0x42, 0x44, 0x38},   //D
	{0x3E, 0x20, 0x20, 0x3E, 0x20, 0x20, 0x20, 0x3E},   //E
	{0x3E, 0x20, 0x20, 0x3E, 0x20, 0x20, 0x20, 0x20},   //F
	{0x1C, 0x22, 0x42, 0x40, 0x40, 0x47, 0x42, 0x3C},   //G
	{0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x42},   //H
	{0x1C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C},   //I
	{0x1C, 0x08, 0x08, 0x08, 0x08, 0x48, 0x48, 0x30},   //J
	{0x44, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44, 0x44},   //K
	{0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3E},   //L
	{0x81, 0xC3, 0xA5, 0x99, 0x81, 0x81, 0x81, 0x81},   //M
	{0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x42, 0x42},   //N
	{0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C},   //O
	{0x7C, 0x42, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40},   //P
	{0x38, 0x44, 0x82, 0x82, 0x82, 0x8A, 0x44, 0x3A},   //Q
	{0x7C, 0x42, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42},   //R
	{0x3C, 0x42, 0x40, 0x3C, 0x02, 0x02, 0x42, 0x3C},   //S
	{0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},   //T
	{0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C},   //U
	{0x81, 0x42, 0x42, 0x42, 0x24, 0x24, 0x24, 0x18},   //V
	{0x81, 0x99, 0x99, 0x99, 0x99, 0x99, 0x5A, 0x24},   //W
	{0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81},   //X
	{0x81, 0x81, 0x42, 0x42, 0x3C, 0x18, 0x18, 0x18},   //Y
	{0xFF, 0x03, 0x02, 0x04, 0x08, 0x10, 0x60, 0xFF}    //Z
};

static void gpio_init(void){
	int i;

	//fpga data gpio init - gpm2_0~2
        for(i=0; i<3; i++){
                gpio_request(DATA_PIN_2(i), "GPM2_0");
                s3c_gpio_cfgpin(DATA_PIN_2(i), S3C_GPIO_SFN(1));
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
                gpio_request(DATA_PIN_2(i), "GPM2_0");
                s3c_gpio_cfgpin(DATA_PIN_2(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_2(i), 1);
        }
        //fpga data gpio init - gpm3_0~7
        for(i=0; i<2; i++){
                gpio_request(DATA_PIN_3(i), "GPM3_0");
                s3c_gpio_cfgpin(DATA_PIN_3(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_3(i), 1);
        }
	//fpga address gpio init - gpm0_1~7 <= (0~6+1) //add 1
        for(i=0; i<7; i++){
                gpio_request(ADDR_PIN_L_0(i), "GPM0_0");
                s3c_gpio_cfgpin(ADDR_PIN_L_0(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_L_0(i), 0);
                gpio_set_value(ADDR_PIN_L_0(i), 0);
        }
        //fpga address gpio init - gpm1_0~0
        for(i=0; i<1; i++){
                gpio_request(ADDR_PIN_L_1(i), "GPM0_0");
                s3c_gpio_cfgpin(ADDR_PIN_L_1(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_L_1(i), 0);
                gpio_set_value(ADDR_PIN_L_1(i), 0);
        }
        //fpga address gpio init - gpm1_1~6
        for(i=0; i<6; i++){
                gpio_request(ADDR_PIN_H_1(i), "GPM1_0");
                s3c_gpio_cfgpin(ADDR_PIN_H_1(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_H_1(i), 0);
                gpio_set_value(ADDR_PIN_H_1(i), 0);
        }
}

void DOT_DATA(unsigned char val){

 if(val & (1<<0))    gpio_set_value(DATA_PIN_2(0), 1);
        else                gpio_set_value(DATA_PIN_2(0), 0);
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

static void write_addr_l(unsigned char val){
	int i;

	for(i=0; i<7; i++){
                if(val & (1<<i)){
                        gpio_set_value(ADDR_PIN_L_0(i), 1);
                }
                else{
                        gpio_set_value(ADDR_PIN_L_0(i), 0);
                }
        }
        if(val & (1 << 7))
                gpio_set_value(ADDR_PIN_L_1(0), 1);
        else
                gpio_set_value(ADDR_PIN_L_1(0), 0);
}
void dot_disp(int num, unsigned char val)
{
	write_addr_l(~col[num]);
	udelay(1);
	DOT_DATA(~val);
	udelay(1);
}

void dot_clr(){
	int i;
	for( i = 0; i < 8; i++ )
	{
		write_addr_l(~col[i]);
		udelay(1);
		DOT_DATA(~clr[i]);
		udelay(1);
	}
}

void init_add_timer(void)
{
	init_timer(&timer_str); // timer

	timer_str.function = &timer_function;
	timer_str.data = (unsigned long)n;
	timer_str.expires = jiffies + (HZ/1000);

	add_timer(&timer_str);
}

void remove_timer(void)
{
	del_timer(&timer_str);
}

void timer_function(unsigned long ptr)
{
	static int r=0;
	int i=0,j;

	if( n > 8)
		n = 0;

	for(j=0;j<60;j++)
	{
		for(i=0;i<9;i++)
		{
			dot_disp(i, row[r][i]);
//			dot_disp(i, row[11][i]);
			mdelay(1);
		}
	}

	if(!(r%36))
		r=0;
	r++;
	
//	dot_disp(n, dot_data[n]);

	mod_timer(&timer_str, jiffies+HZ/100);
//	init_add_timer();
}

void dot_test(void){
	int i, j, k;

	for( k = 0; k < 36; k++ ){
		for( j = 0; j < 2000; j++ ){
			for( i = 0; i < 8; i++ ){
				DOT_DATA(~row[k][i]);
				
				write_addr_l(~col[i]);
			}
		}
	}
}

static int dot_ioctl(struct inode *inode, struct file *file, unsigned int  cmd, unsigned long arg)
{
	return 0;
}

static int dot_open(struct inode *minode, struct file *mfile)
{
	gpio_init();  
	dot_clr();

	init_add_timer();

	return 0;
}

static int dot_release(struct inode *minode, struct file *mfile)
{
	remove_timer();
	gpio_init();

	dot_clr();
	return 0;
}

static ssize_t dot_write (struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
	copy_from_user(&dot_data[0], buf, count);

	return 0;
}

static ssize_t dot_read (struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
	return 0;
}
static struct file_operations dot_fops = {
	.read       =   dot_read,
	.write      =   dot_write,
	.open       =   dot_open,
	.release    =   dot_release,
	.unlocked_ioctl      =   dot_ioctl,
};

static int __init dot_init(void){
	int result;
	struct class *dot_class;
        struct device *dev;

	result = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &dot_fops);
	if (result < 0) {
		printk("unable to register device %s\n", DEVICE_NAME);
		return result;
	}
	printk("H-Smart4412TKU IEB: register device %s\n", DEVICE_NAME);
	
	dot_class = class_create(THIS_MODULE, DEVICE_NAME);
        dev = device_create(dot_class, NULL, MKDEV(DEVICE_MAJOR,0), NULL, DEVICE_NAME);
	
	init_add_timer();	
	gpio_init();

	return 0;
}

static void __exit dot_exit(void){
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);

	remove_timer();
	gpio_init();
}

MODULE_LICENSE("GPL");
module_init(dot_init);
module_exit(dot_exit);


