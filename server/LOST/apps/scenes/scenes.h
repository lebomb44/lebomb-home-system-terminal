#ifndef _SCENES_H_
#define _SCENES_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t scenes_init(void);
extern void scenes_exec(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);
extern int scenes_form(FILE * stream, REQUEST * req);

__END_DECLS

#endif
