#include <Fifo_U08.h>
#include <Fifo_U16.h>
#include <LbCom.h>
#include <HomeEasy.h>
#include <GPRS_Shield_Arduino.h>
#include <RF24.h>
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
RF24 nrf24(7,8);
GPRS gprs(&Serial3, 19200);

void setup() {
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

  homeEasy.init();
  lbCom.init();
  nrf24.begin();
  nrf24.setPALevel(RF24_PA_LOW);
  nrf24.setAddressWidth(4);
  uint32_t nrf24Adr = ID_LOST;
  nrf24.openReadingPipe(1, &nrf24Adr);
  nrf24.startListening();

  gprs.init();
  
  Serial.println("Init OK");
}

void loop() {
  homeEasy.run();
  if(true == homeEasy.rxCodeIsReady()) {
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
  if(true == lbCom.rxIsReady()) {
    if(ID_HOME_EASY == lbCom.rxGetDst()) {
      if(ID_HOME_EASY_SEND_TC == lbCom.rxGetCmd()) {
        if(4 == lbCom.rxGetDataLen()) {
          if(true == homeEasy.txIsReady()) {
            homeEasy.send(*((uint32_t *)lbCom.rxGetData()));
          }
        }
      }
      if(ID_GSM_SMS_SEND_TC == lbCom.rxGetCmd()) {
        lbCom.rxGetData()[10] = 0;
        lbCom.rxGetData()[lbCom.rxGetDataLen()] = 0;
        gprs.sendSMS(&(lbCom.rxGetData()[0]), &(lbCom.rxGetData()[11]));
      }
    }
    else {
      uint32_t nrf24Adr = lbCom.rxGetDst();
      nrf24.openWritingPipe(&nrf24Adr);
      nrf24.write(lbCom.rxGetFrame(), lbCom.rxGetFrameLen());
    }
    lbCom.rxRelease();
  }

  if(true == nrf24.available()) {
    uint8_t lbComFrame[LBCOM_FRAME_MAX_SIZE] = {0};
    nrf24.read(&lbComFrame[0], 4);
    nrf24.read(&lbComFrame[4], lbComFrame[3]+1);
  }
}

