#ifndef _EVENTS_H_
#define _EVENTS_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

typedef enum _EVENT_STATUS_T
{
  EVENT_STATUS_OFF = 0,
  EVENT_STATUS_ON,
  EVENT_STATUS_IN_PROGRESS
} EVENT_STATUS_T;

typedef enum _EVENT_T
{
  EVENT_REVEIL = 0,
  EVENT_COUCHE,
  EVENT_CHAUFFAGE_SDB,
  EVENT_CHAUFFAGE_CAFE,
  EVENT_LUMIERE_AUTO,
  EVENT_MUSIQUE_AUTO,
  EVENT_MAX
} EVENT_T;

extern uint8_t events_init(void);
void event_action(EVENT_T event, EVENT_STATUS_T status);
extern void EventsD(void *arg) __attribute__ ((noreturn));
extern int events_form(FILE * stream, REQUEST * req);
extern int events_xml_get(FILE * stream);

__END_DECLS

#endif
