#ifndef _LBCOM_GSMTM_H_
#define _LBCOM_GSMTM_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_gsmTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);

extern void lbcom_gsmTM_init_status_set(uint8_t status);
extern uint8_t lbcom_gsmTM_init_status_get(void);

extern void lbcom_gsmTM_checkpowerup_status_set(uint8_t status);
extern uint8_t lbcom_gsmTM_checkpowerup_status_get(void);

extern void lbcom_gsmTM_signalstrenght_status_set(uint8_t status, uint32_t value);
extern uint8_t lbcom_gsmTM_signalstrenght_status_get(void);
extern uint32_t lbcom_gsmTM_signalstrenght_value_get(void);

extern void lbcom_gsmTM_sendsms_status_set(uint8_t status);
extern uint8_t lbcom_gsmTM_sendsms_status_get(void);

extern int lbcom_gsmTM_form(FILE * stream, REQUEST * req);
extern int lbcom_gsmTM_xml_get(FILE * stream);

__END_DECLS

#endif

