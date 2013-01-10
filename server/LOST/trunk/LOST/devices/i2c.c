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

volatile uint8_t i2c_mutex;

uint8_t i2c_init(void)
{
  uint32_t val = 0;

  /* Set the pin as input with pull-up */
  cbi(DDRD,0);
  cbi(DDRD,1);
  sbi(PORTD,0);
  sbi(PORTD,1);

  /* Set as I2C master */
  TwInit(1);
  /* Set the bus speed */
  val = 50000; /* MAX = 409582 */
  TwIOCtl(TWI_SETSPEED, &val);

  /* Authorize the use of the hardware interface */
  i2c_mutex = 0;

  return 0;
}

void i2c_reset(void)
{
  /* Clear the interrupt */
  TWCR = (1<<TWINT);
  /* Wait a little bit */
  NutSleep(1);
  /* Generate a STOP */
  TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTO) | (1<<TWEN);
  NutSleep(100); TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTA) | (1<<TWEN);
  NutSleep(100); TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTO) | (1<<TWEN);
  NutSleep(100); TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTA) | (1<<TWEN);
  NutSleep(100); TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTO) | (1<<TWEN);
  NutSleep(100); TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTA) | (1<<TWEN);
  NutSleep(100); TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTO) | (1<<TWEN);
  /* Wait a little bit */
  NutSleep(1);
  /* Stop the I2C core component */
  TWCR = 0;
  /* Wait a little bit */
  NutSleep(1);
  /* Start the I2C core component */
  TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
  /* Initialize TWI */
  i2c_init();
  /* Wait a little bit */
  NutSleep(1);
}

uint8_t i2c_get(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  int nb_rec = 0;
  int ret = 0;

  /* Check the pointer on data area */
  if(data==NULL) { return 6; }

  /* Wait for the hardware interface to be free */
  ret = 10;
  while(ret > 0) { if(i2c_mutex == 0) { i2c_mutex = 1; break; } else { NutSleep(10); ret--; } }
  /* Return if impossible to take the semaphore : do nothing */
  if(ret == 0) { return 7; }

  /* Do the exchange and check the returned number of data */
  nb_rec = TwMasterTransact(sla, &addr, (uint16_t) 1, data, (uint16_t) nb, (uint32_t) 500);
  /* Check the error occurred */
  ret = TwMasterError();
  /* If an error is detected */
  if((nb_rec != nb) || (ret != 0))
  {
    /* Reset the I2C hardware interface */
    i2c_reset();
    /* If no error on transmission, set the returned value to indicate that the error occurred on the number of data */
    if(ret == 0) { ret = 8; }
  }
  /* Free the hardware interface */
  i2c_mutex = 0;

  /* Clear the data if not received */
  if(nb_rec < 0) { nb_rec = 0; }
  while(nb_rec < nb ) { data[nb_rec] = 0; nb_rec++; }

  /* Wait a little bit */
  NutSleep(1);

  return ret;
}

uint8_t i2c_set(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  uint16_t i = 0;
  uint8_t* buff=NULL;
  int nb_rec = 0;
  int ret = 0;

  /* Check the pointer on the data area */
  if(data == NULL) { return 9; }
  /* Allocate a new area in order to build the frame */
  buff = malloc(nb+1);
  /* Check the allocation */
  if(buff == NULL) { return 10; }
  /* Copy the data to the new area */
  if(nb > 0) { for(i=0; i<nb; i++) { buff[i+1] = data[i]; } }
  /* But the first data is the destination address */
  buff[0] = addr;

  /* Do the exchange */
  ret = 0;
  for(i=0; i<3; i++)
  {
    /* Wait for the hardware interface to be free */
    ret = 10;
    while(ret > 0) { if(i2c_mutex == 0) { i2c_mutex = 1; break; } else { NutSleep(10); ret--; } }
    if(ret == 0) { NutSleep(100); ret = 11; continue; }

    /* Execute the transmission */
    nb_rec = TwMasterTransact(sla, buff, (uint16_t) (((uint16_t)nb)+1), NULL, (uint16_t) 0, (uint32_t) 100);
    /* Check the error occurred */
    ret = TwMasterError();
    /* If an error is detected */
    if((nb_rec != 0) || (ret != 0))
    {
      /* Reset the I2C hardware interface */
      i2c_reset();
      /* If no error on transmission, set the returned value to indicate that the error occurred on the number of data */
      if(ret == 0) { ret = 11; }
    }
    /* Free the hardware interface */
    i2c_mutex = 0;
    if((nb_rec == 0) && (ret == 0))
    {
      /* No error, so break the loop */
      break;
    }
    NutSleep(5);
  }
  /* Before to exit, free the allocated area */
  free(buff);
  /* Wait a little bit */
  NutSleep(1);

  return ret;
}

uint8_t i2c_broadcast_set(uint8_t addr, uint8_t nb, uint8_t* data)
{
  /* Broadcast is a set for address 0 */
  return i2c_set(0, addr, nb, data);
}
