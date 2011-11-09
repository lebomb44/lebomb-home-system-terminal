#ifndef _HTTP_H_
#define _HTTP_H_

#include <sys/thread.h>

__BEGIN_DECLS

extern uint8_t http_init(void);
extern void HttpD(void *arg) __attribute__ ((noreturn));
extern char* http_request(char* ip, uint16_t port, char* req, char* host_req, uint16_t len_to_recv);
extern uint8_t http_status_get(void);
extern uint8_t http_email_send(char* msg);

__END_DECLS

#endif
