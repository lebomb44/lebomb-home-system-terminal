#include <inttypes.h>
#include <Arduino.h>

#include <ID/ID.h>
#include <Servo/Servo.h>
#include <RH_NRF24/NRF24.h>

#define RELAICAM_ON 0
#define RELAICAM_OFF 1
#define RELAICAM_STATUS 2
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

  pinMode(RELAICAM_ON, OUTPUT);
  digitalWrite(RELAICAM_ON, LOW);
  pinMode(RELAICAM_OFF, OUTPUT);
  digitalWrite(RELAICAM_OFF, LOW);
  pinMode(RELAICAM_STATUS, INPUT);
  servoL.attach(2);
  servoR.attach(3);
  servoCamLR.attach(4);
  servoCamUD.attach(5);
  servoCharge.attach(6);

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
        digitalWrite(RELAICAM_ON, LOW); digitalWrite(RELAICAM_OFF, LOW);
        nrf24_dstAddr[0] = nrf24_rxRawData[0];
        nrf24.setTransmitAddress(nrf24_dstAddr, 5);
        nrf24_txRawData[0] = ROVER0_ID;
        nrf24_txRawData[1] = ROVER_CMD_TM;
        nrf24_txRawData[2] = digitalRead(RELAICAM_STATUS);
        nrf24_txRawData[3] = servoL.read();
        nrf24_txRawData[4] = servoR.read();
        nrf24_txRawData[5] = servoCamLR.read();
        nrf24_txRawData[6] = servoCamUD.read();
        nrf24_txRawData[7] = servoCharge.read();
        nrf24.send(nrf24_txRawData , 8);
      }
      if(ROVER_CMD_CAM_POWER == nrf24_rxRawData[1])
      {
        digitalWrite(RELAICAM_ON, LOW);
        digitalWrite(RELAICAM_OFF, LOW);
        if(nrf24_rxRawData[2]) { digitalWrite(RELAICAM_ON, HIGH); digitalWrite(RELAICAM_OFF, LOW); }
        else { digitalWrite(RELAICAM_ON, LOW); digitalWrite(RELAICAM_OFF, HIGH); }
      }
      if(ROVER_CMD_CAM_LR == nrf24_rxRawData[1]) { servoCamLR.write(nrf24_rxRawData[2]); }
      if(ROVER_CMD_CAM_UD == nrf24_rxRawData[1]) { servoCamUD.write(nrf24_rxRawData[2]); }
      if(ROVER_CMD_CHARGE == nrf24_rxRawData[1]) { servoCharge.write(nrf24_rxRawData[2]); }
      if(ROVER_CMD_FWD == nrf24_rxRawData[1]) { servoL.write(0); servoR.write(0); }
      if(ROVER_CMD_TURN == nrf24_rxRawData[1]) { servoL.write(360); servoR.write(360); }
      if(ROVER_CMD_STOP == nrf24_rxRawData[1]) { servoL.write(180); servoR.write(180); }
    }
  }
}

