#include <Fifo_U08.h>
#include <Fifo_U16.h>
#include <Cmd.h>
#include <LbCom.h>
#include <LbMsg.h>
#include <HomeEasy.h>
#include <GPRS_Shield_Arduino.h>
#include <RF24.h>
#include <ID.h>

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
  if(2 == arg_cnt) {
    homeEasy.send(cmdStr2Num(args[1], 16));
    Serial.print("homeEasySend: "); Serial.println(args[1]);
  }
  else { Serial.println("ERROR homeEasySend incorrect arg !"); }
}

/* HomeEasy */
void homeEasyEnablePrint(int arg_cnt, char **args) { homeEasy.enablePrint(); Serial.println("HomeEasy print enabled"); }
void homeEasyDisablePrint(int arg_cnt, char **args) { homeEasy.disablePrint(); Serial.println("HomeEasy print disabled"); }
/* LbCom */
void lbComSend(int arg_cnt, char **args) {
}
void lbComEnablePrint(int arg_cnt, char **args) { lbCom.enablePrint(); Serial.println("LbCom print enabled"); }
void lbComDisablePrint(int arg_cnt, char **args) { lbCom.disablePrint(); Serial.println("LbCom print disabled"); }
/* NRF24 */
void nrf24Send(int arg_cnt, char **args) {
}
void nrf24EnablePrint(int arg_cnt, char **args) { nrf24_printIsEnabled = true; Serial.println("NRF24 print enabled"); }
void nrf24DisablePrint(int arg_cnt, char **args) { nrf24_printIsEnabled = false; Serial.println("NRF24 print disabled"); }
/* GPRS */
void gprsSendSMS(int arg_cnt, char **args) {
}
void gprsEnablePrint(int arg_cnt, char **args) { gprs_printIsEnabled = true; Serial.println("GPRS print enabled"); }
void gprsDisablePrint(int arg_cnt, char **args) { gprs_printIsEnabled = false; Serial.println("GPRS print disabled"); }

void setup() {
  Serial.begin(115200);
  Serial.println("RF_TRX Starting...");

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

  Serial.print("NRF24 begin...");
  if(true == nrf24.begin()) { Serial.println("OK"); } else { Serial.println("ERROR"); }
  nrf24.setPALevel(RF24_PA_LOW);
  Serial.println("NRF24 PA level set");
  //nrf24.setAddressWidth(4);
  Serial.println("NRF24 address width set");
  uint8_t nrf24AdrR[6] = "LOST+";
  nrf24.openReadingPipe(1, nrf24AdrR);
  Serial.println("NRF24 reading pipe opened");
  uint8_t nrf24AdrW[6] = "FRIDG";
  nrf24.openWritingPipe(nrf24AdrW);
  Serial.println("NRF24 writing pipe opened");
  nrf24.startListening();
  Serial.println("NRF24 listening started");
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
  cmdAdd("help", "List commands", cmdList);

  Serial.println("RF_TRX Init done");
  homeEasy.enablePrint();
}

void loop() {
  homeEasy.run();
  if(true == homeEasy.rxCodeIsReady()) {
    if(true == homeEasy.printIsEnabled()) {
      Serial.print(homeEasy.rxGetCode(), HEX);Serial.print(" : ");
      Serial.print(homeEasy.rxGetManufacturer(), HEX);Serial.print("-");
      Serial.print(homeEasy.rxGetGroup(), HEX);Serial.print("-");
      Serial.print(homeEasy.rxGetDevice(), HEX);Serial.print("-");
      Serial.print(homeEasy.rxGetStatus(), HEX);Serial.println();
    }
    LbMsg msg(7);
    msg.setSrc(ID_HOME_EASY);
    msg.setDst(ID_LOST);
    *((uint32_t *) &(msg.getData()[0])) = homeEasy.rxGetManufacturer();
    msg.getData()[4] = homeEasy.rxGetGroup();
    msg.getData()[5] = homeEasy.rxGetStatus();
    msg.getData()[6] = homeEasy.rxGetDevice();
    homeEasy.rxRelease();
    msg.compute();
    lbCom.send(msg);
  }

  lbCom.run();
  if(true == lbCom.rxMsgIsReady()) {
    LbMsg msg(0);
    lbCom.rxGetMsg(msg);
    if(true == msg.check()) {
      if(ID_HOME_EASY == msg.getDst()) {
        if(ID_HOME_EASY_SEND_TC == msg.getCmd()) {
          if(4 == msg.getDataLen()) {
            if(true == homeEasy.txIsReady()) {
              homeEasy.send(*((uint32_t *)msg.getData()));
            }
          }
        }
        if(ID_GSM_SMS_SEND_TC == msg.getCmd()) {
          if(11 < msg.getDataLen()) {
            msg.getData()[10] = 0;
            msg.getData()[msg.getDataLen()-1] = 0;
            gprs.sendSMS(&(msg.getData()[0]), &(msg.getData()[11]));
          }
        }
      }
      else {
        uint32_t nrf24Adr = msg.getDst();
        nrf24.openWritingPipe(&nrf24Adr);
        nrf24.write(msg.getFrame(), msg.getFrameLen());
      }
    }
  }

  if(true == nrf24.available()) {
    LbMsg msg(32-4-1); /* 32 bytes max in NRF24 static payload */
    nrf24.read(msg.getFrame(), 32);
    if(true == nrf24_printIsEnabled) { Serial.print("NRF24 rx: "); msg.print(); }
    if(true == msg.check()) {
      if(true == nrf24_printIsEnabled) { Serial.println(": OK"); }
      //lbCom.send(msg);
    }
    else {
      if(true == nrf24_printIsEnabled) { Serial.println(": Bad CRC !"); }
    }
  }

  cmdPoll();
}

