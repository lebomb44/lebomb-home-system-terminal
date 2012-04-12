#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include "remote.h"

#include "../../devices/power.h"
#include "../scenes/scenes.h"
#include "../scenes/events.h"
#include "../rooms/rooms.h"

uint8_t remote_init(void)
{
  NutThreadCreate("RemoteD", RemoteD, 0, 512);

  return 0;
}

#define PROT_RF_LB 1
#define PROT_START 1
#define PROT_FINISHED 0

#define RFIF_HEADER_SIZE       (4)
#define RFIF_REG_LB_TX_DATA_NB (RFIF_HEADER_SIZE - 1)
#define RFIF_REG_LB_CKSUM      (RFIF_REG_LB_TX_DATA_NB + buff[RFIF_REG_LB_TX_DATA_NB] + 1)

/*
Check ACK : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=112&data=?
Set Type  : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=97&data=1
Set SRC   : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=98&data=10
Set DST   : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=99&data=1
Set CMD   : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=100&data=1
Set NB    : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=101&data=2
Set Data0 : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=102&data=0
Set Data1 : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=103&data=1
Set ACK   : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=112&data=1

Check ACK : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=112&data=?
Set Data0 : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=102&data=1
Set ACK   : http://lebomb.no-ip.com/cgi/ext.cgi?sla=6&addr=112&data=1
*/

THREAD(RemoteD, arg)
{
  int ret = 0;
  uint8_t i = 0;
  uint8_t buff[RFIF_HEADER_SIZE + ROOM_RF_DATA_NB + 1] = { 0 };
  uint8_t cksum = 0;

  arg = arg;
  NutThreadSetPriority(250);
  while(1)
  {
    ret = fgetc(stdin);
    /* Search the synchro word */
    if(ret == 0xAA)
    {
      /* Get the mandatory header */
      for(i=0; i<RFIF_HEADER_SIZE; i++)
      {
        ret = fgetc(stdin);
        if(ret >= 0) { buff[i] = ret; }
        else { i = 0; break; }
      }
      if((i == RFIF_HEADER_SIZE) && ((buff[1] == 0) || (buff[1] == 1)))
      {
        /* Check the data length received */
        if(buff[RFIF_REG_LB_TX_DATA_NB] <= ROOM_RF_DATA_NB)
        {
          /* Get the data using the length included in the header */
          for(i=0; i<(buff[RFIF_REG_LB_TX_DATA_NB]+1); i++)
          {
            ret = fgetc(stdin);
            if(ret >= 0) { buff[RFIF_REG_LB_TX_DATA_NB+1+i] = ret; }
            else { break; }
          }
          /* Check the received length */
          if(i == (buff[RFIF_REG_LB_TX_DATA_NB]+1))
          {
            /* Erase the checksum */
            cksum = 0;
            /* Compute the checksum */
            for(i=0; i<(RFIF_HEADER_SIZE + buff[RFIF_REG_LB_TX_DATA_NB]); i++) { cksum = cksum + buff[i]; }
            /* And compare it to the one included in the frame */
            if(cksum == buff[RFIF_REG_LB_CKSUM])
            {
              /* If this is a SCENE command */
              if(buff[2] == 1)
              {
                /* We must have 2 data words */
                if(buff[3] == 2)
                {
                  /* Execute the corresponding scene */
                  if((0xCA <= buff[4]) && (buff[4] < (0xCA+EVENT_MAX)) && (0xCA <= buff[5])) { event_action(buff[4]-0xCA, buff[5]-0xCA); }
                  /* printf("scene=%d data=%d\n",buff[4],buff[5]); */
                  fpurge(stdin);
                }
              }
            }
          }
        }
      }
    }
    NutSleep(1);
  }
}
