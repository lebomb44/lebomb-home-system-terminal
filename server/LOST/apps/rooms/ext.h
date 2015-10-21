#ifndef _EXT_H_
#define _EXT_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t ext_init(void);
extern int ext_form(FILE * stream, REQUEST * req);
extern int ext_xml_get(FILE * stream);

__END_DECLS

#endif
