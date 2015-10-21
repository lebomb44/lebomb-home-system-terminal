#ifndef _EEPROM_
#define _EEPROM_

#include "../global.h"

# define EERIE 3
# define EEMWE 2
# define EEWE 1
# define EERE 0

extern void eeprom_init(void);
extern u08 eeprom_read(u16 address_eeprom);
extern void eeprom_write(u16 address_eeprom, u08 data_eeprom);

#endif
