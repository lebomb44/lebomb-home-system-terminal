#ifndef _ATMOSPHERE_H_
#define _ATMOSPHERE_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t atmosphere_init(void);
extern int atmosphere_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif
