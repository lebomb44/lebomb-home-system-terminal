#include <stdlib.h>
#include <stdio.h>

#include <dev/twif.h>
#include <dev/irqreg.h>

#include <sys/event.h>
#include <sys/atom.h>
#include <sys/timer.h>
#include <sys/thread.h>
#include <sys/heap.h>

#include "i2c.h"

uint8_t i2c_init(void)
{
  uint32_t val = 0;

  cbi(DDRD,0);
  cbi(DDRD,1);
  sbi(PORTD,0);
  sbi(PORTD,1);

  TwInit(0);
  val = 2400;
  TwIOCtl(TWI_SETSPEED, &val);

  return 0;
}

uint8_t i2c_get(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  if(data==NULL) { return 6; }
  if(TwMasterTransact(sla, &addr, (uint16_t) 1, data, (uint16_t) nb, (uint32_t) 1000) != ((int) nb)) { return 7; }

  return TwSlaveError();
}

uint8_t i2c_set(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  uint16_t i = 0;
  uint8_t* buff=NULL;
  int ret = 0;

  if(data == NULL) { return 1; }
  buff = malloc(nb+1);
  if(buff == NULL) { return 2; }
  for(i=0; i<nb; i++) { buff[i+1] = data[i]; }
  buff[0] = addr;

  ret = TwMasterTransact(sla, buff, ((uint16_t)nb)+1, NULL, 0, 1000);
  free(buff);
  if(ret!=0) { return 3; }

  return 0;
}

uint8_t i2c_broadcast_set(uint8_t addr, uint8_t nb, uint8_t* data)
{
  return i2c_set(0, addr, nb, data);
}
