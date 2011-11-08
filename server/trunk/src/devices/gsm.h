#ifndef _GSM_H_
#define _GSM_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern char gsm1[11];
extern char gsm2[11];

extern uint8_t gsm_init(void);
extern uint8_t gsm_status_get(void);
extern uint8_t gsm_sms_send(char * tel, char * msg);
extern char* gsm_sms_receive(void);
extern void GSM_Uart2Uartd(void *arg) __attribute__ ((noreturn));

__END_DECLS

#endif
