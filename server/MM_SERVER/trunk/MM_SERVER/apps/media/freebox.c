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
  char* buff_send = NULL;
  char* buff_recv = NULL;
  int nb = 0;
  int i;
  char *name=NULL;
  char *value=NULL;
  size_t len = 0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBot(stream, "text/html", -1);

  /* Alloc the buffer requered for the request to send */
  buff_send = malloc(FREEBOX_REQUEST_SIZE_MAX);
  /* If the allocation failed return in error */
  if(buff_send == NULL)
  {
    return -1;
  }

  /* Create the HTTP request begining */
  strncpy(buff_send, "pub/remote_control?", 19+1);
  /* Count the arguments in the request */
  nb = NutHttpGetParameterCount(req);
  /* Build the new request with all the arguments comming from the request */
  for (i=0; i<nb; i++)
  {
    /* Get the a parameter name */
    name = NutHttpGetParameterName(req, i);
    /* Get the parameter value */
    value = NutHttpGetParameterValue(req, i);
    /* Get the space left */
    len = strnlen(buff_send, FREEBOX_REQUEST_SIZE_MAX);
    /* Only concat if the parmeter separator (if required) name, separator, value and http end are not too big */
    if(((i?1:0)+strnlen(name, len)+1+strnlen(value, len)+38+0+4+1) <= (FREEBOX_REQUEST_SIZE_MAX-len))
    {
      /* Add a separator only if it is not the first parameter */
      if(i>0) { strncat(buff_send, "&", 2); }
      /* Concat this name */
      strncat(buff_send, name, len);
      /* Concat the separator */
      strncat(buff_send, "=", 2);
      /* Concat this value */
      strncat(buff_send, value, len);
    }
    else
    {
      /* If these is not enought space, continue without the others arguments */
      break;
    }
  }

  buff_recv = http_request("212.027.040.254", 80, buff_send, NULL, 0);
  if(buff_send != NULL) { free(buff_send); }
  if(buff_recv != NULL) { free(buff_recv); }
  
  return 0;
}
