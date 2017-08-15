#ifndef _SAFETY_H_
#define _SAFETY_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t safety_init(void);
extern void safety_gsm_status_set(uint8_t gsm_connection);
extern uint16_t safety_ups_temp_value_get(void);
extern uint16_t safety_rack_temp_value_get(void);
extern void SafetyUpsRackD(void *arg) __attribute__ ((noreturn));
extern void SafetyHttpD(void *arg) __attribute__ ((noreturn));
extern int safety_form(FILE * stream, REQUEST * req);
extern int safety_xml_get(FILE * stream);

__END_DECLS

#endif
