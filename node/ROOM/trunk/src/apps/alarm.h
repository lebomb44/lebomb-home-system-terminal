#ifndef _ALARM_
#define _ALARM_

#include "../global.h"

extern void alarm_init(void);
extern void alarm_cycle(void);
extern u08 alarm_control_shutters(void);
extern u08 alarm_status_shutters(void);
extern u08 alarm_trig_shutters(void);

#endif
