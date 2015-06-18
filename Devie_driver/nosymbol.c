#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static void nosymbol_test (void) {
    printk("nosymbols test");
}

static int module_begin (void) {
	printk ("Hello nosymbol!\n");
	return 0;
}

static void module_end (void) {
	printk ("Goodbye nosymbol\n");
}

module_init (module_begin);
module_exit (module_end);
