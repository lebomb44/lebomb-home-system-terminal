#ifndef LB_Com_h
#define LB_Com_h

#include <inttypes.h>

#define LB_COM_DATA_MAX_SIZE (4+255+1)

class LB_Com
{
public:
  LB_Com();
  void init(void);
  void push(uint8_t data);
  bool packetIsReady(void);
  uint8_t getSrc(void);
  uint8_t getDst(void);
  uint8_t getCmd(void);
  uint8_t getLen(void);
  uint8_t getRawLen(void);
  uint8_t * getData(void);
  uint8_t * getRawData(void);
  void send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);
private:
   uint8_t rawData[LB_COM_DATA_MAX_SIZE];
};

#endif
