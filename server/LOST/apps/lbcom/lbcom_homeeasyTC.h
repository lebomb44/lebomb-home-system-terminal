#ifndef _LBCOM_HOMEEASYTC_H_
#define _LBCOM_HOMEEASYTC_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_homeeasyTC_send(uint32_t manufacturer, uint8_t group, uint8_t device, uint8_t status);

__END_DECLS

#endif

