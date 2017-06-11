#include <Fifo_U08.h>
#include <Fifo_U16.h>
#include <LbCom.h>
#include <HomeEasy.h>
#include <GPRS_Shield_Arduino.h>
#include <RF24.h>
#include <RH_NRF24/NRF24.h>
#include <ID.h>

#define LED_pin 13

#define LOST_TX_pin 16
#define LOST_RX_pin 17

#define HOME_EASY_IN_pin 2

#define GSM_TX_pin    14
#define GSM_RX_pin    15
#define GSM_POWER_pin 9

#define NRF24_CE_pin   11
#define NRF24_CSN_pin  10
#define NRF24_MOSI_pin 51
#define NRF24_MISO_pin 50
#define NRF24_SCK_pin  52

HomeEasy homeEasy;
LbCom lbCom;
NRF24 nrf24(7, SS); // B5(SCK), B4(MISO), B3(MOSI), B2(SS), D7(CE)

void setup()
{
  homeEasy.init();
  lbCom.init();

  nrf24.init();
  nrf24.setChannel(1);
  nrf24.setThisAddress(nrf24_dstAddr, 5);
  nrf24.setPayloadSize(32);
  nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm);


  Serial.begin(115200);
  pinMode(LED_pin, OUTPUT); 

  pinMode(LOST_TX_pin, OUTPUT);
  digitalWrite(LOST_TX_pin, HIGH);
  pinMode(LOST_RX_pin, INPUT_PULLUP);

  pinMode(HOME_EASY_IN_pin, INPUT);

  pinMode(GSM_TX_pin, OUTPUT);
  digitalWrite(GSM_TX_pin, HIGH);
  pinMode(GSM_RX_pin, INPUT_PULLUP);
  pinMode(GSM_POWER_pin, OUTPUT);
  digitalWrite(GSM_POWER_pin, LOW);

  pinMode(NRF24_CE_pin, OUTPUT);
  digitalWrite(NRF24_CE_pin, HIGH);
  pinMode(NRF24_CSN_pin, OUTPUT);
  digitalWrite(NRF24_CSN_pin, HIGH);
  pinMode(NRF24_MOSI_pin, OUTPUT);
  digitalWrite(NRF24_MOSI_pin, HIGH);
  pinMode(NRF24_MISO_pin, INPUT_PULLUP);
  pinMode(NRF24_SCK_pin, OUTPUT);
  digitalWrite(NRF24_SCK_pin, HIGH);

  Serial.println("Init OK");
}

void loop()
{
  homeEasy.run();
//Serial.println(homeEasy.getU16(), DEC);

  if(true == homeEasy.rxCodeIsReady())
  {
    uint8_t buff[7] = {0};
    Serial.print(homeEasy.rxGetCode(), HEX);Serial.print(" : ");
    Serial.print(homeEasy.rxGetManufacturer(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetGroup(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetDevice(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetStatus(), HEX);Serial.println();
    *((uint32_t *) &buff[0]) = homeEasy.rxGetManufacturer();
    buff[4] = homeEasy.rxGetGroup();
    buff[5] = homeEasy.rxGetStatus();
    buff[6] = homeEasy.rxGetDevice();
    homeEasy.rxRelease();

    lbCom.send(ID_HOME_EASY, ID_LOST, ID_HOME_EASY_RCV_TM, 7, buff);
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

    if(true == nrf24.available())
    {
      nrf24_rxLen = 32;
      nrf24.recv(nrf24_rxRawData, &nrf24_rxLen);
      if(TV_RC_CMD_TM == nrf24_rxRawData[1])
      {
        nrf24_dstAddr[0] = nrf24_rxRawData[0];
        nrf24.setTransmitAddress(nrf24_dstAddr, 5);
        nrf24_txRawData[0] = TV_RC_ID;
        nrf24_txRawData[1] = TV_RC_CMD_TM;
  	    nrf24_txRawData[2] = digitalRead(RELAICAM);
        nrf24.send(nrf24_txRawData , 3);
      }
      if(TV_RC_CMD_CAM_POWER == nrf24_rxRawData[1]) { digitalWrite(RELAICAM, nrf24_rxRawData[2]); }
      if(TV_RC_CMD_IR_RAW_SAMSUNG == nrf24_rxRawData[1]) { ir.setSamsung(nrf24_rxRawData[2]); }
      if(TV_RC_CMD_IR_MACRO_SAMSUNG_GO_HDMI1 == nrf24_rxRawData[1]) { ir.setSamsung(0); ir.setSamsung(1); ir.setSamsung(2); }
      if(TV_RC_CMD_IR_MACRO_SAMSUNG_GO_TV == nrf24_rxRawData[1]) { ir.setSamsung(0); ir.setSamsung(1); ir.setSamsung(2); }
    }

}

