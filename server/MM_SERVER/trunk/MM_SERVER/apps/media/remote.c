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
  NutThreadCreate("RemoteD", RemoteD, 0, 128);

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
  size_t ret = 0;
  char c = 0;
  uint8_t i = 0;
  uint8_t buff[RFIF_HEADER_SIZE + ROOM_RF_DATA_NB + 1] = { 0 };
  uint8_t cksum = 0;

  NutThreadSetPriority(250);
  while(1)
  {
    c = fgetc(stdin);
    /* Search the synchro word */
    if(c == 0xAA)
    {
printf("RF Sync OK\n");
      /* Get the mandatory header */
      ret = fread(buff, RFIF_HEADER_SIZE, 1, stdin);
      if(ret == RFIF_HEADER_SIZE)
      {
printf("RF Header OK\n");
        /* Check the data length received else go to start sequence */
        if(buff[RFIF_REG_LB_TX_DATA_NB] > ROOM_RF_DATA_NB) { continue; }
        /* Get the data using the length included in the header */
        ret = fread(&buff[RFIF_REG_LB_TX_DATA_NB+1], buff[RFIF_REG_LB_TX_DATA_NB]+1, 1, stdin);
        /* Check the received length */
        if(ret == (buff[RFIF_REG_LB_TX_DATA_NB]+1))
        {
printf("RF Nb=%d OK\n",ret);
          /* Compute the checksum */
          for(i=0; i<(RFIF_HEADER_SIZE + buff[RFIF_REG_LB_TX_DATA_NB]); i++) { cksum = cksum + buff[i]; }
          /* And compare it to the one included in the frame */
          if(cksum == buff[RFIF_REG_LB_CKSUM])
          {
printf("RF : src=%d dest=%d cmd=%d nb=%d ", buff[0],buff[1],buff[2],buff[3]);
for(i=0; i<(RFIF_HEADER_SIZE + ROOM_RF_DATA_NB + 1); i++) { printf("buff[%d]=%d ",i,buff[i]); }
printf("\n");
            /* If this is a SCENE command */
            if(buff[2] == 1)
            {
              /* We must have 2 data words */
              if(buff[3] == 2)
              /* Execute the corresponding scene */
              if(buff[4] < EVENT_MAX) { event_action(buff[4], buff[5]); }
              if((EVENT_MAX <= buff[4]) && (buff[4] < (EVENT_MAX + POWER_MAX))) { power_set(buff[4] - EVENT_MAX, buff[5]); }
            }
          }
        }
      }
    }
    if(ret > 0) { fputc(c, stdout); }
    NutSleep(1);
  }
}
