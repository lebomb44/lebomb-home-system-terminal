#include <inttypes.h>
#include <Arduino.h>

#include <ID/ID.h>
#include <Servo.h>
#include <RH_NRF24/NRF24.h>

Relai relaiCam;
Servo servoL;
Servo servoR;
Servo servoCamLR;
Servo servoCamUD;
Servo servoCharge;
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

  relaiCam.init();
  servoL.init();
  servoR.init();
  servoCamLR.init();
  servoCamUD.init();
  servoCharge.init();

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
      if(ROVER_CMD_TM == nrf24_rxRawData[1])
      {
          nrf24_dstAddr[0] = nrf24_rxRawData[0];
          nrf24.setTransmitAddress(nrf24_dstAddr, 5);
          nrf24_txRawData[0] = ROVER0_ID;
          nrf24_txRawData[1] = ROVER_CMD_TM;
    	  nrf24_txRawData[2] = servoL.getAngle();
    	  nrf24_txRawData[3] = servoR.getAngle();
    	  nrf24_txRawData[4] = relaiCam.getState();
    	  nrf24_txRawData[5] = relaiCamLR.getState();
    	  nrf24_txRawData[6] = relaiCamUD.getState();
    	  nrf24_txRawData[7] = servoCharge.getAngle();
          nrf24.send(nrf24_txRawData , 8);
      }
      if(ROVER_CMD_CAM_POWER == nrf24_rxRawData[1]) { relaiCam.setState(nrf24_rxRawData[2]); }
      if(ROVER_CMD_CAM_LR == nrf24_rxRawData[1]) { servoCamLR.set(nrf24_rxRawData[2]); }
      if(ROVER_CMD_CAM_UD == nrf24_rxRawData[1]) { servoCamUD.set(nrf24_rxRawData[2]); }
      if(ROVER_CMD_CHARGE == nrf24_rxRawData[1]) { servoCharge.set(nrf24_rxRawData[2]); }
      if(ROVER_CMD_FWD == nrf24_rxRawData[1]) { servoL.set(); servoR.set(); }
      if(ROVER_CMD_TURN == nrf24_rxRawData[1]) { servoL.set(); servoR.set(); }
      if(ROVER_CMD_STOP == nrf24_rxRawData[1]) { servoL.set(180); servoR.set(180); }
    }
  }
}

