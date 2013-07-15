#include "../../include/drivers/lspci.h"

PCI_TABLE pciTable[] = {
    /*Fuente: http://pci-ids.ucw.cz/v2.2/pci.ids */
    /* Para Dell Inspiron 15R */
	{0x8086, 0x0154, "Intel Corporation", "3rd Gen Core processor DRAM Controller"},
    {0x8086, 0x0156, "Intel Corporation", "3rd Gen Core processor Graphics Controller"},
    {0x8086, 0x1e31, "Intel Corporation", "7 Series/C210 Series Chipset Family USB xHCI Host Controller"},
    {0x8086, 0x1e3a, "Intel Corporation", "7 Series/C210 Series Chipset Family MEI Controller #1"},
    {0x8086, 0x1e2d, "Intel Corporation", "7 Series/C210 Series Chipset Family USB Enhanced Host Controller #2"},
    {0x8086, 0x1e20, "Intel Corporation", "7 Series/C210 Series Chipset Family High Definition Audio Controller"},
    {0x8086, 0x1e10, "Intel Corporation", "7 Series/C210 Series Chipset Family PCI Express Root Port 1"},
    {0x8086, 0x1e12, "Intel Corporation", "7 Series/C210 Series Chipset Family PCI Express Root Port 2"},
    {0x8086, 0x1e26, "Intel Corporation", "7 Series/C210 Series Chipset Family USB Enhanced Host Controller #1"},
    {0x8086, 0x1e57, "Intel Corporation", "HM77 Express Chipset LPC Controller"},
    {0x8086, 0x1e03, "Intel Corporation", "7 Series Chipset Family 6-port SATA Controller [AHCI mode]"},
    {0x8086, 0x1e22, "Intel Corporation", "7 Series/C210 Series Chipset Family SMBus Controller"},
    {0x10ec, 0x8136, "Realtek Semiconductor Co., Ltd.", "RTL8101E/RTL8102E PCI Express Fast Ethernet controller"},
    /* Para VirtualBox */
    {0x8086, 0x1237, "Intel Corporation", "440FX - 82441FX PMC [Natoma]"},
    {0x8086, 0x7000, "Intel Corporation", "82371SB PIIX3 ISA [Natoma/Triton II]"},
    {0x8086, 0x7111, "Intel Corporation", "82371AB/EB/MB PIIX4 IDE"},
    {0x80ee, 0xbeef, "InnoTek Systemberatung GmbH", "VirtualBox Graphics Adapter"},
    {0x80ee, 0xcafe, "InnoTek Systemberatung GmbH", "VirtualBox Guest Service"},
    {0x8086, 0x100e, "Intel Corporation", "82540EM Gigabit Ethernet Controller"},
    {0x8086, 0x2415, "Intel Corporation", "82801AA AC'97 Audio Controller"},
    {0x106b, 0x003f, "Apple Inc.", "KeyLargo/Intrepid USB"},    
    {0x8086, 0x7113, "Intel Corporation", "82371AB/EB/MB PIIX4 ACPI"},  
    {0x8086, 0x2829, "Intel Corporation", "82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode]"}      
};
    
int dimPciTable = sizeof(pciTable)/sizeof(PCI_TABLE);

void printPci(unsigned short vendorId, unsigned short deviceId) {
    int i;
    if ( vendorId == 0xFFFF )
        return ;
    for ( i = 0; i < dimPciTable; i++ ) {
        if (pciTable[i].vendorId == vendorId && pciTable[i].deviceId == deviceId) {
            printf("%s - %s\n", pciTable[i].vendor, pciTable[i].device);
            return ;
        }
    }
}
        
void lspci(void) {
    unsigned short vendorId, deviceId;
    int bus, device, reg = 0, mask, data, fun = 0, prints = 0;
	mask = 0xFFFF;
	for ( bus = 0; bus < 256; bus++ ) 
		for ( device = 0; device < 32; device++ ) {
            mask = BIT31 | BITS30A24 | ((bus << 16) & BITS23A16) |
                   ((device << 11) & BITS15A11) | 
                   (fun & BITS10A8) | (reg & BITS7A0);
            outportb32(CONFIG_ADDRESS, mask);
            data = inportb32(CONFIG_DATA);
            if ( data != 0xFFFFFFFF && data != 0x00000000 ) {
                vendorId = data & 0x0000FFFF;
                deviceId = (data & 0xFFFF0000) >> 16;
                printPci(vendorId,deviceId);
                prints++;
                if(prints % 10 == 0) {
                    printf("Presione enter para continuar.\n");
                    while(getchar()!= '\n');
                }
            }
        }
}
