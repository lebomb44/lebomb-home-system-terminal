#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/lbcomif.h"

void lbcom_bourdilot_freezerTC_network(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_BOURDILOT_FRIDGE_SLAVE, ID_BOURDILOT_FREEZER_NETWORK_TC, 0, NULL);
}

void lbcom_bourdilot_freezerTC_temp(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_BOURDILOT_FRIDGE_SLAVE, ID_BOURDILOT_FREEZER_TEMP_TC, 0, NULL);
}

