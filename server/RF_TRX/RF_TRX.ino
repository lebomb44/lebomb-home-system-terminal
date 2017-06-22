#include <Fifo_U08.h>
#include <Fifo_U16.h>
#include <LbCom.h>
#include <HomeEasy.h>
#include <GPRS_Shield_Arduino.h>
#include <RF24.h>
#include <ID.h>
#include <Cmd.h>

#define LED_pin 13

#define LOST_TX_pin 16
#define LOST_RX_pin 17

#define HOME_EASY_IN_pin 21

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
RF24 nrf24(NRF24_CE_pin, NRF24_CSN_pin);
GPRS gprs(&Serial3, 19200);

bool nrf24_printIsEnabled = false;
bool gprs_printIsEnabled = false;

void homeEasySend(int arg_cnt, char **args) {
  if(1 == arg_cnt) {
    homeEasy.send(cmdStr2Num(args[0], 16));
    Serial.print("homeEasySend "); Serial.println(args[0]);
  }
  else { Serial.print("ERROR homeEasySend incorrect arg !"); }
}
void homeEasyEnablePrint(int arg_cnt, char **args) { homeEasy.enablePrint(); Serial.print("HomeEasy print enabled"); }
void homeEasyDisablePrint(int arg_cnt, char **args) { homeEasy.disablePrint(); Serial.print("HomeEasy print disabled"); }

void lbComSend(int arg_cnt, char **args) {
}
void lbComEnablePrint(int arg_cnt, char **args) { lbCom.enablePrint(); Serial.print("LbCom print enabled"); }
void lbComDisablePrint(int arg_cnt, char **args) { lbCom.disablePrint(); Serial.print("LbCom print disabled"); }

void nrf24Send(int arg_cnt, char **args) {
}
void nrf24EnablePrint(int arg_cnt, char **args) { nrf24_printIsEnabled = true; Serial.print("NRF24 print enabled"); }
void nrf24DisablePrint(int arg_cnt, char **args) { nrf24_printIsEnabled = false; Serial.print("NRF24 print disabled"); }

void gprsSendSMS(int arg_cnt, char **args) {
}
void gprsEnablePrint(int arg_cnt, char **args) { gprs_printIsEnabled = true; Serial.print("GPRS print enabled"); }
void gprsDisablePrint(int arg_cnt, char **args) { gprs_printIsEnabled = false; Serial.print("GPRS print disabled"); }

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

  cmdInit();
  cmdAdd("homeEasySend", "Send HomeEsay HEX code", homeEasySend);
  cmdAdd("homeEasyEnablePrint", "Enable print in HomeEasy lib", homeEasyEnablePrint);
  cmdAdd("homeEasyDisablePrint", "Disable print in HomeEasy lib", homeEasyDisablePrint);
  cmdAdd("lbComSend", "Send frame on lbCom port", lbComSend);
  cmdAdd("lbComEnablePrint", "Enable print in LbCom lib", lbComEnablePrint);
  cmdAdd("lbComDisbalePrint", "Disable print in LbCom lib", lbComDisablePrint);
  cmdAdd("nrf24Send", "Send frame on NRF24 link", nrf24Send);
  cmdAdd("nrf24EnablePrint", "Enable print in NRF24 lib", nrf24EnablePrint);
  cmdAdd("nrf24DisbalePrint", "Disable print in NRF24 lib", nrf24DisablePrint);
  cmdAdd("gprsSendSMS", "Send SMS", gprsSendSMS);
  cmdAdd("gprsEnablePrint", "Enable print in GPRS lib", gprsEnablePrint);
  cmdAdd("gprsDisablePrint", "Disable print in GPRS lib", gprsDisablePrint);
  
  Serial.println("Init OK");
}

void loop() {
  homeEasy.run();
  if(true == homeEasy.rxCodeIsReady()) {
    uint8_t buff[7] = {0};
    if(true==homeEasy.printIsEnabled()) {
      Serial.print(homeEasy.rxGetCode(), HEX);Serial.print(" : ");
      Serial.print(homeEasy.rxGetManufacturer(), HEX);Serial.print("-");
      Serial.print(homeEasy.rxGetGroup(), HEX);Serial.print("-");
      Serial.print(homeEasy.rxGetDevice(), HEX);Serial.print("-");
      Serial.print(homeEasy.rxGetStatus(), HEX);Serial.println();
    }
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
    lbCom.send(lbComFrame[0], lbComFrame[1], lbComFrame[2], lbComFrame[3], &lbComFrame[4]);
  }

  cmdPoll();
}

