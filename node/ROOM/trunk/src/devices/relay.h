#ifndef _RELAY_
#define _RELAY_

#include "../global.h"

#define RELAY_OFF 0
#define RELAY_ON 1

#define RELAY_OK 0
#define RELAY_ERROR 1

extern void relay_init(void);
extern u08 relay_get(u08 ch);
extern u08 relay_set(u08 ch, u08 val);

#endif
