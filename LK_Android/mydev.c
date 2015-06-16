#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL")

static struct file_operations fops;

int my_init(void)
{
  register_chrdev(200, "mydev", &fops);
}

void my_exit(void)
{
  unregister_chrdev(200, "mydev");
}

module_init (my_init);
module_exit (my_exit);
