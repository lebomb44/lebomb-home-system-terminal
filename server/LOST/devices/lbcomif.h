#ifndef _LBCOMIF_H_
#define _LBCOMIF_H_

#include <stdio.h>
#include <pro/httpd.h>
#include "ID.h"

__BEGIN_DECLS

extern uint8_t lbcomif_init(void);
extern void lbcomif_registerSlaveCallBack(uint8_t cmd, void (*callBack) (uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data));
void lbcomif_execSlaveCallBack(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);
extern uint8_t lbcomif_run(void);
extern uint8_t lbcomif_rxIsReady(void);
extern uint8_t lbcomif_rxGetSrc(void);
extern uint8_t lbcomif_rxGetDst(void);
extern uint8_t lbcomif_rxGetCmd(void);
extern uint8_t lbcomif_rxGetLen(void);
extern uint8_t * lbcomif_rxGetData(void);
extern void lbcomif_rxRelease(void);
extern void lbcomif_sendByte(uint8_t byte);
extern void lbcomif_flush(void);
extern void lbcomif_send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);

__END_DECLS

#endif

