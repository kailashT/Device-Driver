#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

#define LICENSE		"GPL"
#define DESCRIPTION	"Process Info Module"
#define AUTHOR		"SPANIDEA"
#define	VERSION		"V0.1"




static int process_init(void)
{
	struct task_struct *task;
	for_each_process(task)
	{
		printk("Process Name : %s\tPID : %d\tStatus : %ld\n", task->comm, task->pid, task->state);
	}
	return 0;
}


static void process_exit(void)
{
	printk(KERN_INFO "exiting process module.");
}

module_init(process_init);
module_exit(process_exit);

MODULE_LICENSE(LICENSE);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_AUTHOR(AUTHOR);
MODULE_VERSION(VERSION);
