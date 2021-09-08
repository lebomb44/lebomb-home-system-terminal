#include <Fifo_U08.h>
#include <Fifo_U16.h>
#include <histogram.h>
#include <Cmd.h>
#include <LbCom.h>
#include <LbMsg.h>
#include <HT12E.h>
#include <GPRS_Shield_Arduino.h>
#include <RF24.h>
#include <ID.h>

/* *****************************
 *  Pin allocation
 * *****************************
 */
#define LED_pin 13

#define LOST_TX_pin 16
#define LOST_RX_pin 17

#define HT12E_IN_pin 21
#define HT12E_ICP_pin 49

#define GSM_TX_pin    14
#define GSM_RX_pin    15
#define GSM_POWER_pin 9

#define NRF24_CE_pin   11
#define NRF24_CSN_pin  10
#define NRF24_MOSI_pin 51
#define NRF24_MISO_pin 50
#define NRF24_SCK_pin  52

#define ALARM_STATUS_pin A15
#define ALARM_STATUS_NB_MAX 200

/* *****************************
 *  Global variables
 * *****************************
 */
HT12E ht12e;
LbCom lbCom;
RF24 nrf24(NRF24_CE_pin, NRF24_CSN_pin);
GPRS gprs(&Serial3, 19200);
uint32_t gprs_checkPowerUp_task = 0;
uint32_t gprs_checkPowerUp_counter = 0;
uint8_t alarm_status_previous = ID_ALARM_OFF_TM;
uint8_t alarm_status_current = ID_ALARM_OFF_TM;
uint8_t alarm_status_nb = ALARM_STATUS_NB_MAX;

/* *****************************
 *  Debug Macros
 * *****************************
 */
bool ht12e_printIsEnabled = true;
bool lbMsg_printIsEnabled = true;
bool lbCom_printIsEnabled = true;
bool nrf24_printIsEnabled = true;
bool gprs_printIsEnabled  = true;
#define HT12E_PRINT(m) if(true == ht12e_printIsEnabled) { m }
#define LBMSG_PRINT(m) if(true == lbMsg_printIsEnabled) { m }
#define LBCOM_PRINT(m) if(true == lbCom_printIsEnabled) { m }
#define NRF24_PRINT(m) if(true == nrf24_printIsEnabled) { m }
#define GPRS_PRINT(m)  if(true == gprs_printIsEnabled) { m }

void(* resetArduino) (void) = 0;

/* *****************************
 *  Command lines funstions
 * *****************************
 */
/* HT12E */
void ht12eHistoDump(int arg_cnt, char **args) { ht12e.histoDump(); }
void ht12eSend(int arg_cnt, char **args) {
  /* > ht12eSend 1234 56 2 1*/
  if(5 == arg_cnt) {
    ht12e.send(cmdStr2Num(args[1], 16), cmdStr2Num(args[2], 16));
    Serial.print("ht12eSend: "); Serial.println(args[1]);
  }
  else { Serial.println("ERROR ht12eSend incorrect arg !"); }
}
void ht12eEnablePrint(int arg_cnt, char **args) { ht12e_printIsEnabled = true; Serial.println("HT12E print enabled"); }
void ht12eDisablePrint(int arg_cnt, char **args) { ht12e_printIsEnabled = false; Serial.println("HT12E print disabled"); }
/* LbCom */
void lbComEnablePrint(int arg_cnt, char **args) { lbCom_printIsEnabled = true; Serial.println("LbCom print enabled"); }
void lbComDisablePrint(int arg_cnt, char **args) { lbCom_printIsEnabled = false; Serial.println("LbCom print disabled"); }
/* NRF24 */
void nrf24EnablePrint(int arg_cnt, char **args) { nrf24_printIsEnabled = true; Serial.println("NRF24 print enabled"); }
void nrf24DisablePrint(int arg_cnt, char **args) { nrf24_printIsEnabled = false; Serial.println("NRF24 print disabled"); }
/* GPRS */
void gprsSendSMS(int arg_cnt, char **args) {
  /* > gprsSendSMS 0612345678 sms_text_to_send_without_space */
  if(3 == arg_cnt) {
    Serial.print("Sending SMS...");
    /* Send the SMS: phoneNumber, text */
    if(true == gprs.sendSMS(args[1], args[2])) { Serial.println("OK"); }
    else { Serial.println("ERROR"); }
  }
  else { Serial.println("Incorrect number of arguments"); }
}
void gprsGetSignalStrength(int arg_cnt, char **args) {
  Serial.print("GPRS signal strength...");
  int signalStrength = 0;
  /* Get signal strength: [0..100] % */
  if(true == gprs.getSignalStrength(&signalStrength)) { Serial.print("OK = "); Serial.print(signalStrength); Serial.println(); } else { Serial.println("ERROR"); }
}
void gprsPowerUpDown(int arg_cnt, char **args) { gprs.powerUpDown(GSM_POWER_pin); Serial.println("GPRS power Up-Down done"); }
void gprsCheckPowerUp(int arg_cnt, char **args) { Serial.print("GPRS check power up..."); if(true == gprs.checkPowerUp()) { Serial.println("OK"); } else { Serial.println("ERROR"); } }
void gprsInit(int arg_cnt, char **args) { Serial.print("GPRS init..."); if(true == gprs.init()) { Serial.println("OK"); } else { Serial.println("ERROR"); } }
void gprsEnablePrint(int arg_cnt, char **args) { gprs_printIsEnabled = true; Serial.println("GPRS print enabled"); }
void gprsDisablePrint(int arg_cnt, char **args) { gprs_printIsEnabled = false; Serial.println("GPRS print disabled"); }

