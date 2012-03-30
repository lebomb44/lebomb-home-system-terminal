#ifndef _BUTTON_
#define _BUTTON_

#include "../global.h"

#define BUTTON_OFF 0
#define BUTTON_ON 1

extern void button_init(void);
extern u08 button_get(u08 ch);

#endif
