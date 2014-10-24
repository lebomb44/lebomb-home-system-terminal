#include <Arduino.h> 

#include "LB_Com.h"

LB_Com::LB_Com()
{
  this->init();
}

void LB_Com::init(void)
{
  uint16_t i = 0;

  for(i=0; i<(4+LB_COM_DATA_MAX_SIZE+1); i++)
  {
    this->rawData[i] = 0;
  }
}

void LB_Com::push(uint8_t data)
{
}

bool LB_Com::packetIsReady(void)
{
}

uint8_t LB_Com::getSrc(void)
{
  return this->rawData[0];
}

uint8_t LB_Com::getDst(void)
{
  return this->rawData[1];
}

uint8_t LB_Com::getCmd(void)
{
  return this->rawData[2];
}

uint8_t LB_Com::getLen(void)
{
  return this->rawData[3];
}

uint8_t LB_Com::getRawLen(void)
{
  return (4 + (this->getLen()) + 1);
}

uint8_t * LB_Com::getData(void)
{
  return &(this->rawData[4]);
}

uint8_t * LB_Com::getRawData(void)
{
  return this->rawData;
}

void LB_Com::send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  Serial.write(0xAA);
  Serial.write(src); Serial.write(dst); Serial.write(cmd); Serial.write(len);
  Serial.write(data, len);
}