void lbMsgSend(int arg_cnt, char **args) {
  /* > lbMsgSend SRC DST CMD D0 D1 D2 D3 */
  if(3 < arg_cnt) {
    /* Create the message according to the length derivated from the command line */
    LbMsg msg(arg_cnt - 4);
    /* Set the message with the information given in the command line */
    msg.setSrc(atoi(args[1])); msg.setDst(atoi(args[2])); msg.setCmd(atoi(args[3])); 
    /* Copy the date from the command line */
    for(int i=0; i<msg.getDataLen(); i++) { msg.getData()[i] = atoi(args[i+4]); }
    /* Compute the CRC */
    msg.compute();
    /* Send the message */
    sendLbMsg(msg);
  }
  else { Serial.println("ERROR: Too few arguments"); }
}
void sendLbMsg(LbMsg & msg) {
  /* Id destination is ID_LOST it should be sent en lbCom link */
  if((ID_LOST_MASTER == msg.getDst()) || (ID_LOST_SLAVE == msg.getDst())) {
    LBCOM_PRINT( Serial.print("->LBCOM send: "); msg.print(); )
    /* Send the message now */
    lbCom.send(msg);
    LBCOM_PRINT( Serial.println("done"); )
  }
  /* Otherwise we hope the destination is on NRF24 network */
  else {
    NRF24_PRINT( Serial.print("->NRF24 send: "); )
    /* Message maximum frame length ocer NRF24 is 32 */
    if(33 > msg.getFrameLen()) {
      /* We have to stop listening before sending */
      nrf24.stopListening();
      /* Send the message now */
      bool writeStatus = nrf24.write(msg.getFrame(), msg.getFrameLen());
      nrf24.startListening();
      NRF24_PRINT( msg.print(); if(true == writeStatus) { Serial.println("OK"); } else { Serial.println("ERROR"); } )
    }
    else {
      NRF24_PRINT( Serial.println("ERROR: message too long !"); )
    }
  }
}

