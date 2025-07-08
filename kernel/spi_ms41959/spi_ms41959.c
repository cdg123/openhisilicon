// Starter for ten to get basic framework for building a kernel module in visual studio code on LInux.

// To start with lets just create a framework that writes a hellow world message out to the log file when the module is loaded / unloaded

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Gambell");
MODULE_DESCRIPTION("SPI Driver for MS41959 motor controller with Goke GK7205v300");
MODULE_VERSION("0.1");

struct spi_master *master;
struct spi_device *spi_dev;
#DEFINE SPI_NAME "SPI1@120710000   "

static char spi_name[128] = SPI_NAME; // Name of the SPI device as defined in the device tree
static struct device *dev; // Pointer to the SPI device

static struct spi_board_info my_spi_device = {
    .modalias = "SPI1",
    .max_speed_hz = 10000000; // 10 MHz
    .bus_num = 1, // SPI bus number
    .chip_select = 0, // Chip select line;
    .mode = SPI_MODE_3, // SPI mode;
    .bits_per_word = 8, // 8 bits per word
};


static int __init spi_ms41959_init(void){
    printk(KERN_INFO "SPI kernel module loaded ok\n");
    printk(KERN_IFO "Attempting to register spi controller on bus")

    // Get a pointer to the SPI master bus
    master = spi_busnum_to_master(my_spi_device.bus_num);
    if (!master) {
        printk(KERN_ERR "Failed to get SPI master for bus %d\n", my_spi_device.bus_num);
        return -ENODEV; // Return error if master not found
    }
    printk(KERN_INFO "SPI master found for bus %d\n", my_spi_device.bus_num);

    //Find the SPI device by name as defined in the device tree
    dev = bus_find_device_by_name(&spi_bus_type, NULL, spi_name);



    // do loading stuf here to register the spi device, etc.
    return 0; // Return 0 on success
}





static void __exit spi_ms41959_exit(void){
    printk(KERN_INFO, "Module unloaded ok\n");

}

module_init(spi_ms41959_init);
module_exit(spi_ms41959_exit);
