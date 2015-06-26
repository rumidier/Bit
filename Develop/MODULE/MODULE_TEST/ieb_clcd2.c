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

#define DEVICE_NAME "clcd4"
#define DEVICE_MAJOR   233 

// Device Address
#define CLCD    0x0C

#define ADDR_PIN_L_0(x)           EXYNOS4212_GPM0(x+1)
#define ADDR_PIN_L_1(x)           EXYNOS4212_GPM1(x)

#define ADDR_PIN_H_1(x)           EXYNOS4212_GPM1(x+1)

#define DATA_PIN_2(x)             EXYNOS4212_GPM2(x)
#define DATA_PIN_3(x)             EXYNOS4212_GPM3(x)
#define DATA_PIN_4(x)             EXYNOS4212_GPM4(x)
#define DATA_PIN_0(x)             EXYNOS4212_GPM0(x)

#define RS			ADDR_PIN_H_1(0)
#define WR			ADDR_PIN_H_1(1)
#define EN			ADDR_PIN_H_1(2)

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

void CLCD_DATA(unsigned char val)
{
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

void clcd_rs(unsigned char val){
	gpio_set_value(RS, val);
}
void clcd_wr(unsigned char val){
	gpio_set_value(WR, val);
}
void clcd_en(unsigned char val){
	gpio_set_value(EN, val);
}

static void clcd_data_wr(unsigned char val)
{
	clcd_en(1);
	clcd_wr(0);
	clcd_rs(0);
	CLCD_DATA(val);

	clcd_en(0);
	clcd_wr(0);
	clcd_rs(0);
	CLCD_DATA(val);
}   

static void clcd_data_rs(unsigned char val)
{
	clcd_en(1);
	clcd_wr(0);
	clcd_rs(1);
	CLCD_DATA(val);

	clcd_en(0);
	clcd_wr(0);
	clcd_rs(1);
	CLCD_DATA(val);
}   

static void lcd_init(void)
{
	clcd_data_wr(0x3C); 
	mdelay(100);
	clcd_data_wr(0x0C); 
	mdelay(100);
	clcd_data_wr(0x01); 
	mdelay(100);
	clcd_data_wr(0x06); 
	mdelay(100);
    clcd_data_wr(0x80);
	mdelay(100);
}

static void string_out(char *str)
{
	char *s;
	int i=0;

	lcd_init();

	for (s=str; *s; s++){
		clcd_data_rs(*s); 
		if(i == 15) { 
			udelay(100);
			clcd_data_wr(0xC0); 
		}
		udelay(100);
		i++;
	}
}

static int clcd_ioctl(struct inode *inode, struct file *file, unsigned int  cmd, unsigned long arg)
{
	switch(cmd)
	{
		case 1:
			{
				string_out("http://hybus.net H-Smart4412TKU");
				string_out("H-Smart4412TKU Board Welcome!!");
				break;
			}
		case 2:
			{
				string_out("1234567890ABCDEFGHIJKLMNOPQRSTU");
				break;
			}
		
		default:
			return 0;
	}

   return 0;
}

static int clcd_open(struct inode *minode, struct file *mfile)
{
	gpio_init();	
	return 0;
}

static int clcd_release(struct inode *minode, struct file *mfile)
{
	gpio_init();
   return 0;
}

static ssize_t clcd_write (struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
	char data[32];

	write_addr_l(CLCD);

	memset(data, 0 , 32);
	copy_from_user(data, buf, count);

	string_out(data);

    return 0;   
}

static ssize_t clcd_read (struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
   return 0;
}

static struct file_operations clcd_fops = {
   .read       =   clcd_read,
   .write      =   clcd_write,
   .open       =   clcd_open,
   .release    =   clcd_release,
   .unlocked_ioctl      =   clcd_ioctl,
};
static int __init clcd_init(void){
	int result;
	struct class *clcd_class;
        struct device *dev;

	result = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &clcd_fops);
	if (result < 0) {
		printk("unable to register device %s\n", DEVICE_NAME);
		return result;
	}
	printk("H-Smart4412TKU IEB: register device %s\n", DEVICE_NAME);
 
	clcd_class = class_create(THIS_MODULE, DEVICE_NAME);
        dev = device_create(clcd_class, NULL, MKDEV(DEVICE_MAJOR,0), NULL, DEVICE_NAME);
	
	gpio_init();

	return 0;        

}
static void __exit clcd_exit(void){
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
	gpio_init();
}

MODULE_LICENSE("GPL");
module_init(clcd_init);
module_exit(clcd_exit);
