#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include "remote.h"

#include "../../devices/lbcom.h"
#include "../scenes/safety.h"

uint8_t remote_init(void)
{
  NutThreadCreate("RemoteD", RemoteD, 0, 512);

  return 0;
}

THREAD(RemoteD, arg)
{
  arg = arg;
  NutThreadSetPriority(250);
  while(1)
  {
    lbcom_run();
    if(lbcom_rxIsReady())
    {
      if(LBCOM_SERVER == lbcom_rxGetDst())
      {
        if(LBCOM_SERVER_GSM_STATUS == lbcom_rxGetCmd())
        {
          if(1 == lbcom_rxGetLen())
          {
             safety_gsm_connection_set(lbcom_rxGetData[0]);
          }
        }
      }
      lbcom_rxRelease();
    }
    NutSleep(1);
  }
}
