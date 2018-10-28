#ifndef _LBCOM_HT12ETC_H_
#define _LBCOM_HT12ETC_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern void lbcom_ht12eTC_send(uint16_t address, uint8_t data);

extern int lbcom_ht12eTC_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif

