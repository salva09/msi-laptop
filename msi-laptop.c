#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/acpi.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Salvador Hernández");
MODULE_DESCRIPTION("MSI driver for laptops.");
MODULE_VERSION("0.01");

// All guids used from msi-wmi.c
#define MSIWMI_BIOS_GUID "551A1F84-FBDD-4125-91DB-3EA8F44F1D45"
#define MSIWMI_MSI_EVENT_GUID "B6F3EEF2-3D2F-49DC-9DE3-85BCE18C62F2"
#define MSIWMI_WIND_EVENT_GUID "5B3CC38A-40D9-7245-8AE6-1145B751BE3F"

#define MSI_EC_THRESHOLD_ADDRESS 0xef

static int charge_threshold_get(void);
static int charge_threshold_set(int end);
static void charge_threshold_show(void);

static int charge_threshold_get(void)
{
	int err;
	u8 val;

	err = ec_read(MSI_EC_THRESHOLD_ADDRESS, &val);

	if (!err)
		return (int) val;

	return err;
}

/*
 * Accepeted values are
 * 0 - 60%
 * ? - 80%
 * 1 - 100%
 */
static int charge_threshold_set(int end)
{
	int err;
	u8 val;

	if (end < 0 || end > 2)
		return -EINVAL;

	val = (u8) (end);
	err = ec_write(MSI_EC_THRESHOLD_ADDRESS, val);

	return err;
}

static void charge_threshold_show(void)
{
	int val;

	val = charge_threshold_get();

	printk(KERN_INFO "Charge threshold value: %d\n", val);
}

static int __init msi_laptop_init(void)
{
	printk(KERN_INFO "Loading module\n");

	/*
	 * I'm going to use this guid because is the only
	 * one I have to check if this is an msi laptop
	 *
	 * It needs a better suitable guid, because this
	 * probably will only work with 11th gen intel laptops
	 */
	if (wmi_has_guid(MSIWMI_WIND_EVENT_GUID)) {
		charge_threshold_show();

		//int err = charge_threshold_set(1);
		//printk(KERN_INFO "Write ec, Error: %d\n", err);
	}

	return 0;
}

static void __exit msi_laptop_exit(void)
{
	printk(KERN_INFO "Unloading module\n");
}

module_init(msi_laptop_init);
module_exit(msi_laptop_exit);
