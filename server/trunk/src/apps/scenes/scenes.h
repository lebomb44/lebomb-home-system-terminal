#ifndef _SCENES_H_
#define _SCENES_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t scenes_init(void);
extern void ScenesD(void *arg) __attribute__ ((noreturn));
extern int scenes_form(FILE * stream, REQUEST * req);
extern int scenes_xml_get(FILE * stream);

__END_DECLS

#endif
