#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>


#define LICENSE		"GPL"
#define AUTHOR		"SPANIDEA"
#define DESCRIPTION	"AS you wish"
#define	VERSION		"V1"


dev_t dev = 0;

static int __init major_init(void)
{
	if((alloc_chrdev_region(&dev, 0, 1, "span_dynamic")) < 0)
	{
		printk(KERN_ALERT "cannot assign major no for device");
		printk(KERN_ALERT "cannot assign major no for device");
		return -1;
	}
	printk(KERN_INFO "major : %d\tMinor : %d",MAJOR(dev),MINOR(dev));
	printk(KERN_INFO "Module inserted successfully.");
	return 0;
}

static void __exit major_exit(void)
{
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "module removed successfully.");
}


module_init(major_init);
module_exit(major_exit);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_VERSION(VERSION);
