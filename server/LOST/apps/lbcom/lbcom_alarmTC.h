#ifndef _LBCOM_ALARMTC_H_
#define _LBCOM_ALARMTC_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_alarmTC_status(void);

extern int lbcom_alarmTC_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif

