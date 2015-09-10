#ifndef FBus_h
#define FBus_h

#include <inttypes.h>
#include <SoftwareSerial.h>

class FBus
{
public:
  FBus(const uint8_t rxPin_, const uint8_t txPin_);
  void init(void);
  void sync(void);
  uint8_t header(uint8_t *frame, uint8_t cmd, uint16_t data_len);
  uint16_t frame_len(uint16_t data_len);
  uint8_t trailer(uint8_t * frame, uint8_t seq);
  uint8_t send(uint8_t cmd, uint16_t data_len, uint8_t *data, uint8_t seq);
  uint8_t receive(uint8_t *cmd, uint16_t *data_len, uint8_t **data, uint8_t *seq);
  uint8_t receive_ack(uint8_t _cmd);
private:
  SoftwareSerial _serial;
};

#endif
