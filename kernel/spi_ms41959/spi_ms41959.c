// Starter for ten to get basic framework for building a kernel module in visual studio code on LInux.

// To start with lets just create a framework that writes a hellow world message out to the log file when the module is loaded / unloaded

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Gambell");
MODULE_DESCRIPTION("SPI Driver for MS41959 motor controller spi module");
MODULE_VERSION("1.0");

static int __init spi_ms41959_init(void){
    printk(KERN_INFO "SPI kernel module loaded ok\n");
}

static void __exit spi_ms41959_exit(void){
    printk(KERN_INFO, "Module unloaded ok\n");
}

module_init(spi_ms41959_init);
module_exit(spi_ms41959_exit);
