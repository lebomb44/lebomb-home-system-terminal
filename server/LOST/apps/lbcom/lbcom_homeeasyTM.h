#ifndef _LBCOM_HOMEEASYTM_H_
#define _LBCOM_HOMEEASYTM_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_homeeasyTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);

extern void lbcom_homeeasyTM_code_reset(void);
extern uint32_t lbcom_homeeasyTM_manufacturer_get(void);
extern uint8_t lbcom_homeeasyTM_group_get(void);
extern uint8_t lbcom_homeeasyTM_device_get(void);
extern uint8_t lbcom_homeeasyTM_status_get(void);

extern int lbcom_homeeasyTM_form(FILE * stream, REQUEST * req);
extern int lbcom_homeeasyTM_xml_get(FILE * stream);

__END_DECLS

#endif

