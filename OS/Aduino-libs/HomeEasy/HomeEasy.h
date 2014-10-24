#ifndef HomeEasy_h
#define HomeEasy_h

#include <inttypes.h>

#define HOME_EASY_UNKNOWN_CMD 0
#define HOME_EASY_DIG_CMD 1
#define HOME_EASY_ANA_CMD 2

class HomeEasy
{
public:
  HomeEasy();
  void init(void);
  void push(uint16_t dataU16);
  bool codeIsReady(void);
  uint32_t * getCode(void);
  uint8_t getDevice(void);
  bool getStatus(void);
  bool getGroup(void);
  uint32_t getManufacturer(void);
  void send(uint32_t code);
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
