#ifndef _pci_database_h
#define _pci_database_h

/* FUENTE: http://www.pcidatabase.com/pci_c_header.php */

#if 0

PCIHDR.H: PCI Vendors, Devices, and Class Type information

Created automatically from the web using the following URL:
http://pcidatabase.com/
Software to create and maintain the PCICODE List written by:
Jim Boemler (jboemler@halcyon.com)

This header created on Wed May 29 09:39:22 PDT 2013

Too many people have contributed to this list to acknowledge them all, but
a few have provided the majority of the input and deserve special mention:
Frederic Potter, who maintains a list for Linux.
Chris Aston at Madge Networks.
Thomas Dippon of Hewlett-Packard GmbH.
Jurgen ("Josh") Thelen
William H. Avery III at Altitech
Sergei Shtylyov of Brain-dead Software in Russia

#endif

//  NOTE that the 0xFFFF of 0xFF entries at the end of some tables below are
//  not properly list terminators, but are actually the printable definitions
//  of values that are legitimately found on the PCI bus.  The size
//  definitions should be used for loop control when the table is searched.

typedef struct _PCI_VENTABLE {
	unsigned short VenId ;
	char * VenShort ;
	char * VenFull ;
} PCI_VENTABLE, *PPCI_VENTABLE ;

// Use this value for loop control during searching:
#define	PCI_VENTABLE_LEN	(sizeof(PciVenTable)/sizeof(PCI_VENTABLE))

typedef struct _PCI_DEVTABLE {
	unsigned short	VenId ;
	unsigned short	DevId ;
	char *	Chip ;
	char *	ChipDesc ;
} PCI_DEVTABLE, *PPCI_DEVTABLE ;

// Use this value for loop control during searching:
#define	PCI_DEVTABLE_LEN	(sizeof(PciDevTable)/sizeof(PCI_DEVTABLE))

typedef struct _PCI_CLASSCODETABLE {
	unsigned char	BaseClass ;
	unsigned char	SubClass ;
	unsigned char	ProgIf ;
	char *		BaseDesc ;
	char *		SubDesc ;
	char *		ProgDesc ;
}  PCI_CLASSCODETABLE, *PPCI_CLASSCODETABLE ;

// Use this value for loop control during searching:
#define	PCI_CLASSCODETABLE_LEN	(sizeof(PciClassCodeTable)/sizeof(PCI_CLASSCODETABLE))

// Use this value for loop control during searching:
#define	PCI_COMMANDFLAGS_LEN	(sizeof(PciCommandFlags)/sizeof(char *))

// Use this value for loop control during searching:
#define	PCI_STATUSFLAGS_LEN	(sizeof(PciStatusFlags)/sizeof(char *))

// Use this value for loop control during searching:
#define	PCI_DEVSELFLAGS_LEN	(sizeof(PciDevSelFlags)/sizeof(char *))

#endif