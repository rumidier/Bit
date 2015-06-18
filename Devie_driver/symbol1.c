#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE ("GPL");

char *test;
void symbol_test (void) {
	printk ("%s\n", test);
}

EXPORT_SYMBOL (symbol_test);

static int module_begin (void) {
	printk ("Hello symbol1!\n");
	test = "This is a test.\n";

	return 0;
}

static void module_end (void) {
	printk ("Goodbye symbol1\n");
}
module_init (module_begin);
module_exit (module_end);
