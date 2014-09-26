#include <inttypes.h>

#include <Fifo_U16.h>
#include <HomeEasy.h>
#include <LB_Com.h>

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define UNKNOWN_ID 0
#define LOST_ID 1
#define RF_UART_ID 2
#define HOME_EASY_ID 3

const int ledPin = 13;

Fifo_U16 lost_fifo;
Fifo_U16 rf_fifo;
HomeEasy homeEasy;
LB_Com lbCom;

void setup() {
  lost_fifo.init();
  rf_fifo.init();
  homeEasy.init();
  lbCom.init();
  /*
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();
  */
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
      Serial.print(*homeEasy.getCode(), HEX);Serial.print(" : ");
      Serial.print(homeEasy.getManufacturer(), HEX);Serial.print("-");
      Serial.print(homeEasy.getGroup(), HEX);Serial.print("-");
      Serial.print(homeEasy.getDevice(), HEX);Serial.print("-");
      Serial.print(homeEasy.getStatus(), HEX);Serial.println();
      
      //lbCom.send(HOME_EASY_ID, LOST_ID, HOME_EASY_DIG_CMD, 4, (uint8_t *) homeEasy.getCode());
      homeEasy.init();
    }
  }
  if(false == lost_fifo.isEmpty())
  {
    dataU16 = lost_fifo.pop();
    lbCom.push(dataU16);
    if(lbCom.packetIsReady())
    {
      if(HOME_EASY_ID == lbCom.getDst())
      {
        if(4 == lbCom.getLen()) { homeEasy.send(*((uint32_t *)lbCom.getData())); }
      }
      else if(RF_UART_ID == lbCom.getDst())
      {
        /* FIXME : Not implemented */
      }
      else
      {
        /*
        Mirf.setTADDR((byte *)"serv1");
        Mirf.send(lbCom.getRawData());
        while(Mirf.isSending()) {}
        */
      }
      lbCom.init();
    }
  }
  /*
  if(true == Mirf.dataReady())
  {
    Mirf.getData(lbCom.getRawData());
    lbCom.send(lbCom.getSrc(), lbCom.getDst(), lbCom.getCmd(), lbCom.getLen(), lbCom.getData());
  }
  */
}

void extInt0(void)
{
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

