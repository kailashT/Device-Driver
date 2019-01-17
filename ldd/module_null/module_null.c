#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>


static dev_t first; //major no minor no sane in dev_t
static struct cdev c_dev;//device structure for character device
static struct class *cl; //structure class

static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver :open()\n");
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver : close()\n");
	return 0;
}

static ssize_t my_read(struct file *f, char __user *buf,size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver : read()\n");
	return 0;
}


static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Drivr: write()\n");
	return len;
}

static struct file_operations pugs_fops=
{
	.owner = THIS_MODULE,
	.open =my_open,
	.release =my_close,
	.read =my_read,
	.write =my_write,
};

static int __init ofcd_init(void)
{
	printk(KERN_INFO "Namskar : ofd reg"); //entry for init
	if(alloc_chrdev_region(&first, 0, 3, "SPANIDEA") < 0) // register device for major no and minor no
	{
		return -1;
	}
	if((cl = class_create(THIS_MODULE, "chardrv")) == NULL) // create class for device
	{
		unregister_chrdev_region(first,1);
		return -1;
	}
	if(device_create(cl,NULL,first,NULL,"mynull") == NULL) //device crate
	{
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	cdev_init(&c_dev, &pugs_fops); // device init 
	if(cdev_add(&c_dev, first,1) == -1) // add device in the catagory of character device
	{
		device_destroy(cl,first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	return 0;
}

static void __exit ofcd_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cl,first);
	class_destroy(cl);
	unregister_chrdev_region(first,1);
	printk(KERN_INFO "Unloaded Successfully");

}

module_init(ofcd_init);
module_exit(ofcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MJ");
MODULE_DESCRIPTION("OUR FIRST CHARACTER DRIVER : automatic");