void lbMsgExec(int arg_cnt, char **args) {
  /* > lbMsgExec interfaceName SRC DST CMD D0 D1 D2 D3 */
  if(4 < arg_cnt) {
    /* Create the message according to the length derivated from the command line */
    LbMsg msg(arg_cnt - 5);
    /* Set the message with the information given in the command line */
    msg.setSrc(atoi(args[2])); msg.setDst(atoi(args[3])); msg.setCmd(atoi(args[4]));
    /* Copy the date from the command line */
    for(int i=0; i<msg.getDataLen(); i++) { msg.getData()[i] = atoi(args[i+5]); }
    /* Compute the CRC */
    msg.compute();
    /* Execute the message now */
    execMsg(args[1], msg);
  }
  else { Serial.println("ERROR: Too few arguments"); }
}
/* Execute a message */
bool execMsg(String ife, LbMsg & msg) {
  LBMSG_PRINT( Serial.print(ife + " tc: "); msg.print(); )
  /* First check the message. It must be wel formed */
  if(true == msg.check()) {
    /* OK, it is well formed */
    LBMSG_PRINT( Serial.println(": OK"); )
    /* This message is for HT12E module */
    if(ID_HT12E_SLAVE == msg.getDst()) {
      if(ID_HT12E_SEND_TC == msg.getCmd()) {
        HT12E_PRINT( Serial.print("  " + ife + " tc: ID_HT12E_SEND_TC: "); )
        /* Data is the full HT12E frame */
        if(7 == msg.getDataLen()) {
          if(true == ht12e.txIsReady()) {
            /* This command is not implemented */
            uint16_t address = (0xFF00 & (((uint16_t)msg.getData()[0])<<8)) | (0x00FF & ((uint16_t)msg.getData()[1]));
            uint8_t data = msg.getData()[2];
            ht12e.send(address, data);
            HT12E_PRINT( Serial.println("OK"); )
          }
          else { HT12E_PRINT( Serial.println("ERROR: device busy"); ) }
        }
        else { HT12E_PRINT( Serial.println("ERROR: bad data length"); ) }
      }
      else {
        HT12E_PRINT( Serial.println("  " + ife + " tc: HT12E UNKNOWN TC"); )
      }
    }
    else {
      /* This message is for GPRS module */
      if(ID_GSM_SLAVE == msg.getDst()) {
        if(ID_GSM_INIT_TC == msg.getCmd()) {
          GPRS_PRINT( Serial.print("  " + ife + " tc: ID_GSM_INIT_TC: "); )
          /* No data for this command */
          if(0 == msg.getDataLen()) {
            GPRS_PRINT( Serial.println("OK"); )
            /* Build a TM to send back containing the status of the command execution */
            LbMsg tm(1); tm.setSrc(msg.getDst()); tm.setDst(msg.getSrc()); tm.setCmd(ID_GSM_INIT_TM);
            /* Set the data, compute the CRC and send the message */
            tm.getData()[0] = gprs.init(); tm.compute(); sendLbMsg(tm);
            GPRS_PRINT( Serial.print("    " + ife + " tm: ID_GSM_INIT_TM: "); Serial.println(tm.getData()[0]); )
          }
          else { GPRS_PRINT( Serial.println("ERROR: bad data length"); ) }
        }
        else if(ID_GSM_CHECKPOWERUP_TC == msg.getCmd()) {
          GPRS_PRINT( Serial.print("  " + ife + " tc: ID_GSM_CHECKPOWERUP_TC: "); )
          /* No data for this command */
          if(0 == msg.getDataLen()) {
            GPRS_PRINT( Serial.println("OK"); )
            /* Build a TM to send back containing the status of the command execution */
            LbMsg tm(1); tm.setSrc(msg.getDst()); tm.setDst(msg.getSrc()); tm.setCmd(ID_GSM_CHECKPOWERUP_TM);
            /* Set the data, compute the CRC and send the message */
            tm.getData()[0] = gprs.checkPowerUp(); tm.compute(); sendLbMsg(tm);
            GPRS_PRINT( Serial.print("    " + ife + " tm: ID_GSM_CHECKPOWERUP_TM: "); Serial.println(tm.getData()[0]); )
          }
          else { GPRS_PRINT( Serial.println("ERROR: bad data length"); ) }
        }
        else if(ID_GSM_POWERUPDOWN_TC == msg.getCmd()) {
          GPRS_PRINT( Serial.print("  " + ife + " tc: ID_GSM_POWERUPDOWN_TC: "); )
          /* No data for this command */
          if(0 == msg.getDataLen()) {
            GPRS_PRINT( Serial.println("OK"); )
            gprs.powerUpDown(GSM_POWER_pin);
            /* No returned status, so no TM to send */
          }
          else { GPRS_PRINT( Serial.println("ERROR: bad data length"); ) }
        }
        //else if(ID_GSM_POWERRESET_TC == msg.getCmd()) { gprs.powerReset(/* FIXME */); }
        else if(ID_GSM_GETSIGNALSTRENGTH_TC == msg.getCmd()) {
          GPRS_PRINT( Serial.print("  " + ife + " tc: ID_GSM_GETSIGNALSTRENGTH_TC: "); )
          /* No data for this command */
          if(0 == msg.getDataLen()) {
            GPRS_PRINT( Serial.println("OK"); )
            /* Build a TM to send back containing the status of the command execution and the signal strength */
            LbMsg tm(1 + sizeof(int)); tm.setSrc(msg.getDst()); tm.setDst(msg.getSrc()); tm.setCmd(ID_GSM_GETSIGNALSTRENGTH_TM);
            /* Set the data: status of the exectution and the signal strength */
            int signalStrengthValue = 0;
            tm.getData()[0] = gprs.getSignalStrength(&signalStrengthValue);
            tm.getData()[1] = 0x000000FF & (signalStrengthValue>>8);
            tm.getData()[2] = 0x000000FF & (signalStrengthValue);
            /* Compute the CRC and send the message */
            tm.compute(); sendLbMsg(tm);
            GPRS_PRINT( Serial.print("    " + ife + " tm: ID_GSM_GETSIGNALSTRENGTH_TM: "); Serial.print(tm.getData()[0]); Serial.print(", "); Serial.println(signalStrengthValue); )
          }
          else { GPRS_PRINT( Serial.println("ERROR: bad data length"); ) }
        }
        else if(ID_GSM_SENDSMS_TC == msg.getCmd()) {
          GPRS_PRINT( Serial.print("  " + ife + " tc: ID_GSM_SENDSMS_TC: "); )
          /* Data is phone number + '0' + text + '0' */
          if(13 < msg.getDataLen()) {
            GPRS_PRINT( Serial.println("OK"); )
            /* Force the end of line at the end of the phone number string */
            msg.getData()[12] = 0;
            /* Force the end of line at the end of the test string which is the latest data */
            msg.getData()[msg.getDataLen()-1] = 0;
            /* Build a TM to send back containing the status of the command execution */
            LbMsg tm(1); tm.setSrc(msg.getDst()); tm.setDst(msg.getSrc()); tm.setCmd(ID_GSM_SENDSMS_TM);
            char ph[] = "0689350159";
            tm.getData()[0] = gprs.sendSMS(ph /*&(msg.getData()[0]*/), &(msg.getData()[13]));
            /* Compute the CRC and send the message */
            tm.compute(); sendLbMsg(tm);
            GPRS_PRINT( Serial.print("    " + ife + " tm: ID_GSM_SENDSMS_TM: "); Serial.println(tm.getData()[0]); )
            
            Serial.print("CHECK PU: "); Serial.println(gprs.checkPowerUp());
            Serial.print("CHECK INIT: "); Serial.println(gprs.init());
          }
          else { GPRS_PRINT( Serial.println("ERROR: data length too short"); ) }
        }
        else {
          GPRS_PRINT( Serial.println("  " + ife + " tc: GPRS UNKNOWN TC"); )
        }
      }
      else {
        /* The message is neither for HT12E not for GPRS */
        /* So we try to route it */
        sendLbMsg(msg);
      }
    }
  }
  else {
    LBMSG_PRINT( Serial.println(": Bad CRC !"); )
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("RF_TRX Starting...");

/* ****************************
 *  Pin configuration
 * ****************************
 */
  pinMode(LED_pin, OUTPUT); 

  pinMode(LOST_TX_pin, OUTPUT);
  digitalWrite(LOST_TX_pin, HIGH);
  pinMode(LOST_RX_pin, INPUT_PULLUP);

  pinMode(HT12E_IN_pin, INPUT_PULLUP);
  pinMode(HT12E_ICP_pin, INPUT_PULLUP);

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

  pinMode(ALARM_STATUS_pin, INPUT_PULLUP);

/* ****************************
 *  Modules initialization
 * ****************************
 */
  ht12e.init();

  lbCom.init();

  Serial.print("NRF24 begin...");
  if(true == nrf24.begin()) { Serial.println("OK"); } else { Serial.println("ERROR"); }
  /* Set Power Amplifier (PA) level to one of four levels: */
  /* RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX */
  /* The power levels correspond to the following output levels respectively: */
  /* NRF24L01: -18dBm, -12dBm,-6dBM, and 0dBm */
  nrf24.setPALevel(RF24_PA_MAX);
  Serial.println("NRF24 PA level set");
  nrf24.setDataRate(RF24_250KBPS);
  Serial.println("NRF24 data rate set");
  nrf24.setRetries(15, 15);
  Serial.println("NRF24 retries set");
  //nrf24.setAddressWidth(4);
  Serial.println("NRF24 address width set");
  /* Open pipe for Slave to Master messages */
  uint8_t nrf24AdrR[6] = "LBS2M";
  nrf24.openReadingPipe(1, nrf24AdrR);
  Serial.println("NRF24 reading pipe opened");
  /* Open pipe for Master to Slave messages */
  uint8_t nrf24AdrW[6] = "LBM2S";
  nrf24.openWritingPipe(nrf24AdrW);
  Serial.println("NRF24 writing pipe opened");
  nrf24.startListening();
  Serial.println("NRF24 listening started");

  //gprs.powerUpDown(GSM_POWER_pin);
  gprs.init();

  alarm_status_previous = ID_ALARM_OFF_TM;
  alarm_status_current = ID_ALARM_OFF_TM;
  alarm_status_nb = ALARM_STATUS_NB_MAX;

  cmdInit();

  /* ***********************************
   *  Register commands for command line
   * ***********************************
   */
  cmdAdd("histoDump", "Dump histogram", ht12eHistoDump);
  cmdAdd("lbMsgExec", "Execute LB message", lbMsgExec);
  cmdAdd("lbMsgSend", "Send LB message", lbMsgSend);
  cmdAdd("ht12eSend", "Send HT12E HEX code", ht12eSend);
  cmdAdd("ht12eEnablePrint", "Enable print in HT12E lib", ht12eEnablePrint);
  cmdAdd("ht12eDisablePrint", "Disable print in HT12E lib", ht12eDisablePrint);
  cmdAdd("lbComEnablePrint", "Enable print in LbCom lib", lbComEnablePrint);
  cmdAdd("lbComDisbalePrint", "Disable print in LbCom lib", lbComDisablePrint);
  cmdAdd("nrf24EnablePrint", "Enable print in NRF24 lib", nrf24EnablePrint);
  cmdAdd("nrf24DisbalePrint", "Disable print in NRF24 lib", nrf24DisablePrint);
  cmdAdd("gprsSendSMS", "Send SMS", gprsSendSMS);
  cmdAdd("gprsGetSignal", "Get GPRS signal strength", gprsGetSignalStrength);
  cmdAdd("gprsPowerUpDown", "GPRS power up-down", gprsPowerUpDown);
  cmdAdd("gprsCheckPowerUp", "Check GPRS power up", gprsCheckPowerUp);
  cmdAdd("gprsInit", "Initialize GPRS", gprsInit);
  cmdAdd("gprsEnablePrint", "Enable print in GPRS lib", gprsEnablePrint);
  cmdAdd("gprsDisablePrint", "Disable print in GPRS lib", gprsDisablePrint);
  cmdAdd("help", "List commands", cmdList);
  
  Serial.println("RF_TRX Init done");
}

