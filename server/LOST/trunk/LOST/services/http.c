#include <stdio.h>
#include <string.h>

#include <dev/nicrtl.h>
#include <dev/lanc111.h>
#include <dev/urom.h>
#include <dev/board.h>

#include <sys/timer.h>
#include <sys/thread.h>
#include <sys/socket.h>
#include <sys/heap.h>

#include <arpa/inet.h>
#include <pro/httpd.h>
#include <pro/ssi.h>
#include <pro/asp.h>

#include <sys/atom.h>

#include "../config.h"
#include "http.h"
#include "web.h"
#include "../devices/xflash.h"

uint8_t http_init(void)
{
  /*
   * Register our device for the file system.
   */
  NutRegisterDevice(&devUrom, 0, 0);
  /*
   * Register CGI routines.
   */
  NutRegisterCgiBinPath("cgi/");

  NutRegisterSsi();
  NutRegisterAsp();
  NutRegisterAspCallback(web_ASPCallback);

  NutThreadCreate("HttpD0", HttpD, 0, 512);
  NutThreadCreate("HttpD1", HttpD, 0, 512);
  NutThreadCreate("HttpD2", HttpD, 0, 512);
  NutThreadCreate("HttpD3", HttpD, 0, 512);

  return 0;
}

THREAD(HttpD, arg)
{
  TCPSOCKET *sock = NULL;
  u_long to = 30000;
  int ret = 0;
  FILE *stream = NULL;

  arg = arg;
  NutThreadSetPriority(150);

  /*
   * Now loop endless for connections.
   */
  while(1)
  {
    /*
     * Create a socket.
     */
    sock = NutTcpCreateSocket();
    if(sock == NULL)
    {
      NutSleep(100);
      continue;
    }
    ret = NutTcpSetSockOpt(sock, SO_RCVTIMEO, &to, sizeof(to));
    if(ret == 0)
    {
      /*
       * Listen on port 80. If we return,
       * we got a client.
       */
      if(NutTcpAccept(sock, 80) == 0)
      {
        if(NutHeapAvailable() > 8192)
        {
          /*
           * Create a stream from the socket, so we can use stdio.
           */
          stream = _fdopen((int) ((uptr_t) sock), "r+b");
          if(stream != NULL)
          {
            /*
             * Process http request.
             */
            NutHttpProcessRequest(stream);
            /*
             * Destroy our stream.
             */
            fclose(stream);
            stream = NULL;
          }
          else
          {
            NutSleep(1);
          }
        }
        else
        {
          NutSleep(1);
        }
      }
      else
      {
        NutSleep(1);
      }
      /*
       * Destroy our device.
       */
    }
    else
    {
      NutSleep(1);
    }
    NutTcpCloseSocket(sock);
    sock = NULL;
  }
}

#define HTTP_METHOD_END " HTTP/1.0\r\n"
#define HTTP_HOST_HEAD  "Host: "
#define HTTP_HOST_END   "\r\n"
#define HTTP_USER       "User-Agent: LOST\r\n"
#define HTTP_REQ_END    "\r\n"

uint8_t http_request_header_start(char* ip, uint16_t port, int method, TCPSOCKET **sock, FILE **stream)
{
  uint32_t rip = 0;
  u_long sock_opt = 0;

  /* Check the entries */
  if((ip == NULL) || (sock == NULL) || (stream == NULL)) { return 1; }

  /* Get the inet for the IP */
  rip = inet_addr(ip);
  /* Check the inet we got */
  if(rip == 0) { *sock = NULL; *stream = NULL; return  2; }

  /* Create of socket for the connection to the IP */
  *sock = NutTcpCreateSocket();
  if(*sock == NULL) { *stream = NULL; return 3; }
  /* Set send timeout */
  sock_opt = 10000;
  NutTcpSetSockOpt(*sock, SO_SNDTIMEO, &sock_opt, sizeof(sock_opt));
  /* Set receive timeout */
  sock_opt = 30000;
  NutTcpSetSockOpt(*sock, SO_RCVTIMEO, &sock_opt, sizeof(sock_opt));

  /* Connect the server of the IP */
  if(NutTcpConnect(*sock, rip, port) != 0) { NutTcpCloseSocket(*sock); *sock = NULL; *stream = NULL; return 4; }

  /* Assign a stream to our connected socket */
  *stream = _fdopen((int) *sock, "r+b");

  /* Check the returned stream */
  if(*stream == NULL) { NutTcpCloseSocket(*sock); *sock = NULL; return 5; }

  /* Send the HTTP header according to the chosen method */
  if(method == METHOD_GET) { fputs("GET", *stream); }
  if(method == METHOD_POST) { fputs("POST", *stream); }
  fputs(" /", *stream);

  return 0;
}

void http_request_header_end(char* host_req, uint32_t content_length, FILE *stream)
{
  /* Check the input stream */
  if(stream != NULL)
  {
    /* Send all the fields of the header */
    fputs(HTTP_METHOD_END, stream);
    /* Send the host target if needed */
    if(host_req!=NULL)
    {
      fputs(HTTP_HOST_HEAD, stream);
      fputs(host_req, stream);
      fputs(HTTP_HOST_END, stream);

    }
    fputs(HTTP_USER, stream);
    fputs("Accept: text/html\r\n",stream);
    fputs("Content-Type: application/x-www-form-urlencoded\r\n", stream);
    fputs("Connection: Close\r\n",stream);
    if(content_length > 0) { fprintf(stream, "Content-Length: %ld\r\n", content_length); }
    fputs(HTTP_REQ_END, stream);
    /* Flush the stream to really send the datas */
    if(content_length == 0 ) { fflush(stream); }
  }
}

void http_request_close(TCPSOCKET **sock, FILE **stream)
{
  /* The message has been sent. Now we can close the connection */
  /* Check the pointers and there contents */
  if(stream != NULL) { if(*stream != NULL) { fflush(*stream); fclose(*stream); *stream = NULL; } }
  /* Also close the associated raw socket */
  if(sock != NULL) { if(*sock != NULL) { NutTcpCloseSocket(*sock); *sock = NULL; } }
}

uint8_t http_status_get(void)
{
  TCPSOCKET *sock = NULL;
  FILE *stream = NULL;
  char* buff = NULL;
  char* out = NULL;

  /* Connect and send the HTTP header */
  if(http_request_header_start("88.190.253.248", 80, METHOD_GET, &sock, &stream) == 0)
  {
    /* Send the URL */
    fputs(LOST_STATUS, stream);
    /* Send the host target */
    http_request_header_end("www.lebomb.fr", 0, stream);
    /* Catch the answer */
    buff = malloc(400);
    if(buff != NULL)
    {
      while(fgets(buff, 400, stream))
      {
        /* Force the end of the string */
        buff[399] = '\0';
        /* On each string search the good answer */
        out = strstr(buff, "LOST safety.http_status OK");
        /* If the good answer is found, we can break the loop */
        if(out) { break; }
      }
      /* The analyze is finished, so free the answer buffer */
      free(buff);
    }
    /* Close the connection : raw socket and the corresponding stream */
    http_request_close(&sock, &stream);
  }
  /* Build the return status */
  if(out) { return 0; }

  return 1;
}

uint8_t http_email_send_once(char* msg)
{
  TCPSOCKET *sock = NULL;
  FILE *stream = NULL;
  char* buff = NULL;
  char* out = NULL;

  /* Connect and send the HTTP header */
  if(http_request_header_start("88.190.253.248", 80, METHOD_GET, &sock, &stream) == 0)
  {
    /* Send the URL */
    fputs(LOST_EMAIL, stream);
    /* and the parameters of the URL */
    if(msg != NULL) { fputs(msg, stream); }
    /* Send the host target */
    http_request_header_end("www.lebomb.fr", 0, stream);
    buff = malloc(400);
    /* Catch the answer */
    if(buff != NULL)
    {
      while(fgets(buff, 400, stream))
      {
        /* Force the end of the string */
        buff[399] = '\0';
        /* On each string search the good answer */
        out = strstr(buff, "LOST Email OK");
        /* If the good answer is found, we can break the loop */
        if(out) { break; }
      }
      /* The analyze is finished, so free the answer buffer */
      free(buff);
    }
    /* Close the connection : raw socket and the corresponding stream */
    http_request_close(&sock, &stream);
  }
  /* Build the return status */
  if(out) { return 0; }

  return 1;
}

uint8_t http_email_send(char* msg)
{
  uint8_t i = 0;

  for(i=0; i<10; i++)
  {
    if(http_email_send_once(msg) == 0) { return 0; }
    NutSleep(1000);
  }

  return 1;
}
