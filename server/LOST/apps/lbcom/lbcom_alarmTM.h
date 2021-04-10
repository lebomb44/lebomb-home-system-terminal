#ifndef _LBCOM_ALARMTM_H_
#define _LBCOM_ALARMTM_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_alarmTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);

extern uint8_t lbcom_alarmTM_status_get(void);
extern void lbcom_alarmTM_status_set(uint8_t status);
extern void lbcom_alarmTM_status_reset(void);

extern int lbcom_alarmTM_form(FILE * stream, REQUEST * req);
extern int lbcom_alarmTM_xml_get(FILE * stream);

__END_DECLS

#endif

