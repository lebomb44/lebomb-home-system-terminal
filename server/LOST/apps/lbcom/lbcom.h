#ifndef _LBCOM_H_
#define _LBCOM_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t lbcom_init(void);
extern void LbComD(void *arg) __attribute__ ((noreturn));
extern int lbcom_form(FILE * stream, REQUEST * req);
extern int lbcom_homeeasy_form(FILE * stream, REQUEST * req);
extern int lbcom_gsm_form(FILE * stream, REQUEST * req);
extern int lbcom_bourdilot_freezer_form(FILE * stream, REQUEST * req);
extern int lbcom_xml_get(FILE * stream);

__END_DECLS

#endif

