#include <Fifo_U08.h>
#include <Fifo_U16.h>
#include <HomeEasy.h>
#include <LB_Com.h>
#include <ID.h>

#define LED_pin 13

#define RF_IN_pin 2
#define RF_OUT_pin 9
#define RF_TXRX_MODE_pin 5
#define RF_ENABLE_pin 4

#define PHONE_TX_pin 3
#define PHONE_RX_pin 8
#define PHONE_POWER_pin A1

#define LOST_TX_pin A0
#define LOST_RX_pin 10

HomeEasy homeEasy;
LB_Com lbCom;

void setup()
{
  homeEasy.init();
  Serial.begin(115200);
  pinMode(LED_pin, OUTPUT); 

  pinMode(PHONE_TX_pin, OUTPUT);
  digitalWrite(PHONE_TX_pin, HIGH);
  pinMode(PHONE_RX_pin, INPUT_PULLUP);
  pinMode(PHONE_POWER_pin, OUTPUT);
  digitalWrite(PHONE_POWER_pin, LOW);

  pinMode(LOST_TX_pin, OUTPUT);
  digitalWrite(LOST_TX_pin, HIGH);
  pinMode(LOST_RX_pin, INPUT_PULLUP);

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
    *((uint32_t *) &buff[0]) = homeEasy.rxGetManufacturer();
    buff[4] = homeEasy.rxGetGroup();
    buff[5] = homeEasy.rxGetStatus();
    buff[6] = homeEasy.rxGetDevice();

    lbCom.send(id.homeEasy, id.lost, x, homeEasy.async_cmd, buff);
    homeEasy.rxRelease();
  }

}

