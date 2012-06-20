#ifndef _GSM_H_
#define _GSM_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t gsm_init(void);
extern uint8_t gsm_status_get(void);
extern uint8_t gsm_sms_send(char * msg);
extern char* gsm_sms_receive(void);

__END_DECLS

#endif
