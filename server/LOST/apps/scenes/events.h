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
  EVENT_SHUTTERS_ALL = 0,
  EVENT_SHUTTERS_UPSTAIRS,
  EVENT_SHUTTERS_DOWNSTAIRS,
  EVENT_SHUTTERS_C1,
  EVENT_SHUTTERS_C2,
  EVENT_SHUTTERS_C3,
  EVENT_SHUTTERS_C4,
  EVENT_ALARM_ALL,
  EVENT_ALARM_PERIMETER,
  EVENT_ALARM_VOLUME,
  EVENT_SIMU,
  EVENT_POWER_0,
  EVENT_POWER_1,
  EVENT_POWER_2,
  EVENT_POWER_3,
  EVENT_ALARM_PERIMETER_CHECK,
  EVENT_MAX
} EVENT_T;

extern uint8_t events_init(void);
extern void event_set(EVENT_T event, void (*fcnt_start)(void), void (*fcnt_end)(void));
extern void event_config(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);
extern void event_action(EVENT_T event, EVENT_STATUS_T status);
extern void EventsD(void *arg) __attribute__ ((noreturn));
extern int events_form(FILE * stream, REQUEST * req);
extern int events_xml_get(FILE * stream);

__END_DECLS

#endif
