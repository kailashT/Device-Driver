#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

dev_t dev = MKDEV(235, 0);

static int major_init(void)
{
	printk(KERN_ALERT "Major no Driver loaded successfully");
	register_chrdev_region(dev, 1, "spanidea_dev");
	printk(KERN_ALERT "Major : %d\tMinor : %d",MAJOR(dev),MINOR(dev));
	printk(KERN_ALERT "Your Module inserted successfully");
	return 0;
}

static void major_exit(void)
{
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Goodbye Major no.");
	printk(KERN_INFO "Goodbye Major no.");
}

module_init(major_init);
module_exit(major_exit);

MODULE_LICENSE("GPL");
