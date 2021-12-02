#include <stdint.h>
#include "../includes/pci.h"
#include "../includes/io.h"

void PCI_InitDevices()
{
    num_devices = 0;
    for(uint8_t b = 0;b < 10;b++)
    {
        for (uint8_t d = 0; d < 10;d++)
        {
            uint32_t address = 0;
            uint32_t device = d;
            uint32_t configured = 1 << 31;
            device <<= 11;
            uint32_t bus = b;
            bus <<= 16;
            address = bus | device | configured;
            outl(0xCF8,address);
            uint32_t ouput = inl(0xCFC);
            if(ouput != 0)
            {
                pci_devices[num_devices].bus = b;
                pci_devices[num_devices].device = d;
                num_devices++;
                if(num_devices == 7)
                {
                    d = 32;
                    b = 255;
                }
            }
        }
        
    }
}


PCI_DeviceInfo_t PCI_GetDeviceInfo(uint32_t bus,uint32_t dev)
{
    PCI_DeviceInfo_t t;
    dev <<= 11;
    bus <<= 16;
    uint32_t configured = 1 << 31;
    uint32_t address = dev | bus | configured;
    outl(0xCF8,address);
    uint32_t output = (uint16_t)((inl(0xCFC) >> ((1 & 2) * 8)) & 0xFFFF);
    output |= (uint16_t)((inl(0xCFC) >> ((2 & 2) * 8)) & 0xFFFF);
    uint32_t vendor = output & 0xFFFF0000;
    uint32_t device = output & 0x0000FFFF;
    t.device = (uint16_t)device;
    t.vendor = (uint16_t)vendor;
    address |= 0x2;
    outl(0xCF8,address);
    output = 0;
    output = inl(0xCFC);
    t.class_code = output & 0x000000FF;
    t.subclass = output & 0x000eFe00;
    return t;
}