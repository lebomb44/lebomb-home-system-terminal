#include <inttypes.h>
#include <Arduino.h>

#include <ID/ID.h>
#include <IR/IR.h>
#include <RH_NRF24/NRF24.h>

#define RELAICAM 0
IR ir;
NRF24 nrf24;

int main(void)
{
  uint8_t nrf24_dstAddr[5] = {0};
  nrf24_dstAddr[0] = ROVER0_ID;
  nrf24_dstAddr[1] = 0;
  nrf24_dstAddr[2] = 0;
  nrf24_dstAddr[3] = 0;
  nrf24_dstAddr[4] = 0;
  uint8_t nrf24_txRawData[32] = {0};
  uint8_t nrf24_rxRawData[32] = {0};
  uint8_t nrf24_rxLen = 32;

  pinMode(RELAICAM, OUTPUT);
  digitalWrite(RELAICAM, LOW);

  ir.init();

  nrf24.init();
  nrf24.setChannel(1);
  nrf24.setThisAddress(nrf24_dstAddr, 5);
  nrf24.setPayloadSize(32);
  nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm);

  while(1)
  {
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
}

