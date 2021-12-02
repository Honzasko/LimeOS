typedef struct PCI_Device 
{
    uint32_t bus;
    uint32_t device;
}PCI_Device_t;

typedef struct PCI_DeviceInfo
{
    uint16_t vendor;
    uint16_t device;
    uint16_t class_code;
    uint16_t subclass;
    
}PCI_DeviceInfo_t;

PCI_Device_t pci_devices[25];
uint8_t num_devices;

void PCI_InitDevices();

PCI_DeviceInfo_t PCI_GetDeviceInfo(uint32_t bus,uint32_t dev);
