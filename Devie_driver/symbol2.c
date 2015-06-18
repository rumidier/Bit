#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE ("GPL");
extern void symbol_test(void);

static int module_begin (void) {
	printk ("Hello symbol2!!\n");
	symbol_test();

	return 0;
}

static void module_end (void) {
	printk ("Goodbye symbol2\n");
}

module_init (module_begin);
module_exit (module_end);
