#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/acpi.h>
#include <linux/wmi.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Salvador Hernández");
MODULE_DESCRIPTION("MSI driver for laptops.");
MODULE_VERSION("0.01");

// All guids used from msi-wmi.c
#define MSIWMI_BIOS_GUID "551A1F84-FBDD-4125-91DB-3EA8F44F1D45"
#define MSIWMI_MSI_EVENT_GUID "B6F3EEF2-3D2F-49DC-9DE3-85BCE18C62F2"
#define MSIWMI_WIND_EVENT_GUID "5B3CC38A-40D9-7245-8AE6-1145B751BE3F"

#define MSI_WMI_BATTERY_GUID "ABBC0F6E-8EA1-11D1-00A0-C90629100000"

#define MSI_EC_THRESHOLD_ADDRESS 0xef

static int charge_threshold_get(void);
static int charge_threshold_set(int end);
static void charge_threshold_show(void);

static void test_wmi_method(void)
{
  struct acpi_buffer input, output;
  acpi_status status;
  u8 instance = 0;
  u32 method_id = 1;
  
  status = wmi_evaluate_method(MSI_WMI_BATTERY_GUID, instance, method_id, &input, &output);
}

static int __init msi_laptop_init(void)
{
	printk(KERN_INFO "Loading module\n");

	if (wmi_has_guid(MSI_WMI_BATTERY_GUID)) {
		test_wmi_method();
	}

	return 0;
}

static void __exit msi_laptop_exit(void)
{
	printk(KERN_INFO "Unloading module\n");
}

module_init(msi_laptop_init);
module_exit(msi_laptop_exit);
