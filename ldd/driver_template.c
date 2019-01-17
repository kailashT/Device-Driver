#include <linux/init.h>
#include <linux/module.h>

#define LICENSE		"GPL"
#define AUTHOR		"SPANIDEA"
#define DESCRIPTION	"AS you wish"
#define	VERSION		"V"

static int __init entry_func_name(void)
{
	printk(KERN_INFO "Module inserted successfully.");
	return 0;
}

static void __exit exit_func_name(void)
{
	printk(KERN_INFO "module removed successfully.");
}


module_init();
module_exit();

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_VERSION(VERSION);
