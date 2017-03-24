#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_hello(void)
{
	printk("HELLO SYSTEM CALL \n");
	return 0;
}
