#ifndef _ALARM_H_
#define _ALARM_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t alarm_init(void);
extern void AlarmD(void *arg) __attribute__ ((noreturn));
extern int alarm_form(FILE * stream, REQUEST * req);
extern int alarm_xml_get(FILE * stream);

__END_DECLS

#endif
