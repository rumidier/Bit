#if 1
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#define DEVICE_NAME		"ioctl_test"
#define DEVICE_MAJOR	200

int my_open(struct inode *inode, struct file *filp)
{
	printk("my_open()\n");
	return 0;
}
int my_close(struct inode *inode, struct file *file)
{
	printk("my_close()\n");
	return 0;
}

//#define LED_ON	1
#define LED_ON			_IO('c',1)
#define LED_RATIO		_IOW('c', 2, int)
#define LED_RATIO_READ	_IOR('c', 3, int)
long my_ioctl(struct file *flip, unsigned int cmd, unsigned long opt)
{
	int ratio,size, ret;
	printk("my_ioctl()\n");

	if(_IOC_TYPE(cmd) != 'c')
	{
		printk("type error\n");
		return EINVAL;
	}
	printk("_IOC_TYPE\n");
	if(_IOC_NR(cmd) < 1 || _IOC_NR(cmd) > 3)
	{
		printk("nr error\n");
		return EINVAL;
	}
	printk("_IOC_NR\n");

	if(_IOC_DIR(cmd) == _IOC_WRITE)
	{
		size = _IOC_SIZE(cmd);
		ret = copy_from_user((void*)&ratio, (const void*)opt, size);
	}
	printk("_IOC_DIR\n");
	if(_IOC_DIR(cmd) == _IOC_READ)
	{
		ratio = 100;
		size = _IOC_SIZE(cmd);
		ret = copy_to_user((void*)opt, (const void*)&ratio, size);
	}
	printk("_IOC_DIR_READ\n");
	switch(cmd)
	{
		case LED_ON: printk("LED_ON\n");	 break;
		case LED_RATIO: printk("LED_RATIO = %d\n", ratio);	break;
		case LED_RATIO_READ: printk("LED_RATIO_READ = %d\n", ratio);	break;
	}
	return 0;
}
static struct file_operations fops=
{
	.open			= my_open,
	.release		= my_close,
	.unlocked_ioctl	= my_ioctl,
};

static int __init ioctl_init(void)
{
	int result;
	result = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &fops);

	if(result < 0)
	{
		printk("unable to register devices %s\n", DEVICE_NAME);
		return result;
	}
	return 0;
}

static void __exit ioctl_exit(void)
{
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
	printk("rmmod %s\n", DEVICE_NAME);
}
MODULE_LICENSE("GPL");
module_init(ioctl_init);
module_exit(ioctl_exit);
#endif
