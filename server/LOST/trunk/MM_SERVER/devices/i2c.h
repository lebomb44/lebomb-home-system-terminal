#ifndef _I2C_
#define _I2C_

extern uint8_t i2c_init(void);
extern uint8_t i2c_get(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data);
extern uint8_t i2c_set(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data);
extern uint8_t i2c_broadcast_set(uint8_t addr, uint8_t nb, uint8_t* data);

#endif
