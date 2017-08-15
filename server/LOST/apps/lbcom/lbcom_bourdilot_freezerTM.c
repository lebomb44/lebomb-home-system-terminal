#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/ID.h"

uint8_t _lbcom_bourdilot_freezerTM_network = 0;
int16_t _lbcom_bourdilot_freezerTM_temp = 0;

void lbcom_homeeasyTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
       if(ID_BOURDILOT_FREEZER_NETWORK_TM == cmd) { if(0 == len) { _lbcom_bourdilot_freezerTM_network++; } }
  else if(ID_BOURDILOT_FREEZER_TEMP_TM    == cmd) { if(0 == len) { _lbcom_bourdilot_freezerTM_temp = (0xFF00 & (((int16_t)data[0])<<8)) | (0x00FF & ((int16_t)data[1])); } }
}

uint8_t lbcom_bourdilot_freezerTM_network_get(void) { return _lbcom_bourdilot_freezerTM_network; }
void lbcom_bourdilot_freezerTM_network_set(uint8_t network) { _lbcom_bourdilot_freezerTM_network = network; }
int16_t lbcom_bourdilot_freezerTM_temp_get(void) { return _lbcom_bourdilot_freezerTM_temp; }
void lbcom_bourdilot_freezerTM_temp_set(int16_t temp) { _lbcom_bourdilot_freezerTM_temp = temp; }

