#ifndef _LBCOM_H_
#define _LBCOM_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

/* Nodes */
#define LBCOM_SERVER 0
#define LBCOM_RFTRX 1

/* LBCOM_SERVER commands */
#define LBCOM_SERVER_GSM_STATUS 0
/* LBCOM_RFTRX commands */
#define LBCOM_RFTRX_GSM_SMS_SEND 1

extern uint8_t lbcom_init(void);
extern void lbcom_run(void);
extern uint8_t lbcom_rxIsReady(void);
extern uint8_t lbcom_rxGetSrc(void);
extern uint8_t lbcom_rxGetDst(void);
extern uint8_t lbcom_rxGetCmd(void);
extern uint8_t lbcom_rxGetLen(void);
extern uint8_t * lbcom_rxGetData(void);
extern void lbcom_rxRelease(void);
extern void lbcom_send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);
extern uint8_t lbcom_gsm_sms_send_with_phone(char * phone, char * msg);
extern uint8_t lbcom_gsm_sms_send(char * msg);

__END_DECLS

#endif

