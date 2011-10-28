#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern char admin_gsm1[11];
extern char admin_gsm2[11];

extern uint8_t admin_init(void);
extern int admin_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif
