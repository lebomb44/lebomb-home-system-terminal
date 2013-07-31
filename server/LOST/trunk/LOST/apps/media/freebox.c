#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pro/httpd.h>

#include "../../services/http.h"
#include "freebox.h"

#define FREEBOX_REQUEST_SIZE_MAX 200

uint8_t freebox_init(void)
{
  /* Register the CGI form managing the Freebox interface */
  NutRegisterCgi("freebox.cgi", freebox_form);

  return 0;
}

int freebox_form(FILE * stream, REQUEST * req)
{
  TCPSOCKET *sock_out = NULL;
  FILE *stream_out = NULL;
  int nb = 0;
  int i;
  char *name = NULL;
  char *value = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(0 == http_request_header_start("212.027.040.254", 80, METHOD_GET, &sock_out, &stream_out))
  {
    /* Build the beginning of the URL */
    fputs("pub/remote_control?", stream_out);
    /* Count the arguments in the request */
    nb = NutHttpGetParameterCount(req);
    /* Build the new request with all the arguments coming from the request */
    for (i=0; i<nb; i++)
    {
      /* Get the parameter name */
      name = NutHttpGetParameterName(req, i);
      /* Get the parameter value */
      value = NutHttpGetParameterValue(req, i);
      /* Check the received parameters */
      if((NULL != name) && (NULL != value))
      {
        /* Add a separator only if it is not the first parameter */
        if(0 < i) { fputs("&", stream_out); }
        /* Concat this name */
        fputs(name, stream_out);
        /* Concat the separator */
        fputs("=", stream_out);
        /* Concat this value */
        fputs(value, stream_out);
      }
    }
    http_request_header_end(NULL, 0, stream_out);
    http_request_close(&sock_out, &stream_out);
  }

  return 0;
}
