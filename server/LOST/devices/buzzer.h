#ifndef _BUZZER_H_
#define _BUZZER_H_

__BEGIN_DECLS

extern uint8_t buzzer_init(void);
extern void buzzer_on(void);
extern void buzzer_off(void);
extern void buzzer_start(uint16_t duration);
extern void buzzer_stop(void);
extern void buzzer_update(void);
extern uint16_t buzzer_state(void);

__END_DECLS

#endif
