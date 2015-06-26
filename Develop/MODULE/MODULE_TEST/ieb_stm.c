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

#define DEVICE_NAME "stmotor"
#define DEVICE_MAJOR    234

// Device Address
#define STEP	0x0D

#define ADDR_PIN_L_0(x)           EXYNOS4212_GPM0(x+1)
#define ADDR_PIN_L_1(x)           EXYNOS4212_GPM1(x)

#define ADDR_PIN_H_1(x)           EXYNOS4212_GPM1(x+1)

#define DATA_PIN_2(x)             EXYNOS4212_GPM2(x)
#define DATA_PIN_3(x)             EXYNOS4212_GPM3(x)
#define DATA_PIN_4(x)             EXYNOS4212_GPM4(x)
#define DATA_PIN_0(x)             EXYNOS4212_GPM0(x)

#define ST_EN(x)  	ADDR_PIN_H_1(x)
#define ST_CTL 		ADDR_PIN_H_1(2)

static int ST_DELAY =  (HZ/100);

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
void STM_DATA(unsigned char val)
{
	if(val & (1<<0))    gpio_set_value(DATA_PIN_2(0), 1);
        else                gpio_set_value(DATA_PIN_2(0), 0);
        if(val & (1<<1))    gpio_set_value(DATA_PIN_2(1), 1);
        else                gpio_set_value(DATA_PIN_2(1), 0);
        if(val & (1<<2))    gpio_set_value(DATA_PIN_2(2), 1);
        else                gpio_set_value(DATA_PIN_2(2), 0);

        if(val & (1<<3))    gpio_set_value(DATA_PIN_0(0), 1);
        else                gpio_set_value(DATA_PIN_0(0), 0);

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

void STM_EN(unsigned char val)
{
	int i;
	for(i=0; i<2; i++){
		if(val & (1<<i))    gpio_set_value(ST_EN(i), 1);
		else                gpio_set_value(ST_EN(i), 0);
	}
}

void STM_DELAY(void)
{
  	udelay( 900 );
  	udelay( 900 );
  	udelay( 900 );
}

static void SMOTOR_CW(void)
{
	STM_DATA(0x01);
	STM_DELAY();

  	STM_DATA(0x02);
	STM_DELAY();

  	STM_DATA(0x04);
	STM_DELAY();

	STM_DATA(0x08);
	STM_DELAY();

	STM_DATA(0x00);
}

static void SMOTOR_CCW(void)
{
	STM_DATA(0x08);
    	STM_DELAY();

  	STM_DATA(0x04);
    	STM_DELAY();

  	STM_DATA(0x02);
    	STM_DELAY();

	STM_DATA(0x01);
    	STM_DELAY();

  	STM_DATA(0x00);
}

static void SMOTOR_CW_poll(int num)
{
	int i;

	gpio_set_value(ST_CTL, 0);
	
	for(i=0;i<num;i++)
    	{
        	STM_EN(0x03);

        	SMOTOR_CW();

        	STM_EN(0x00);
   	}
	gpio_set_value(ST_CTL, 1);
}

static void SMOTOR_CCW_poll(int num)
{
	int i;
	
	gpio_set_value(ST_CTL, 0);
    	
	for(i=0;i<num;i++)
    	{
        	STM_EN(0x03);

        	SMOTOR_CCW();

        	STM_EN(0x00);
    	}
	gpio_set_value(ST_CTL, 1);
}

static int stmotor_ioctl(struct file *file, unsigned int  cmd, unsigned long arg)
{
	int num = 0;
	printk("%s cmd[%d]\n", __func__, cmd);

	write_addr_l(STEP);

	switch(cmd)
	{
		case 1:
			copy_from_user(&num,(void *)arg,sizeof(num));
			printk("%s CW %d\n", __func__, num); 

			SMOTOR_CW_poll(num);
			break;
		case 3:
			copy_from_user(&num,(void *)arg,sizeof(num));
			printk("%s CCW %d\n", __func__, num); 

			SMOTOR_CCW_poll(num);
			break;
		case 2:
			copy_from_user(&ST_DELAY,(void *)arg,sizeof(ST_DELAY));
			printk("%s delay %d \n", __func__, ST_DELAY);
			break;
		default:
			return 0;
	}
	return 0;
}

static int stmotor_open(struct inode *minode, struct file *mfile)
{
	gpio_init();	

	return 0;
}

static int stmotor_release(struct inode *minode, struct file *mfile)
{
	gpio_init();
	return 0;
}

static ssize_t stmotor_write (struct file *file, const char *buf, 
		size_t count, loff_t *f_pos)
{
    return 0;   
}

static ssize_t stmotor_read (struct file *file, const char *buf, 
		size_t count, loff_t *f_pos)
{
	return 0;
}

static struct file_operations stmotor_fops = {
   .read       =   stmotor_read,
   .write      =   stmotor_write,
   .open       =   stmotor_open,
   .release    =   stmotor_release,
   .unlocked_ioctl      =   stmotor_ioctl,
};

static int __init stmotor_init(void){
	int result;
	struct class *stmotor_class;
        struct device *dev;

	result = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &stmotor_fops);
	if (result < 0) {
		printk("unable to register device %s\n", DEVICE_NAME);
		return result;
	}
	printk("H-Smart4412TKU IEB: register device %s\n", DEVICE_NAME);
	
	stmotor_class = class_create(THIS_MODULE, DEVICE_NAME);
        dev = device_create(stmotor_class, NULL, MKDEV(DEVICE_MAJOR,0), NULL, DEVICE_NAME);
	
	gpio_init();

	return 0;
}

static void __exit stmotor_exit(void){
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
	gpio_init();
}

MODULE_LICENSE("GPL");
module_init(stmotor_init);
module_exit(stmotor_exit);
