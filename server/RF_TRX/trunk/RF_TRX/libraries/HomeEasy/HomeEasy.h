#ifndef HomeEasy_h
#define HomeEasy_h

#include <inttypes.h>

class HomeEasy
{
public:
  HomeEasy();
  void init(void);
  void push(uint16_t dataU16);
  bool codeIsReady(void);
  uint32_t getCode(void);
  uint8_t getDevice(void);
  bool getGroup(void);
  bool getStatus(void);
  uint32_t getManufacturer(void);
private:
   uint32_t code;
   bool codeBitStream[64];
   uint16_t step;
   bool isHigh(uint16_t timeU16);
   bool isLowShort(uint16_t timeU16);
   bool isLowLong(uint16_t timeU16);
   bool isLowSync(uint16_t timeU16);
};

#endif
