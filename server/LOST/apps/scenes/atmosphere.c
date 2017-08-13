#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pro/httpd.h>

#include "atmosphere.h"

enum ATM_T
{
  ATM_UNKNOWN = 0,
  ATM_CINEMA,
  ATM_ROMANTIQUE,
  ATM_ECO
};

uint8_t atmosphere_init(void)
{
  NutRegisterCgi("atm.cgi", atmosphere_form);

  return 0;
}

int atmosphere_form(FILE * stream, REQUEST * req)
{
  char* atm = NULL;
  unsigned int value = ATM_UNKNOWN;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    atm = NutHttpGetParameter(req, "atm");
    if(atm)
    {
      value = strtoul(atm, NULL, 10);
      switch(value)
      {
        case ATM_CINEMA :
          break;
        case ATM_ROMANTIQUE :
          break;
        case ATM_ECO :
          break;
        default :
          break;
      }
    }
    fflush(stream);
  }

  return 0;
}
