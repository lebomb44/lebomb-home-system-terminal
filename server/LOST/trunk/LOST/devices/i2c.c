#include <stdlib.h>
#include <stdio.h>

#include <dev/twif.h>
#include <dev/irqreg.h>

#include <sys/event.h>
#include <sys/atom.h>
#include <sys/timer.h>
#include <sys/event.h>
#include <sys/thread.h>
#include <sys/heap.h>

#include "i2c.h"

static HANDLE i2c_mutex;

uint8_t i2c_init(void)
{
  uint32_t val = 0;

  /* Set the pin as output with pull-up */
  cbi(DDRD,0);
  cbi(DDRD,1);
  sbi(PORTD,0);
  sbi(PORTD,1);

  /* Set as I2C master */
  TwInit(1);
  /* Set the bus speed */
  val = 50000;
  TwIOCtl(TWI_SETSPEED, &val);
  /* Authorize the use of the hardware interface */
  NutEventPost(&i2c_mutex);

  return 0;
}

uint8_t i2c_get(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  int ret = 0;

  /* Check the pointer on data area */
  if(data==NULL) { return 6; }

  /* Wait for the hardware interface to be free */
  ret = NutEventWait(&i2c_mutex, 100);
  if(ret != 0) { return 7; }

  /* Send a STOP on I2C in order to initialize the transmission */
  outb(TWCR, _BV(TWINT));
  outb(TWCR, _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWSTO));

  /* Do the exchange and check the returned number of data */
  if(TwMasterTransact(sla, &addr, (uint16_t) 1, data, (uint16_t) nb, (uint32_t) 500) != ((int) nb))
  {
    ret = TwMasterError();
    /* Free the hardware interface */
    NutEventPost(&i2c_mutex);
    if(ret == 0) { return 8; } else { return ret; }
  }

  /* Verify that there was no error during the transmission */
  ret = TwMasterError();
  /* Free the hardware interface */
  NutEventPost(&i2c_mutex);
  NutSleep(1);

  return ret;
}

uint8_t i2c_set(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  uint16_t i = 0;
  uint8_t* buff=NULL;
  int ret = 0;

  /* Check the pointer on the data area */
  if(data == NULL) { return 8; }
  /* Allocate a new area in order to build the frame */
  buff = malloc(nb+1);
  /* Check the allocation */
  if(buff == NULL) { return 9; }
  /* Copy the data to the new area */
  for(i=0; i<nb; i++) { buff[i+1] = data[i]; }
  /* But the first data is the destination address */
  buff[0] = addr;

  /* Do the exchange */
  ret = 0;
  for(i=0; i<3; i++)
  {
    /* Wait for the hardware interface to be free */
    ret = NutEventWait(&i2c_mutex, 100);
    if(ret != 0) { continue; }
    /* Send a STOP on I2C in order to initialize the transmission */
    outb(TWCR, _BV(TWINT));
    outb(TWCR, _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWSTO));
    ret += TwMasterTransact(sla, buff, (uint16_t) (((uint16_t)nb)+1), NULL, (uint16_t) 0, (uint32_t) 100);
    if(i==2)
    {
      ret = TwMasterError();
    }
    /* Free the hardware interface */
    NutEventPost(&i2c_mutex);
    NutSleep(5);
  }
  /* Before to exit, free the allocated area */
  free(buff);

  return ret;
}

uint8_t i2c_broadcast_set(uint8_t addr, uint8_t nb, uint8_t* data)
{
  /* Broadcast is a set for address 0 */
  return i2c_set(0, addr, nb, data);
}
