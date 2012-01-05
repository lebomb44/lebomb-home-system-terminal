#ifndef _REMOTE_H_
#define _REMOTE_H_

#include <stdio.h>
#include <sys/thread.h>

__BEGIN_DECLS

extern uint8_t remote_init(void);
extern void RemoteD(void *arg) __attribute__ ((noreturn));

__END_DECLS

#endif
