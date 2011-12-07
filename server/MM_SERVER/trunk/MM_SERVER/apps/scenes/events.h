#ifndef _EVENTS_H_
#define _EVENTS_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t events_init(void);
extern void EventsD(void *arg) __attribute__ ((noreturn));
extern int events_form(FILE * stream, REQUEST * req);
extern int events_xml_get(FILE * stream);

__END_DECLS

#endif
