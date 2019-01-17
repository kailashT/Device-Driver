#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/fs.h>

dev_t first = 0 ;
static struct class *dev_class;

static int __init ddf_init(void)
{
	printk(KERN_INFO "Loading Driver");
	if(alloc_chrdev_region(&first, 0, 1, "ddl") < 0)
	{
		printk(KERN_INFO "can not allocate major no for device\n");
		return -1;
	}
	printk(KERN_INFO "MAJOR : %d\t Minor : %d \n",MAJOR(first),MINOR(first));
	if((dev_class = class_create(THIS_MODULE,"ddl")) ==NULL  )
	{
		printk(KERN_INFO "class create failed \n");
		goto r_class;
	}
	if((device_create(dev_class,NULL,first,NULL,"ddl"))==NULL)
	{
		printk(KERN_INFO "device create failed. \n");
		goto r_device;
	}
	printk(KERN_INFO "kernel module inserdted succussfully\n");

	return 0;
r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(first,1);
	return -1;
}

static void __exit ddf_exit(void)
{
	device_destroy(dev_class,first);
	class_destroy(dev_class);
	unregister_chrdev_region(first,1);
	printk(KERN_INFO "unloading successfull");
}


module_init(ddf_init);
module_exit(ddf_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Devic edriver file creation");
MODULE_AUTHOR("MAHESH");
MODULE_VERSION("V15");
