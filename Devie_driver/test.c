#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE ("GPL");

extern int module_begin (void);

module_init (module_begin);
