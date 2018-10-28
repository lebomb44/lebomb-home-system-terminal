#ifndef _LBCOM_HT12ETM_H_
#define _LBCOM_HT12ETM_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_ht12eTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);

extern void lbcom_ht12eTM_code_reset(void);
extern uint16_t lbcom_ht12eTM_address_get(void);
extern uint8_t lbcom_ht12eTM_data_get(void);

extern int lbcom_ht12eTM_form(FILE * stream, REQUEST * req);
extern int lbcom_ht12eTM_xml_get(FILE * stream);

__END_DECLS

#endif

