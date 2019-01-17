#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>


#define LICENSE		"GPL"
#define DESCRIPTION	"PARAMETER CHANGE DEMO"
#define AUTHOR		"SPANIDEA"
#define VERSION		"v0.8"



int param1,param2[4];
char *paramstr;
int cb_valueETX = 0;

module_param(param1, int, S_IRUSR | S_IWUSR);
module_param_array(param2, int, NULL, S_IRUSR | S_IWUSR);
module_param(paramstr, charp, S_IRUSR | S_IWUSR);

/****************************
 * setting call back function
 * *****************************/

int notify_param(const char *val, const struct kernel_param *kp)
{
	int res = param_set_int(val,kp);
	if(res == 0)
	{
		printk(KERN_INFO "your callback function called.");
		printk(KERN_INFO "value change to cb_valueETX : %d",cb_valueETX);
		return 0;
	}
	return -1;
}

const struct kernel_param_ops my_param_ops=
{
	.set = &notify_param,
	.get = &param_get_int,	
};

module_param_cb( cb_valueETX, &my_param_ops, &cb_valueETX, S_IRUGO | S_IWUSR);


static int param_change_init(void)
{
	printk(KERN_ALERT, "param change module load." );
	printk(KERN_ALERT "param1 : %d,\t\nparam2 : %d,\t%d,\t%d,\t%d\nparamstr : %s\n",param1,param2[0],param2[1],param2[2],param2[3],paramstr);
	printk(KERN_ALERT, "param change module load successfully" );
	return 0;
}

static void param_change_exit(void)
{
	printk(KERN_ALERT, "param change module unload successfully." );
}

module_init(param_change_init);
module_exit(param_change_exit);

MODULE_DESCRIPTION(DESCRIPTION);
MODULE_AUTHOR(AUTHOR);
MODULE_LICENSE(LICENSE);
MODULE_VERSION(VERSION);



