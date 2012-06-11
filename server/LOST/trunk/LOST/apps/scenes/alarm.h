#ifndef _ALARM_H_
#define _ALARM_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t alarm_init(void);
extern void alarm_perimeter_set(uint8_t control);
extern void alarm_volume_set(uint8_t control);
extern void alarm_simulation_set(uint8_t control);
extern void AlarmD(void *arg) __attribute__ ((noreturn));
extern int alarm_form(FILE * stream, REQUEST * req);
extern int alarm_xml_get(FILE * stream);

__END_DECLS

#endif
