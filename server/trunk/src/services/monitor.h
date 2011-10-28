#ifndef _MONITOR_H_
#define _MONIOR_H_

#include <sys/thread.h>
#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t mon_init(void);
extern void Mond(void *arg) __attribute__ ((noreturn));
extern int mon_showThreads(FILE * stream, REQUEST * req);
extern int mon_showSockets(FILE * stream, REQUEST * req);
extern int mon_showPorts(FILE * stream, REQUEST * req);

__END_DECLS

#endif
