#ifndef _SCENES_H_
#define _SCENES_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t scenes_init(void);
extern int scenes_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif
