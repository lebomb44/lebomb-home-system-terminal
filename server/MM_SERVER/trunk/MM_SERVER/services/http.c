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

#include "http.h"
#include "web.h"
#include "../devices/xflash.h"

uint8_t http_init(void)
{
  /*
   * Register our device for the file system.
   */
  NutRegisterDevice(&devUrom, 0, 0);
  // TODO NutRegisterDevice(&devXflash, 0, 0);
  // TODO NutRegisterHttpRoot("XFLASH:");
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
  NutThreadCreate("HttpD4", HttpD, 0, 512);
  NutThreadCreate("HttpD5", HttpD, 0, 512);
  NutThreadCreate("HttpD6", HttpD, 0, 512);
  NutThreadCreate("HttpD7", HttpD, 0, 512);

  return 0;
}

THREAD(HttpD, arg)
{
  TCPSOCKET *sock = NULL;
  u_long to = 30000;
  int ret = 0;
  FILE *stream = NULL;

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

#define HTTP_GET_HEAD  "GET /"
#define HTTP_GET_END   " HTTP/1.0\r\n"
#define HTTP_HOST_HEAD "Host: "
#define HTTP_HOST_END  "\r\n"
#define HTTP_USER      "User-Agent: LOST\r\n"
#define HTTP_REQ_END   "\r\n"
char* http_request(char* ip, uint16_t port, char* req, char* host_req, uint16_t len_to_recv)
{
  uint32_t rip = 0;
  TCPSOCKET *sock = NULL;
  u_long sock_opt = 0;
  char* buff = NULL;
  size_t len_to_send = 0;
  size_t total = 0;
  int nb = 0;

  /* Get the inet for the IP */
  rip = inet_addr(ip);
  /* Check the inet we got */
  if(rip == 0) { return  NULL; }

  /* Create of socket for the connection to the IP */
  sock = NutTcpCreateSocket();
  if(sock == NULL) { return NULL; }
  sock_opt = 10000;
  NutTcpSetSockOpt(sock, SO_RCVTIMEO, &sock_opt, sizeof(sock_opt));
  
  /* Connect the server of the IP */
  if(NutTcpConnect(sock, rip, port) != 0) { return NULL; }

  /* Get the length of the prepared request */
  len_to_send = sizeof(HTTP_GET_HEAD ) + strnlen(req     , 500) + sizeof(HTTP_GET_END ) \
              + sizeof(HTTP_HOST_HEAD) + strnlen(host_req, 100) + sizeof(HTTP_HOST_END) \
              + sizeof(HTTP_USER     ) \
              + sizeof(HTTP_GET_END  );

  /* Allocation of the buffer required for the request to send */
  buff = malloc(len_to_send + 1);
  /* If the allocation failed return in error */
  if(buff == NULL) { NutTcpCloseSocket(sock); return NULL; }

  /* Create the HTTP request beginning */
  strncpy(buff, HTTP_GET_HEAD, sizeof(HTTP_GET_HEAD));
  /* Build the URL */
  if(req) { strncat(buff, req, 500); }
  /* Finish to build the URL */
  strncat(buff, HTTP_GET_END, sizeof(HTTP_GET_END));

  /* Add the host target if necessary */
  if(host_req)
  {
    strncat(buff, HTTP_HOST_HEAD, sizeof(HTTP_HOST_HEAD));
    strncat(buff, host_req, 100);
    strncat(buff, HTTP_HOST_END, sizeof(HTTP_HOST_END));
  }

  /* Add the user agent */
  strncat(buff, HTTP_USER, sizeof(HTTP_USER));

  /* Add the request end */
  strncat(buff, HTTP_REQ_END, sizeof(HTTP_REQ_END));

  /*
   * Send HTTP request to the server. NutTcpSend() doesn't
   * guarantee to send out all bytes, thus the loop.
  */
  total = 0;
  while(total < len_to_send)
  {
    // Send the message by block
    nb = NutTcpSend(sock, buff + total, len_to_send - total);
    // And verify that there is no error
    if(nb <= 0) { break; }
    total = total + nb;
  }
  free(buff);
  buff = NULL;

  /*
   * Read server response.
   */
  total = 0;
  /* Allocation of the buffer required for the request to receive */
  if(len_to_recv > 0)
  {
    buff = malloc(len_to_recv + 1);
    //If the allocation failed return in error
    if(buff == NULL) { NutTcpCloseSocket(sock); return NULL; }
    while (total < len_to_recv)
    {
      //Receive the message by block
      nb = NutTcpReceive(sock, buff + total, len_to_recv - total);
      //And verify that there is no error
      if(nb <= 0) { break; }
      total = total + nb;
    }
    //Force the position of the end because of possible corruption
    if(total > len_to_recv) { total = len_to_recv; }
    buff[total] = '\0';
  }
  /* The message has been sent. Now we can close the connection */
  NutTcpCloseSocket(sock);

  return buff;
}

uint8_t http_status_get(void)
{
  char* buff=NULL;
  char* out=NULL;

  buff = http_request("88.190.253.248", 80, "status.txt", "www.lebomb.fr", 400);
  if(buff == NULL) { return 1; }
  out = strstr(buff, "safety.http_status");
  free(buff);
  if(out) { return 0; }
  return 1;
}

uint8_t http_email_send_once(char* msg)
{
  char url[sizeof("email.php?msg=")+20];
  char* buff=NULL;
  char* out=NULL;

  strncpy(url, "email.php?msg=", sizeof(url));
  strncat(url, msg, sizeof(url));
  buff = http_request("88.190.253.248", 80, url, "www.lebomb.fr", 400);
  if(buff == NULL) { return 1; }
  out = strstr(buff, "OK");
  free(buff);
  if(out) { return 0; }
  return 1;
}

uint8_t http_email_send(char* msg)
{
  uint8_t i = 0;

  // TODO for(i=0; i<10; i++)
  {
    if(http_email_send_once(msg) == 0) { return 0; }
    NutSleep(1000);
  }

  return 1;
}
