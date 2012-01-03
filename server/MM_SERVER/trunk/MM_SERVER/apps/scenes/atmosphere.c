#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pro/httpd.h>

#include "../rooms/rooms.h"
#include "atmosphere.h"

typedef enum _ATM_T
{
  ATM_UNKNOWN =0,
  ATM_CINEMA,
  ATM_ROMANTIQUE,
  ATM_ECO
} ATM_T;

uint8_t atmosphere_init(void)
{
  NutRegisterCgi("atm.cgi", atmosphere_form);

  return 0;
}

int atmosphere_form(FILE * stream, REQUEST * req)
{
  char* atm=0;
  ATM_T value = ATM_UNKNOWN;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    atm = NutHttpGetParameter(req, "atm");
    if(atm)
    {
      value = strtoul(atm, NULL, 10);
      switch(value)
      {
        case ATM_CINEMA :
          room_light_set(ROOM_SALON, 0, 100);
          room_shutter_set(ROOM_SALON, 0, 0);
          break;
        case ATM_ROMANTIQUE :
          room_light_set(ROOM_SALON, 0, 100);
          room_shutter_set(ROOM_SALON, 0, 0);
          break;
        case ATM_ECO :
          room_light_set(ROOM_SALON, 0, 100);
          room_shutter_set(ROOM_SALON, 0, 0);
          break;
        default :
          break;
      }
    }
    fflush(stream);
  }

  return 0;
}
