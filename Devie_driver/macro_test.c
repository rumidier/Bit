#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Device Driver");
MODULE_DESCRIPTION("Parameter Test Module");

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "mykernel";
static int arr_argc = 0;

module_param (myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC (myshort, "A short interger");

module_param (myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC (myint, "An interger");

module_param (mylong, long, S_IRUSR);
MODULE_PARM_DESC (mylong, "A long interger");

module_param(mystring, charp, 0000);
MODULE_PARM_DESC (mystring, "A character string");

static int __init hello_param_init (void)
{
	int i;
	printk ("Hello, world \n");
	printk ("myshort short interger: %hd\n", myshort);
	printk ("myint is an interger: %d\n", myint);
	printk ("mylong is a long interger: %ld\n", mylong);
	printk ("mystring is a string: %s\n", mystring);

	return 0;
}

static void __exit hello_param_exit (void)
{
	printk ("Goodbye, world \n");
}

module_init(hello_param_init);
module_exit(hello_param_exit);
