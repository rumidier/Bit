#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gfp.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int my_init(void)
{
	char *p;
	p = (char *)__get_free_pages(GFP_KERNEL, 0);
	p[0] = 'a';
	p[4096-1] = 'z';
	printk("------------ buddy memory test ----------\n");
	printk("%c   -    %c\n", p[0], p[4096-1]);
	free_pages((unsigned long)p, 0);

	return 0;
}

void my_exit(void)
{
	printk("------------ buddy test exit ----------\n");
}

module_init (my_init);
module_exit(my_exit);
