#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_show(void)
{
	printk("B04611015 Chen Chia-You\n");
	printk("B04902009 Hsiao Chien-Huei\n");
	return 0;
}