void loop() {
  /* ****************************
   *  HT12E loop
   * ****************************
   */
  ht12e.run();
  /* A full code as been received */
  if(true == ht12e.rxCodeIsReady()) {
    HT12E_PRINT(
      if(0x5956 == ht12e.rxGetAddress())
      {
        Serial.print(ht12e.rxGetCode(), HEX);Serial.print(" : ");
        Serial.print(ht12e.rxGetAddress(), HEX);Serial.print(" - ");
        Serial.print(ht12e.rxGetData(), HEX);Serial.println();
        //ht12e.histoDump();
      }
    )
    ht12e.purge();
    /* Prepare the message to send to the central */
    LbMsg msg(3);
    msg.setSrc(ID_HT12E_SLAVE);
    msg.setDst(ID_LOST_MASTER);
    msg.setCmd(ID_HT12E_RCV_TM);
    /* Set the data */
    uint16_t addr = ht12e.rxGetAddress();
    msg.getData()[0] = 0x00FF & (addr>>8);
    msg.getData()[1] = 0x00FF & (addr);
    msg.getData()[2] = ht12e.rxGetData();

    /* Release as soon as possible */
    ht12e.rxRelease();
    /* Finalize the message */
    msg.compute();
    /* and send it */
    if(0x5956 == addr) { sendLbMsg(msg); }
  }

  /* ****************************
   *  LbCom loop
   * ****************************
   */
  lbCom.run();
  /* Is there something received ? */
  if(true == lbCom.rxMsgIsReady()) {
    /* Construct the smallest message */
    LbMsg msg(0);
    /* The message will be set by LbCom */
    lbCom.rxGetMsg(msg);
    /* Now we can execute it */
    execMsg("LBCOM", msg);
  }

  /* ****************************
   *  NRF24 loop
   * ****************************
   */
  if(true == nrf24.available()) {
    /* Contruct the biggest message : 32 data maximum */
    LbMsg msg(32-4-1); /* 32 bytes max in NRF24 static payload */
    nrf24.read(msg.getFrame(), 32);
    /* Now we can execute it */
    execMsg("NRF24", msg);
  }

  /* ****************************
   *  Cyclic tasks
   * ****************************
   */
  gprs_checkPowerUp_task++;
  /* Check GPRS power every 10 seconds */
  if(10000 < gprs_checkPowerUp_task) {
    /* Initialiaze counter for the new cycle */
    gprs_checkPowerUp_task=0;
    /* Power Up cycle */
    gprs_checkPowerUp_counter++;
    /* Prepare the message to send to the central */
    LbMsg hktm(1 + sizeof(int)); hktm.setSrc(ID_GSM_SLAVE); hktm.setDst(ID_LOST_MASTER); hktm.setCmd(ID_GSM_GETSIGNALSTRENGTH_TM);
    hktm.getData()[0] = 0;
    /* Get the signal strength and set it in the message */
    /* SRC DST CMS LEN status signalStrength CRC */
    /* But also reset the power Up timeout */
    int signalStrengthValue = 0;
    if(true == gprs.getSignalStrength(&signalStrengthValue)) {
      if(0 < signalStrengthValue) {
        gprs_checkPowerUp_counter = 0; hktm.getData()[0] = 1;
      }
    }
    hktm.getData()[1] = 0x000000FF & (signalStrengthValue>>8);
    hktm.getData()[2] = 0x000000FF & (signalStrengthValue);
    /* Compute the CRC */
    hktm.compute();
    LBCOM_PRINT( Serial.print("hktm: ID_GSM_GETSIGNALSTRENGTH_TM ("); Serial.print(hktm.getData()[0]); Serial.print(", "); Serial.print(signalStrengthValue); )
    /* Send the message */
    LBCOM_PRINT( Serial.print(") : "); ) sendLbMsg(hktm);
    /* Timeout ! */
    /* We have to turn ON the GPRS shield after 6 attempts */
    if(6 < gprs_checkPowerUp_counter) {
      /* Initialiaze counter for the new cycle */
      gprs_checkPowerUp_counter = 0;
      GPRS_PRINT( Serial.print("Powering up GPRS..."); )
      /* Toggle the power og the GPRS shield */
      gprs.powerUpDown(GSM_POWER_pin);
      GPRS_PRINT( Serial.println("done"); )
      GPRS_PRINT( Serial.print("GPRS init..."); )
      /* Try to initialize thr shield */
      if(true == gprs.init()) { GPRS_PRINT( Serial.println("OK"); ) } else { GPRS_PRINT( Serial.println("ERROR"); ) }
    }
  }

  /* ****************************
   *  Alarm loop
   * ****************************
   */
  if(LOW == digitalRead(ALARM_STATUS_pin)) {
    if(0 < alarm_status_nb) { alarm_status_nb--; }
  }
  else {
    if(alarm_status_nb < ALARM_STATUS_NB_MAX) { alarm_status_nb++; }
  }
  if(alarm_status_nb < ALARM_STATUS_NB_MAX / 2) {
    alarm_status_current = ID_ALARM_ON_TM;
  }
  else {
    alarm_status_current = ID_ALARM_OFF_TM;
  }

  if(alarm_status_current != alarm_status_previous) {
    /* Prepare the message to send to the central */
    LbMsg hktm(0); hktm.setSrc(ID_ALARM_SLAVE); hktm.setDst(ID_LOST_MASTER); hktm.setCmd(alarm_status_current);
    /* Compute the CRC */
    hktm.compute();
    if(ID_ALARM_ON_TM == alarm_status_current) {
      LBCOM_PRINT( Serial.print("hktm: ID_ALARM_ON_TM"); )
    }
    if(ID_ALARM_OFF_TM == alarm_status_current) {
      LBCOM_PRINT( Serial.print("hktm: ID_ALARM_OFF_TM"); )
    }
    /* Send the message */
    sendLbMsg(hktm);
    alarm_status_previous = alarm_status_current;
  }

  /* Poll for new command line */
  cmdPoll();
  /* Wait a minimum for cyclic task */
  delay(1);

  /* Reset every day */
  if(86400000<millis()) {
    resetArduino();
  }
}
