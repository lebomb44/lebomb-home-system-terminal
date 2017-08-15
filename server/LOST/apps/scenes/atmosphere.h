#ifndef _ATMOSPHERE_H_
#define _ATMOSPHERE_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t atmosphere_init(void);
extern void atmosphere_set(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);
extern int atmosphere_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif
