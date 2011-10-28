#ifndef _FREEBOX_H_
#define _FREEBOX_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t freebox_init(void);
extern int freebox_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif
