#ifndef _HTTP_H_
#define _HTTP_H_

#include <stdio.h>
#include <sys/thread.h>
#include <sys/socket.h>
#include <pro/httpd.h>

__BEGIN_DECLS

extern uint8_t http_init(void);
extern void HttpD(void *arg) __attribute__ ((noreturn));
extern uint8_t http_request_header_start(char* ip, uint16_t port, int method, TCPSOCKET **sock, FILE **stream);
extern void http_request_header_end(char* host_req, uint32_t content_length, FILE *stream);
extern void http_request_close(TCPSOCKET **sock, FILE **stream);
extern uint8_t http_status_get(void);
extern uint8_t http_email_send(char* msg);

__END_DECLS

#endif
