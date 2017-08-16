#ifndef _LBCOM_GSMTC_H_
#define _LBCOM_GSMTC_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_gsmTC_init(void);
extern void lbcom_gsmTC_checkpowerup(void);
extern void lbcom_gsmTC_powerupdown(void);
extern void lbcom_gsmTC_powerreset(void);
extern void lbcom_gsmTC_getsignalstrenght(void);
extern uint8_t lbcom_gsmTC_sms_send_with_phone(char * phone, char * msg);
extern uint8_t lbcom_gsmTC_sms_send(char * msg);

extern int lbcom_gsmTC_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif

