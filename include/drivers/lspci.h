#ifndef _lspci_h
#define _lspci_h

#include "../lib/stdio.h"
#include "../kasm.h"

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

#define BIT31 0x80000000 
/* Siempre en 1 */

#define BITS30A24 0x7F000000
/* Siempre en 0 */

#define BITS23A16 0x00FF0000
/* Bus Number */

#define BITS15A11 0x0000F800
/* Device Number */

#define BITS10A8 0x00000700
/* Function Number */

#define BITS7A0 0x000000FF
/* Register Number */

/* Imprime en salida estándar el detalle de un PCI Device */
void printPci(unsigned short vendorId, unsigned short deviceId);

/* lspci */
void lspci(void);

typedef struct {
	unsigned short	vendorId ;
	unsigned short	deviceId ;
	char * vendor;
	char * device;
} PCI_TABLE;

#endif
