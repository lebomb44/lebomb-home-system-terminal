#ifndef _UPS_H_
#define _UPS_H_

__BEGIN_DECLS

extern uint8_t ups_init(void);
extern uint8_t ups_temp_status_get(uint16_t temp_th);
extern uint16_t ups_temp_get(void);
extern uint8_t ups_power_status_get(void);

__END_DECLS

#endif
