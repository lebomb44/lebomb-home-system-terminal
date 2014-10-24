#include <Arduino.h> 

#include "LB_NRF24.h"

LB_NRF24::LB_NRF24()
{
  this->init();
}

void LB_NRF24::init(void)
{
}

void LB_NRF24::run(void)
{
}

bool LB_NRF24::rxIsReady(void)
{

}

uint8_t LB_NRF24::rxGetSrc(void)
{
  return this->rawData[0];
}

uint8_t LB_NRF24::rxGetDst(void)
{
  return this->rawData[1];
}

uint8_t LB_NRF24::rxGetCmd(void)
{
  return this->rawData[2];
}

uint8_t LB_NRF24::rxGetLen(void)
{
  return this->rawData[3];
}

uint8_t * LB_NRF24::rxGetData(void)
{
  return &(this->rawData[4]);
}

void LB_NRF24::rxRelease(void)
{
}

bool LB_NRF24::txIsReady(void)
{

}

void LB_NRF24::send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
/*
  Serial.write(0xAA);
  Serial.write(src); Serial.write(dst); Serial.write(cmd); Serial.write(len);
  Serial.write(data, len);
*/
}

