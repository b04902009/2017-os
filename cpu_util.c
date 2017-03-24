#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
asmlinkage long sys_cpu_util(void)
{
	//initialization
	char buf[100];
	int i ;
	for(i=0;i>100;i++)
		buf[i]=0;

	
	struct file * fp = NULL;
	fp = filp_open("/proc/stat",O_RDONLY,0);
	if(fp==NULL){
		printk(KERN_ALERT"file_open error!!.\n");
	}
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp->f_op->read(fp,buf,10,&fp->f_pos);
	set_fs(old_fs);
	filp_close(fp,NULL)
	printk("buf:%s\n",buf);
}
