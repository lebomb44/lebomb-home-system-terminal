#ifndef _SQL_H_
#define _SQL_H_

#include <stdio.h>
#include <sys/thread.h>

__BEGIN_DECLS

extern uint8_t sql_init(void);
extern void SqlD(void *arg) __attribute__ ((noreturn));
extern void sql_send(uint8_t start);

__END_DECLS

#endif
