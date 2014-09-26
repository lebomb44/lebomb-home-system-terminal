#include <Arduino.h> 

#include "LB_Com.h"

LB_Com::LB_Com()
{
  this->init();
}

void LB_Com::init(void)
{
  uint16_t i = 0;

  this->src = 0;
  this->dst = 0;
  this->len = 0;
  for(i=0; i<LB_COM_DATA_MAX_SIZE; i++)
  {
    this->data[i] = 0;
  }
}

void LB_Com::push(uint8_t data)
{
}

bool LB_Com::packetIsReady(void)
{
}

bool LB_Com::getSrc(void)
{
  return this->src;
}

bool LB_Com::getDst(void)
{
  return this->dst;
}

bool LB_Com::getLen(void)
{
  return this->len;
}

bool LB_Com::getRawLen(void)
{
  return this->len;
}

uint8_t * LB_Com::getData(void)
{
  return &(this->rawData[3]);
}

uint8_t * LB_Com::getRawData(void)
{
  return this->rawData;
}
