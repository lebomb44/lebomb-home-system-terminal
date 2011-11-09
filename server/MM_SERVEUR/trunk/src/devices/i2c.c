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

  /* Set the pin as output with pull-up */
  cbi(DDRD,0);
  cbi(DDRD,1);
  sbi(PORTD,0);
  sbi(PORTD,1);

  /* Set as I2C master */
  TwInit(0);
  /* Set the bus speed */
  val = 2400;
  TwIOCtl(TWI_SETSPEED, &val);

  return 0;
}

uint8_t i2c_get(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  /* Check the pointer on data area */
  if(data==NULL) { return 6; }
  /* Do the exchange and the returned number of data */
  if(TwMasterTransact(sla, &addr, (uint16_t) 1, data, (uint16_t) nb, (uint32_t) 1000) != ((int) nb)) { return 7; }

  /* Verify that there was no error during the transmission */
  return TwSlaveError();
}

uint8_t i2c_set(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  uint16_t i = 0;
  uint8_t* buff=NULL;
  int ret = 0;

  /* Check the pointer on the data area */
  if(data == NULL) { return 1; }
  /* Allocate a new area in order to build the frame */
  buff = malloc(nb+1);
  /* Check the allocation */
  if(buff == NULL) { return 2; }
  /* Copy the data to the new area */
  for(i=0; i<nb; i++) { buff[i+1] = data[i]; }
  /* But the first data is the destination adress */
  buff[0] = addr;

  /* Do the exchange */
  ret = TwMasterTransact(sla, buff, ((uint16_t)nb)+1, NULL, 0, 1000);
  /* Before to exit, free the allocated area */
  free(buff);
  /* Check the returned code of the exchange */
  if(ret!=0) { return 3; }

  return 0;
}

uint8_t i2c_broadcast_set(uint8_t addr, uint8_t nb, uint8_t* data)
{
  /* Broadcast is a set for adress 0 */
  return i2c_set(0, addr, nb, data);
}
