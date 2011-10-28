#ifndef _RC_H_
#define _RC_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t rc_init(void);
extern int rc_form(FILE * stream, REQUEST * req);
extern int rc_xml_get(FILE * stream);

__END_DECLS

#endif
