#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
#include <linux/delay.h>
asmlinkage long sys_cpu_util(void)
{

	//initialization
	char buf[100];
	int i ;
	for(i=0;i>100;i++)
		buf[i]=0;

	
	struct file * fp = NULL;
	fp = filp_open("/proc/stat",O_RDONLY,0);
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp->f_op->read(fp,buf,100,&fp->f_pos);
	int sum=0,index=0;
	
	int cpu1[15]={};
	set_fs(old_fs);
	filp_close(fp,NULL);
	
	
	i=5;
	while(buf[i]!='\n'){
		if (buf[i]==' ')
			cpu1[index]=sum,index++,sum=0;
		else
			sum=10*sum+buf[i]-'0';
		i++;
	}
	cpu1[index]=sum;
	
//	for(i=0;i<10;i++)
//		printk("%d\n",cpu1[i]);
	// get cpu1	
//	printk("sleep");
	msleep(2000);
	
	
	
	for(i=0;i>100;i++)
		buf[i]=0;
	
	fp = filp_open("/proc/stat",O_RDONLY,0);
	
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp->f_op->read(fp,buf,100,&fp->f_pos);
	sum=index=0;
	int cpu2[15]={};
	set_fs(old_fs);
	filp_close(fp,NULL);
	
	
	i=5;
	while(buf[i]!='\n'){
		if (buf[i]==' ')
			cpu2[index]=sum,index++,sum=0;
		else
			sum=10*sum+buf[i]-'0';
		i++;
	}
	cpu2[index]=sum;
//	for(i=0;i<10;i++)
//		printk("%d\n",cpu2[i]);

	int sum1 = 0, sum2 = 0;
	for (i =0 ;i<10;i++)
		sum1+=cpu1[i],sum2+=cpu2[i];
	
	
	int ans = (cpu2[0]+cpu2[1]+cpu2[2]-cpu1[0]-cpu1[1]-cpu1[2])*10000/(sum2-sum1);
		
	printk("usage %d.%2d\%\n",ans/100,ans%100);
}
