#ifndef _LBCOM_BOURDILOT_FREEZERTM_H_
#define _LBCOM_BOURDILOT_FREEZERTM_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_bourdilot_freezerTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);

extern uint8_t lbcom_bourdilot_freezerTM_network_get(void);
extern void lbcom_bourdilot_freezerTM_network_set(uint8_t network);
extern int16_t lbcom_bourdilot_freezerTM_temp_get(void);
extern void lbcom_bourdilot_freezerTM_temp_set(int16_t temp);

extern int lbcom_bourdilot_freezerTM_form(FILE * stream, REQUEST * req);
extern int lbcom_bourdilot_freezerTM_xml_get(FILE * stream);

__END_DECLS

#endif

