#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>


dev_t dev = 0 ;
static struct class *dev_class;
static struct cdev etx_cdev;

static int __init dummy_init(void);
static void __exit dummy_exit(void);
static int dummy_open(struct inode *inode, struct file *file);
static int dummy_close(struct inode *inode, struct file *file);
static ssize_t dummy_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t dummy_write(struct file *filp, const char *buf, size_t len, loff_t *off);

static struct file_operations fops =
{
	.owner	=	THIS_MODULE,
	.read 	=	dummy_read,
	.write	=	dummy_write,
	.open	=	dummy_open,
	.release=	dummy_close,
};


static int __init dummy_init(void)
{
	printk(KERN_INFO "Driver init\n");
	//register major minor
	if(alloc_chrdev_region(&dev, 0, 1, "dummy") < 0 )
	{
		printk(KERN_INFO "cannot allocate major no");
		return -1;
	}
	
	printk(KERN_INFO "MAJOR : %d\tMINOR : %d",MAJOR(dev),MINOR(dev));

	cdev_init(&etx_cdev, &fops);

	if((cdev_add(&etx_cdev, dev,1)) < 0)
	{
		printk(KERN_INFO "cannot add device to system");
		goto r_class;
	}

	if((dev_class = class_create(THIS_MODULE, "dummy_class")) == NULL)
	{
		printk(KERN_INFO "cannot create class");
		goto r_class;
	}

	if((device_create(dev_class,NULL,dev,NULL,"dummy")) == NULL)
	{
		printk(KERN_INFO "device create failed\n");
		goto r_device;
	}
	printk(KERN_INFO "device driver insert...done\n");
	return 0;
r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev,1);
	return -1;
	//device class
	//device create
}

static void __exit dummy_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&etx_cdev);
	unregister_chrdev_region(dev,1);

	printk(KERN_INFO "Device driver removed successfully");
}

static int dummy_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Driver open function called\n");
	return 0;
}

static int dummy_close(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Driver close function called\n");
	return 0;
}
static ssize_t dummy_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver read called");
	return 0;
}

static ssize_t dummy_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver write called");
	return len;
}


module_init(dummy_init);
module_exit(dummy_exit);

MODULE_LICENSE("GPL");
