#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

struct pci_dev_info {
    unsigned int devfn;
    unsigned short vendor;
    unsigned short device;
    unsigned short subsystem_vendor;
    unsigned short subsystem_device;
    unsigned int class;
    unsigned char revision;
    unsigned char hdr_type;
};

void print_pci_dev_info_to_kernel(struct pci_dev_info *pci_dev_info) {
    printk("struct pci_dev_info {\n");
    printk("  devfn: %d\n", pci_dev_info->devfn);
    printk("  vendor: %d\n", pci_dev_info->vendor);
    printk("  device: %d\n", pci_dev_info->device);
    printk("  subsystem_vendor: %d\n", pci_dev_info->subsystem_vendor);
    printk("  subsystem_device: %d\n", pci_dev_info->subsystem_device);
    printk("  class: %d\n", pci_dev_info->class);
    printk("  revision: %d\n", pci_dev_info->revision);
    printk("  hdr_type: %d\n", pci_dev_info->hdr_type);
    printk("}\n");
}

struct pci_dev_info pci_dev_to_dev_info(struct pci_dev *pci_dev) {
    struct pci_dev_info pci_dev_info;
    pci_dev_info.devfn = pci_dev->devfn;
    pci_dev_info.vendor = pci_dev->vendor;
    pci_dev_info.device = pci_dev->device;
    pci_dev_info.subsystem_vendor = pci_dev->subsystem_vendor;
    pci_dev_info.subsystem_device = pci_dev->subsystem_device;
    pci_dev_info.class = pci_dev->class;
    pci_dev_info.revision = pci_dev->revision;
    pci_dev_info.revision = pci_dev->revision;
    
    return pci_dev_info;
}

SYSCALL_DEFINE3(pci_dev, struct pci_dev_info*, user_pci_device_info, unsigned int, vendor, unsigned int, device) {
    struct pci_dev *pci_dev = NULL;
    struct pci_dev_info pci_dev_info;
    printk("---- SYS_PCI_DEV ----\n");
    
    pci_dev = pci_get_device(vendor, device, pci_dev);
    pci_dev_info = pci_dev_to_dev_info(pci_dev);
    
    print_pci_dev_info_to_kernel(&pci_dev_info);

    return copy_to_user(user_pci_device_info, &pci_dev_info,
				sizeof(struct pci_dev_info));
}
