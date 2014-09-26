#include <Arduino.h> 

#include "HomeEasy.h"

HomeEasy::HomeEasy()
{
  this->init();
}

void HomeEasy::init(void)
{
  uint8_t i = 0;

  this->code = 0;
  for(i=0; i<64; i++) { this->codeBitStream[i] = false; }
  this->step = 0;
}

void HomeEasy::push(uint16_t dataU16)
{
  if((1 < this->step) && (this->step < 130))
  {
    if(0 == (this->step%2)) { if(this->isHigh(dataU16)) { this->step++; } else { /*Serial.print("BadHigh");Serial.print("-");Serial.println(dataU16);*/ this->step = 0; } }
    else
    {
      if(this->isLowShort(dataU16)) { this->codeBitStream[(this->step-3)/2] = false; this->step++; }
      else
      {
        if(this->isLowLong(dataU16)) { this->codeBitStream[(this->step-3)/2] = true; this->step++; }
        else { /*Serial.print(this->step);Serial.print("-");Serial.println(dataU16);*/ this->step = 0; }
      }
    }
  }
  if(1 == this->step) { if(this->isLowSync(dataU16)) { this->step++; } else { this->step = 0; } }
  if(0 == this->step) { if(this->isHigh(dataU16)) { this->step++; } }
}

bool HomeEasy::codeIsReady(void)
{
  uint8_t cBit = 0;

  if(129 < this->step)
  {
    for(cBit=0; cBit<32; cBit++)
    {
      /* Serial.print(chaconBitStream[2*cBit]); Serial.print(chaconBitStream[(2*cBit) + 1]); */
      if((false == this->codeBitStream[2*cBit]) && (true == this->codeBitStream[(2*cBit) + 1]))
      {
        bitClear(this->code, cBit);
      }
      else
      {
        if((true == this->codeBitStream[2*cBit]) && (false == this->codeBitStream[(2*cBit) + 1]))
        {
          bitSet(this->code, cBit);
        }
        else
        {
          /* Serial.print("Bad sequence-");Serial.print(cBit);Serial.print("=");Serial.print(chaconBitStream[2*cBit]);Serial.println(chaconBitStream[(2*cBit) +1]); */
          this->init();
		  return false;
        }
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

uint32_t HomeEasy::getCode(void)
{
  return this->code;
}

uint8_t HomeEasy::getDevice(void)
{
  return (0xF0000000 & this->code) >> 28;
}

bool HomeEasy::getGroup(void)
{
  return (0x08000000 & this->code) >> 27;
}

bool HomeEasy::getStatus(void)
{
  return (0x04000000 & this->code) >> 26;
}

uint32_t HomeEasy::getManufacturer(void)
{
  return (0x03FFFFFF & this->code);
}

bool HomeEasy::isHigh(uint16_t timeU16)
{
  if((495 < timeU16) && (timeU16 < 640)) { return true; }
  else { return false; }
}

bool HomeEasy::isLowShort(uint16_t timeU16)
{
  if((432 < timeU16) && (timeU16 < 650)) { return true; }
  else { return false; }
}

bool HomeEasy::isLowLong(uint16_t timeU16)
{
  if((2340 < timeU16) && (timeU16 < 2860)) { return true; }
  else { return false; }
}

bool HomeEasy::isLowSync(uint16_t timeU16)
{
  if((4815 < timeU16) && (timeU16 < 5585)) { return true; }
  else { return false; }
}
