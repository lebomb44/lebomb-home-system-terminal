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

void LB_Com::run(void)
{
  /* FIXME : Not implemented */
}

bool LB_Com::rxIsReady(void)
{
  /* FIXME : Not implemented */
}

uint8_t LB_Com::rxGetSrc(void)
{
  return this->rawData[0];
}

uint8_t LB_Com::rxGetDst(void)
{
  return this->rawData[1];
}

uint8_t LB_Com::rxGetCmd(void)
{
  return this->rawData[2];
}

uint8_t LB_Com::rxGetLen(void)
{
  return this->rawData[3];
}

uint8_t * LB_Com::rxGetData(void)
{
  return &(this->rawData[4]);
}

void LB_Com::rxRelease(void)
{
  /* FIXME : Not implemented */
}

bool LB_Com::txIsReady(void)
{
  /* FIXME : Not implemented */
}

void LB_Com::send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
/*
  Serial.write(0xAA);
  Serial.write(src); Serial.write(dst); Serial.write(cmd); Serial.write(len);
  Serial.write(data, len);
*/
}
