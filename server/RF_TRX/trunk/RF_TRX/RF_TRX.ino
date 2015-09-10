#include <Fifo_U16.h>
#include <HomeEasy.h>
#include <SoftwareSerial.h>
#include <FBus.h>

#define LED_pin 13

#define RF_IN_pin 2
#define RF_OUT_pin 9
#define RF_TXRX_MODE_pin 5
#define RF_ENABLE_pin 4

#define PHONE_TX_pin 3
#define PHONE_RX_pin 8
#define PHONE_POWER_pin 10

HomeEasy homeEasy;
FBus fbus(PHONE_RX_pin, PHONE_TX_pin);

void setup()
{
  homeEasy.init();
  Serial.begin(115200);
  pinMode(LED_pin, OUTPUT); 
  /*
  pinMode(PHONE_TX_pin, INPUT);
  pinMode(PHONE_RX_pin, INPUT);
  pinMode(PHONE_POWER_pin, OUTPUT);
  digitalWrite(PHONE_POWER_pin, LOW);
  */
  pinMode(RF_IN_pin, INPUT);
  pinMode(RF_OUT_pin, OUTPUT);
  digitalWrite(RF_OUT_pin, LOW);
  pinMode(RF_TXRX_MODE_pin, OUTPUT);
  digitalWrite(RF_TXRX_MODE_pin, LOW);
  pinMode(RF_ENABLE_pin, OUTPUT);
  digitalWrite(RF_ENABLE_pin, HIGH);

  Serial.println("Init OK");
}

void loop()
{
  homeEasy.run();
//Serial.println(homeEasy.getU16(), DEC);
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
      if(0 == homeEasy.rxGetStatus()) {
      }
      if(1 == homeEasy.rxGetStatus()) {
      }
    }
    homeEasy.rxRelease();
  }
}

