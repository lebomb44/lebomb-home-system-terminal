#include <inttypes.h>
#include <Fifo_U16.h>
#include <HomeEasy.h>
#include <LB_Com.h>

const int ledPin = 13;

Fifo_U16 lost_fifo;
Fifo_U16 rf_fifo;
HomeEasy homeEasy;

void setup() {
  lost_fifo.init();
  rf_fifo.init();
  homeEasy.init();
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  // initialize the pushbutton pin as an input
  Serial.begin(115200);
  TCNT1  = 0x0000;
  TCCR1A = 0x00;
  TCCR1C = 0x00;
  TCCR1B = 0x02;

  //EIMSK = 0x00;
  attachInterrupt(0, extInt0, CHANGE);
  //EICRA = 0x03;
  //EIMSK = 0x01;
}

void loop() {
  uint16_t dataU16 = 0;

  if(false == rf_fifo.isEmpty())
  {
    dataU16 = rf_fifo.pop();
    digitalWrite(ledPin, LOW);
    homeEasy.push(dataU16);
    if(homeEasy.codeIsReady())
    {
      Serial.println();
      Serial.println(homeEasy.getCode(), HEX);
      Serial.print(homeEasy.getDevice(), HEX);Serial.print("-");
      Serial.print(homeEasy.getGroup(), HEX);Serial.print("-");
      Serial.print(homeEasy.getStatus(), HEX);Serial.print("-");
      Serial.print(homeEasy.getManufacturer(), HEX);Serial.println();
      lbCom.send(HOME_EASY_ID, LOST_ID, HOME_EASY_CMD, 4, homeEasy.getCode());

      homeEasy.init();
    }
  }
  if(false == lost_fifo.isEmpty())
  {
    dataU16 = rf_fifo.pop();
    lbCom.push(dataU16);
    if(lbCom.packetIsReady())
    {
      if(HOME_EASY_ID == lbCom.getDst())
      {
        if(7 == lbCom.getLen()) { homeEasy.send(lbCom.getData()[0], lbCom.getData()[1], lbCom.getData()[2], &(lbCom.getData()[3])); }
      }
      else
      {
        nrf.send(lbCom.getDst(), lbCom.getRawData());
      }
      lbCom.init();
    }
  }
}

void extInt0(void) {
  word dataU16 = 0;

  dataU16 = TCNT1;
  TCNT1 = 0x0000;

  if((432 < dataU16) && (dataU16 < 5585))
  {
    digitalWrite(ledPin, HIGH);
    if(false == rf_fifo.isFull())
    {
      rf_fifo.push(dataU16);
    }
  }
}

