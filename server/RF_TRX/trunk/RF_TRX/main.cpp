#include <inttypes.h>
#include <Arduino.h>

#include <ID/ID.h>
#include <HomeEasy/HomeEasy.h>
#include <LB_NRF24/LB_NRF24.h>
#include <LB_Com/LB_Com.h>

HomeEasy homeEasy;
LB_NRF24 nrf24;
LB_Com lbCom;

int main(void)
{
  homeEasy.init();
  nrf24.init();
  lbCom.init();

while(1)
{
  homeEasy.run();
  if(true == homeEasy.rxCodeIsReady())
  {
/*
    Serial.println();
    Serial.print(homeEasy.rxGetCode(), HEX);Serial.print(" : ");
    Serial.print(homeEasy.rxGetManufacturer(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetGroup(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetDevice(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetStatus(), HEX);Serial.println();
*/
    if(HOME_EASY_ROVER_RC == homeEasy.rxGetManufacturer())
    {
      if(true == nrf24.txIsReady())
      {
        uint8_t cmd = 0xFF;
        if(0 == homeEasy.rxGetDevice()) { cmd = ROVER_CMD_FWD; }
		if(1 == homeEasy.rxGetDevice()) { cmd = ROVER_CMD_TURN; }
		if(2 == homeEasy.rxGetDevice()) { cmd = ROVER_CMD_STOP; }
		uint8_t status = 0;
		status = homeEasy.rxGetStatus();
        nrf24.send(ROVER_RC_ID, ROVER_ID, cmd, 1, & status);
        homeEasy.rxRelease();
      }
    }
    else
    {
      if(true == lbCom.txIsReady())
      {
        uint32_t code = 0;
        code = homeEasy.rxGetCode();
        lbCom.send(HOME_EASY_ID, LOST_ID, HOME_EASY_DIG_CMD, 4, (uint8_t *) &code);
        homeEasy.rxRelease();
      }
    }
  }

  lbCom.run();
  if(true == lbCom.rxIsReady())
  {
    if(HOME_EASY_ID == lbCom.rxGetDst())
    {
      if(4 == lbCom.rxGetLen())
      {
        if(true == homeEasy.txIsReady())
        {
          homeEasy.send(*((uint32_t *)lbCom.rxGetData()));
          lbCom.rxRelease();
        }
      }
      else
      {
        lbCom.rxRelease();
      }
    }
    else
    {
      if(true == nrf24.txIsReady())
      {
        nrf24.send(lbCom.rxGetSrc(), lbCom.rxGetDst(), lbCom.rxGetCmd(), lbCom.rxGetLen(), lbCom.rxGetData());
        lbCom.rxRelease();
      }
    }
  }

  nrf24.run();
  if(true == nrf24.rxIsReady())
  {
    if(true == lbCom.txIsReady())
    {
      lbCom.send(nrf24.rxGetSrc(), nrf24.rxGetDst(), nrf24.rxGetCmd(), nrf24.rxGetLen(), nrf24.rxGetData());
      nrf24.rxRelease();
    }
  }
}
}

