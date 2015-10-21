#ifndef _ALARM_H_
#define _ALARM_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

typedef enum _ALARM_TYPE_T
{
  ALARM_TYPE_OFF_AUTO = 0,
  ALARM_TYPE_OFF_MANUAL,
  ALARM_TYPE_ON_AUTO,
  ALARM_TYPE_ON_MANUAL,
  ALARM_TYPE_MAX
} ALARM_TYPE_T;

extern uint8_t alarm_init(void);
extern void alarm_perimeter_set(ALARM_TYPE_T type);
extern void alarm_volume_set(ALARM_TYPE_T type);
extern void alarm_simulation_set(ALARM_TYPE_T type);
extern void AlarmD(void *arg) __attribute__ ((noreturn));
extern int alarm_form(FILE * stream, REQUEST * req);
extern int alarm_xml_get(FILE * stream);

__END_DECLS

#endif
