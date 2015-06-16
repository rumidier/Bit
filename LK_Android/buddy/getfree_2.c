#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gfp.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

int my_init(void)
{
	char *p;
	p = (char *)kmalloc(GFP_KERNEL, 32);
	p[0] = 'a';
	p[32-1] = 'z';
	printk("------------ slab memory test ----------\n");
	printk("%c   -    %c\n", p[0], p[32-1]);
	kfree(p);

	return 0;
}

void my_exit(void)
{
	printk("------------ slab test exit ----------\n");
}

module_init (my_init);
module_exit(my_exit);
