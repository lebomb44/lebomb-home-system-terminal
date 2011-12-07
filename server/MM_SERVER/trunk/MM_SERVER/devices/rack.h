#ifndef _RACK_H_
#define _RACK_H_

__BEGIN_DECLS

extern uint8_t rack_init(void);
extern uint8_t rack_temp_status_get(uint16_t temp_th);
extern uint16_t rack_temp_get(void);
extern uint8_t rack_alarm_status_get(void);

__END_DECLS

#endif
