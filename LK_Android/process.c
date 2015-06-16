#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

int my_init(void)
{
	struct task_struct *p;
	p = current;
	printk("------------ process -----------\n");
	printk("pid = %d, comm=%s\n", p->pid, p->comm);

	return 0;
}

void my_exit(void)
{
	printk("---------- process end ------------\n");
}

module_init (my_init);
module_exit (my_exit);
