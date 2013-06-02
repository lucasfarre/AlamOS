/* .h */
/* Imprime en salida estándar el detalle de un PCI Vendor */
static void printPCIVen(unsigned short aVenId);

/* Imprime en salida estándar el detalle de un PCI Device */
static void printPCIDev(unsigned short aVenId, unsigned short aDevId);

/* lspci */
void lspci(void);

/* Completa los campos de la estructura PCI_VENTABLE con el aVenID recibido */
/*
void getPCIVenTable(unsigned short aVenId, PPCI_VENTABLE * table) {
    int i;
    for ( i = 0; i < PCI_DEVTABLE_LEN; i++ ) {
        if ( PciVenTable[i].VenId == aVenId ) {
            *table.VenId = aVenId;
            *table.VenShort = PciVenTable[i].VenShort;
            *table.VenFull = PciVenTable[i].VenFull;
        }
}
*/

/* Device ID: Identifies the particular device. Where valid IDs are allocated
 * by the vendor.
 * Vendor ID: Identifies the manufacturer of the device. Where valid IDs are
 * allocated by PCI-SIG to ensure uniqueness and 0xFFFF is an invalid value
 * that will be returned on read accesses to Configuration Space registers of
 * non-existent devices.
 */

/* OJO: Los arreglos de estructuras están en el punto .h */


/* .c */

static void printPCIVen(unsigned short aVenId) {
    int i;
    if ( aVenID == 0xFFFF )
        return ;
    for ( i = 0; i < PCI_VENTABLE_LEN; i++ ) {
        if ( PciVenTable[i].VenId == aVenId ) {
            printf("%s",PciVenTable[i].VenFull);
            return ;
        }
    
}

static void printPCIDev(unsigned short aVenId, unsigned short aDevId) {
    int i;
    if ( aVenID == 0xFFFF )
        return ;
    for ( i = 0; i < PCI_DEVTABLE_LEN; i++ ) {
        if (PciDevTable[i].VenId == aVenId && PciDevTable[i].DevId == aDevId) {
            printf("%s",PciDevTable[i].ChipDesc);
            return ;
        }
}
        
/* Preguntar si tiene o no que recibir argumentos. ¿Y qué retorna? */
void lspci(void) {
    int i, j, data;
    unsigned short aVenId, aDevId;
    
    /* Ciclo que recorre todos los dispositivos */
    for ( i = 0; i < 256; i++) {
        for ( j = 0; j < 32; j++) {
  
    /* Encuentro un dispositivo y le pido el código */

            
    /* Coniverto el código */
        if ( data != 0xFFFFFFFF && data != 0x00000000 ) {
            aVenId = data & 0x0000FFFF;
            aDevId = (data & 0xFFFF0000) >> 16;
        }
    
    /* Lo imprimo */
        printPCIVen(aVenId);
        putchar(' ');
        printPCIDev(aVenId,aDevId);
        putchar('\n');
        }
    }
    return;
}