#ifndef _MONITOR_H_
#define _MONITOR_H_

#include <sys/thread.h>
#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t mon_init(void);
extern void Mond(void *arg) __attribute__ ((noreturn));
extern int mon_show(FILE * stream, REQUEST * req);

__END_DECLS

#endif
