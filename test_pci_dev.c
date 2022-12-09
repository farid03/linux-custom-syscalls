#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void print_pci_dev_info(struct pci_dev_info *pci_dev_info) {
    printf("struct pci_dev_info {\n");
    printf("  devfn: %d\n", pci_dev_info->devfn);
    printf("  vendor: %d\n", pci_dev_info->vendor);
    printf("  device: %d\n", pci_dev_info->device);
    printf("  subsystem_vendor: %d\n", pci_dev_info->subsystem_vendor);
    printf("  subsystem_device: %d\n", pci_dev_info->subsystem_device);
    printf("  class: %d\n", pci_dev_info->class);
    printf("  revision: %d\n", pci_dev_info->revision);
    printf("  hdr_type: %d\n", pci_dev_info->hdr_type);
    printf("}\n");
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Invalid command line argeuments!\n");
    }
    
    printf("---- pci_dev syscall testing ----\n");
    struct pci_dev_info dev = { 0 };
    long int ret_code = syscall(549, &dev, atoi(argv[1]), atoi(argv[2]));
    
    printf("syscall ret code: %li\n", ret_code);
    print_pci_dev_info(&dev);
    
    return 0;
}

