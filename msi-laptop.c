#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Salvador Hernández");
MODULE_DESCRIPTION("MSI driver for laptops.");
MODULE_VERSION("0.01");

static int __init msi_laptop_init(void) {
  printk(KERN_INFO "Hello, World!\n");
  return 0;
}

static void __exit msi_laptop_exit(void) {
  printk(KERN_INFO "Goodbye, World!\n");
}

module_init(msi_laptop_init);
module_exit(msi_laptop_exit);
