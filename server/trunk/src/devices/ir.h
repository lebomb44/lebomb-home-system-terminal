#ifndef _IR_
#define _IR_

#define RC5 0
#define SIRCS 1

uint8_t ir_init(void);
uint8_t ir_send(int type, uint8_t addr, uint8_t cmd, uint8_t nb);

#endif
