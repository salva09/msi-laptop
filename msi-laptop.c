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

static int __init msi_laptop_init(void) {
	printk(KERN_INFO "Loading module\n");

	/*
	 * I'm going to use this guid because is the only
	 * one I have to check if this an msi laptop
	 */
	if (wmi_has_guid(MSIWMI_WIND_EVENT_GUID)) {
		printk(KERN_INFO "Has MSIWMI_WIND_EVENT_GUID!\n");
	}

	return 0;
}

static void __exit msi_laptop_exit(void) {
	printk(KERN_INFO "Unloading module\n");
}

module_init(msi_laptop_init);
module_exit(msi_laptop_exit);
