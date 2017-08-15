#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/lbcomif.h"

void lbcom_homeeasyTC_send(uint32_t manufacturer, uint8_t group, uint8_t device, uint8_t status)
{
  uint8_t data[7] = {0};

  data[0] = 0x000000FF & (manufacturer>>24);
  data[1] = 0x000000FF & (manufacturer>>16);
  data[2] = 0x000000FF & (manufacturer>>8);
  data[3] = 0x000000FF & (manufacturer);

  data[4] = group;
  data[5] = device;
  data[6] = status;

  lbcomif_send(ID_LOST_MASTER, ID_HOME_EASY_SLAVE, ID_HOME_EASY_SEND_TC, sizeof(data), data);
}

