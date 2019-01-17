#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>


#define LICENSE  	"GPL"
#define AUTHOR   	"SPANIDEA"
#define DESCREPTION 	"Tesing for parameter passing"
#define VERSION 	"V2.0"

int paramTest;
module_param(paramTest, int, S_IRUSR | S_IWUSR);

static int param_init(void)
{
	printk(KERN_ALERT "Showing the parameter demo");
	printk(KERN_ALERT "Value of paramTest = %d",paramTest);
	return 0;
}

static void param_exit(void)
{
	printk(KERN_ALERT "Exiting the parameter demo. ");

}

module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCREPTION);
MODULE_VERSION(VERSION);


