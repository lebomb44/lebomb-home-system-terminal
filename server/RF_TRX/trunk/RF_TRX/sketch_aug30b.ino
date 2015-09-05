#include <Fifo_U16.h>
#include <HomeEasy.h>

#define LED_pin 13

#define RF_IN_pin 2
#define RF_OUT_pin 9
#define RF_TXRX_MODE_pin 5
#define RF_ENABLE_pin 4

HomeEasy homeEasy;

void setup()
{
  //pinMode(RF_IN_pin, INPUT);
  //pinMode(RF_OUT_pin, OUTPUT);
  pinMode(RF_TXRX_MODE_pin, OUTPUT);
  digitalWrite(RF_TXRX_MODE_pin, LOW);
  pinMode(RF_ENABLE_pin, OUTPUT);
  digitalWrite(RF_ENABLE_pin, HIGH);
}

void loop()
{
  homeEasy.run();
  if(true == homeEasy.rxCodeIsReady())
  {
    Serial.print(homeEasy.rxGetCode(), HEX);Serial.print(" : ");
    Serial.print(homeEasy.rxGetManufacturer(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetGroup(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetDevice(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetStatus(), HEX);Serial.println();
    /* Check the authorized codes */
    if(((0xFCE1CE == homeEasy.rxGetManufacturer()) && (0x0 == homeEasy.rxGetGroup()) && (0x2 == homeEasy.rxGetDevice())) \
    || ((0xFCBDD6 == homeEasy.rxGetManufacturer()) && (0x0 == homeEasy.rxGetGroup()) && (0x2 == homeEasy.rxGetDevice()))) {
      delay(1);
    }
    homeEasy.rxRelease();
  }
}


