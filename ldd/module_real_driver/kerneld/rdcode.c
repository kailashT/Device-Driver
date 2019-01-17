#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
//#include <linux/kdev_t>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define mem_size 1024

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
uint8_t *kernel_buffer;

static int __init rdcode_init(void);
static void __exit rdcode_exit(void);
static int rdcode_open(struct inode *inode, struct file *file);
static int rdcode_release(struct inode *inode, struct file *file);
static ssize_t rdcode_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t rdcode_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
        .owner          =THIS_MODULE,
        .read           =rdcode_read,
        .write          =rdcode_write,
        .open           =rdcode_open,
        .release        =rdcode_release,
};

static int rdcode_open(struct inode *inode, struct file *file)
{
        if((kernel_buffer = kmalloc(mem_size, GFP_KERNEL)) == 0)
        {
                printk(KERN_INFO "cannot allocate memory in kernel\n");
                return -1;
        }
        printk(KERN_INFO "Device File Opened\n");
        return 0;
}
static int rdcode_release(struct inode *inode, struct file *file)
{
        kfree(kernel_buffer);
        printk(KERN_INFO "Device file closed.\n");
        return 0;
}

static ssize_t rdcode_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        copy_to_user(buf, kernel_buffer, mem_size);
        printk(KERN_INFO "Data read : Done\n");
        return mem_size;
}

static ssize_t rdcode_write(struct file *filp, const char *buf, size_t len, loff_t * off)
{
        copy_from_user(kernel_buffer, buf, len);
        printk(KERN_INFO "Data Write : Done \n");
        return len;
}

static int __init rdcode_init(void)
{
        printk(KERN_INFO "Device Driver loading...");
        if((alloc_chrdev_region(&dev, 0, 1, "my_device")) < 0)
        {
                printk(KERN_INFO "Cannot allocate major number\n");
                return -1;
        }
        printk(KERN_INFO "Major no : %d\tMinor no : %d",MAJOR(dev),MINOR(dev));

        cdev_init(&etx_cdev, &fops);

        if((cdev_add(&etx_cdev, dev, 1)) < 0)
        {
                printk(KERN_INFO "Cannot add device to the system\n");
                goto r_class;
        }
        if((dev_class = class_create(THIS_MODULE,"etx_class")) == NULL)
        {
                printk(KERN_INFO "can not crate the struct class\n");
                goto r_class;
        }

        if((device_create(dev_class, NULL, dev, NULL,"my_device")) == NULL)
        {
                printk(KERN_INFO "Can not create the device.\n");
                goto r_device;
        }
        printk(KERN_INFO "Device Driver insert done..\n");
        return 0;
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev, 1);
        return -1;
}

static void __exit rdcode_exit(void)
{
        device_destroy(dev_class, dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev,1);
        printk(KERN_INFO "Device Driver remove done.\n");
}



module_init(rdcode_init);
module_exit(rdcode_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SPANIDEA");
MODULE_DESCRIPTION("A Simple read write Device Driver.\n");
MODULE_VERSION("1.0");

