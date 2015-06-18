/*
Device driver 64p

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

int init_module()
{
	printk("module1 : init_module()\n");
	return 0;
}

void cleanup_module()
{
	printk("module : cleanup_module()\n");
}
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

int module_start ()
{
	printk("module1 : module_start()\n");
	return 0;
}

void module_end()
{
	printk("module : module_end()\n");
}

module_init(module_start);
module_exit(module_end);
