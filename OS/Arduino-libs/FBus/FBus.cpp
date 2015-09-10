#include <Arduino.h> 

#include "FBus.h"

#define NOKIA_3310_HWSWV   0xD1
#define NOKIA_3310_NETW    0x0A
#define NOKIA_3310_SMSSEND 0x02
#define NOKIA_3310_ACK     0x7F

FBus::FBus(const uint8_t rxPin_, const uint8_t txPin_) : _serial(rxPin_, txPin_)
{
  this->init();
}

void FBus::init(void)
{
  _serial.begin(115200);
  _serial.setTimeout(1000);
}

void FBus::sync(void)
{
  uint8_t i = 0;
  char sync_w = 0x55;

  for(i=0; i<128; i++) { _serial.write(sync_w); } _serial.flush();
}

uint8_t FBus::header(uint8_t *frame, uint8_t cmd, uint16_t data_len)
{
  /* Check the frame pointer */
  if(NULL == frame) { return 1; }
  /* Cable link */
  frame[0] = 0x1E;
  /* Destination device (cell phone) */
  frame[1] = 0x00;
  /* Source device (PC) */
  frame[2] = 0x0C;
  /* Command */
  frame[3] = cmd;
  /* Length (16 bits) = data length + sequence number */
  frame[4] = (data_len+1) / 256;
  frame[5] = (data_len+1) % 256;
  return 0;
}

uint16_t FBus::frame_len(uint16_t data_len)
{
  /* Header + data length + sequence number + 1 if length is odd + checksum */
  return (6 + data_len + 1 + ((data_len+1)%2) + 2);
}

uint8_t FBus::trailer(uint8_t * frame, uint8_t seq)
{
  uint16_t i = 0;
  uint16_t pos = 0;

  /* Check the frame pointer */
  if(NULL == frame) { return 1; }
  /* Get the length from the frame */
  pos = frame[4]; pos = pos << 8; pos += frame[5];
  /* Add header */
  pos = 5 + pos;
  /* Set the sequence number */
  frame[pos] = seq; pos++;
  /* Set the padding byte if necessary */
  if((pos%2)==1) { frame[pos]=0; pos++; }
  /* Compute the checksum on even data number */
  frame[pos] = 0; for(i=0; i<pos; i=i+2) { frame[pos] = frame[pos]^frame[i]; } pos++;
  /* Compute the checksum on odd data number */
  frame[pos] = 0; for(i=1; i<pos; i=i+2) { frame[pos] = frame[pos]^frame[i]; }

  return 0;
}

uint8_t FBus::send(uint8_t cmd, uint16_t data_len, uint8_t *data, uint8_t seq)
{
  uint8_t *frame = NULL;

  /* Check the data pointer to send */
  if(NULL == data) { return 1; }
  /* Allocate the frame buffer */
  frame = (uint8_t *) malloc(frame_len(data_len));
  /* Check the frame pointer */
  if(NULL == frame) { return 2; }
  /* Build the frame header */
  header(frame, cmd, data_len);
  /* Copy the data in the frame buffer */
  memcpy(&frame[6], data, data_len);
  /* Build the frame trailer */
  trailer(frame, seq);
  /* Send the frame to the cell phone */
  _serial.write(frame, frame_len(data_len)); _serial.flush();
  /* Free the frame buffer */
  free(frame);

  return 0;
}

uint8_t FBus::receive(uint8_t *cmd, uint16_t *data_len, uint8_t **data, uint8_t *seq)
{
  uint16_t buff_len = 0;
  uint16_t i = 0;
  uint8_t xor1 = 0;
  uint8_t xor2 = 0;
  int ret = 0;

  if(0x1E != _serial.read()) { /*printf("ERROR header0\n");*/ return 1; }
  if(0x0C != _serial.read()) { /*printf("ERROR header1\n");*/ return 2; }
  if(0x00 != _serial.read()) { /*printf("ERROR header2\n");*/ return 3; }

  ret = _serial.read(); if(0>ret) { /*printf("ERROR data lenH\n");*/ return 4; }
  *cmd = ret;

  ret = _serial.read(); if(0>ret) { /*printf("ERROR data lenH\n");*/ return 5; }
  *data_len = (((ret)&0x00FF)<<8);
  ret = _serial.read(); if(0>ret) { /*printf("ERROR data lenL\n");*/ return 6; }
  *data_len = *data_len + ret;
  if(1>*data_len) { /*printf("ERROR data len\n");*/ return 7; }
  *data_len = (*data_len) - 1;

  buff_len = (*data_len) + ((*data_len)+1)%2 + 1 + 2;
  *data = (uint8_t *) malloc(buff_len);
  if(NULL == *data) { /*printf("ERROR malloc\n");*/ return 8; }

  for(i=0; i<buff_len; i++)
  {
    ret = _serial.read();
    if(0>ret) { /*printf("ERROR data\n");*/ free(*data); *data=NULL; return 9; }
    else { (*data)[i] = ret; }
  }

  *seq = (*data)[*data_len];

  /* Compute the checksum on even data number */
  xor1 = 0x1E^0x00^((((*data_len)+1)>>8)&0x00FF); for(i=0; i<(buff_len-2); i=i+2) { xor1 = xor1^(*data)[i]; }
  if(xor1 != (*data)[buff_len-2]) { /*printf("ERROR xor1\n");*/ free(*data); *data=NULL; return 10; }
  /* Compute the checksum on odd data number */
  xor2 = 0x0C^(*cmd)^(((*data_len)+1)&0x00FF); for(i=1; i<(buff_len-2); i=i+2) { xor2 = xor2^(*data)[i]; }
  if(xor2 != (*data)[buff_len-1]) { /*printf("ERROR xor2\n");*/ free(*data); *data=NULL; return 11; }

  return 0;
}

uint8_t FBus::receive_ack(uint8_t _cmd)
{
  uint8_t cmd = 0;
  uint16_t data_len = 0;
  uint8_t *data = NULL;
  uint8_t seq = 0;

  if(0 != receive(&cmd, &data_len, &data, &seq)) { /*printf("ERROR receive\n");*/ return 1; }
  if(NOKIA_3310_ACK != cmd) { free(data); /*printf("ERROR ack\n");*/ return 2; }
  if(1 != data_len) { free(data); /*printf("ERROR ack len\n");*/ return 3; }
  if(data[0] != _cmd) { free(data); /*printf("ERROR ack cmd\n");*/ return 4; }
//if(seq != 0x00) { free(data); /*printf("ERROR ack seq\n");*/ return 5; }
  free(data);
  return 0;
}

