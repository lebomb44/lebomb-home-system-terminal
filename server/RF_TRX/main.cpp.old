#include <inttypes.h>
#include <Arduino.h>

#include <ID/ID.h>
#include <HomeEasy/HomeEasy.h>
#include <RH_NRF24/NRF24.h>
#include <LB_Com/LB_Com.h>

HomeEasy homeEasy; // OUT = B1(OC1A), IN = B0(ICP), MODE = D5, EN = D4
NRF24 nrf24(7, SS); // B5(SCK), B4(MISO), B3(MOSI), B2(SS), D7(CE)
LB_Com lbCom; // OUT = D1(TXD), IN = D0(RXD)

int main(void)
{
  uint8_t nrf24_dstAddr[5] = {0};
  nrf24_dstAddr[0] = LOST_ID;
  nrf24_dstAddr[1] = 0;
  nrf24_dstAddr[2] = 0;
  nrf24_dstAddr[3] = 0;
  nrf24_dstAddr[4] = 0;
  uint8_t nrf24_txRawData[32] = {0};
  uint8_t nrf24_rxRawData[32] = {0};
  uint8_t nrf24_rxLen = 32;

  homeEasy.init();
  nrf24.init();
  nrf24.setChannel(1);
  nrf24.setThisAddress(nrf24_dstAddr, 5);
  nrf24.setPayloadSize(32);
  nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm);
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
      if(HOME_EASY_ROVER0_RC == homeEasy.rxGetManufacturer())
      {
        if(false == nrf24.isSending())
        {
          nrf24_dstAddr[0] = ROVER0_ID;
          nrf24.setTransmitAddress(nrf24_dstAddr, 5);
          nrf24_txRawData[0] = ROVER0_RC_ID;
          if(0 == homeEasy.rxGetDevice()) { nrf24_txRawData[1] = ROVER_CMD_FWD; }
          if(1 == homeEasy.rxGetDevice()) { nrf24_txRawData[1] = ROVER_CMD_TURN; }
          if(2 == homeEasy.rxGetDevice()) { nrf24_txRawData[1] = ROVER_CMD_STOP; }
          nrf24_txRawData[2] = homeEasy.rxGetStatus();
          nrf24.send(nrf24_txRawData, 3);
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
        if(false == nrf24.isSending())
        {
          if(33 > lbCom.rxGetLen())
          {
            nrf24_dstAddr[0] = lbCom.rxGetDst();
            nrf24.setTransmitAddress(nrf24_dstAddr, 5);
            nrf24_txRawData[0] = lbCom.rxGetSrc();
            nrf24_txRawData[1] = lbCom.rxGetCmd();
            for(uint8_t i=0; i<lbCom.rxGetLen(); i++) { nrf24_txRawData[2+i] = lbCom.rxGetData()[i]; }
            nrf24.send(nrf24_txRawData , 2+lbCom.rxGetLen());
          }
          lbCom.rxRelease();
        }
      }
    }

    if(true == nrf24.available())
    {
      if(true == lbCom.txIsReady())
      {
        nrf24_rxLen = 32;
        nrf24.recv(nrf24_rxRawData, &nrf24_rxLen);
        lbCom.send(nrf24_rxRawData[0], LOST_ID, nrf24_rxRawData[1], nrf24_rxLen-2, &nrf24_rxRawData[2]);
      }
    }
  }
}

