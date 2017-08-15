#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pro/httpd.h>
#include "../../devices/lbcomif.h"

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
  lbcomif_registerSlaveCallBack(ID_LOST_ATMOSPHERE_SET_TC, atmosphere_set);
  NutRegisterCgi("atm.cgi", atmosphere_form);

  return 0;
}

void atmosphere_set(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  uint8_t value = ATM_UNKNOWN;

  if(1 == len)
  {
    value = data[0];
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
}

int atmosphere_form(FILE * stream, REQUEST * req)
{
  char* atm = NULL;
  uint8_t value = ATM_UNKNOWN;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    atm = NutHttpGetParameter(req, "atm");
    if(atm)
    {
      value = strtoul(atm, NULL, 10);
      atmosphere_set(ID_LOST_MASTER, ID_LOST_SLAVE, ID_LOST_ATMOSPHERE_SET_TC, 1, &value);
    }
    fflush(stream);
  }

  return 0;
}

