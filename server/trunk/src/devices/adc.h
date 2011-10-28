#ifndef _ADC_H_
#define _ADC_H_

__BEGIN_DECLS

extern uint8_t adc_init(void);
extern uint16_t adc_get(uint8_t channel);

__END_DECLS

#endif
