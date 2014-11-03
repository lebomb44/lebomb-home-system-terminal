#ifndef HomeEasy_h
#define HomeEasy_h

#include <inttypes.h>
#include <Fifo_U16/Fifo_U16.h>

class HomeEasy
{
public:
  HomeEasy();
  void init(void);
  void run(void);
  bool rxCodeIsReady(void);
  uint32_t rxGetCode(void);
  uint8_t rxGetDevice(void);
  bool rxGetStatus(void);
  bool rxGetGroup(void);
  uint32_t rxGetManufacturer(void);
  void rxRelease(void);
  bool txIsReady(void);
  void send(uint32_t code);
private:
  Fifo_U16 rx_fifo;
  uint32_t code;
  bool codeBitStream[64];
  uint16_t step;
  bool isHigh(uint16_t timeU16);
  bool isLowShort(uint16_t timeU16);
  bool isLowLong(uint16_t timeU16);
  bool isLowSync(uint16_t timeU16);
};

#endif
