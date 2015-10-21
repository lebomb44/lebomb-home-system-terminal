#include "global.h"

void timer_init(void)
{
  /* Initialisations de Timer0 */
  sbi(TIMSK,0);  /* Interruption Timer0 owerflow */
  TCNT0 = 0x00;  /* Initialisation Timer0 */
  TCCR0 = 0x00;  /* Clock Select STOP */
  /* Initialisations de Timer2 */
  // sbi(TIMSK,6);    // Interruption Timer2 owerflow
  // TCNT2=0x00;         // Initialisation timer2
}

void timer_start(void)
{
  TCCR0 = 0x05;  /* Clock Select clkio/1024 */
}

void timer_stop(void)
{
  TCCR0 = 0x00;  /* Clock Select STOP */
}

void sleep_mode(void)
{
  MCUCR = 0x80; /* Sleep mode */
}

/* Timer0 */
SIGNAL(TIMER0_OVF_vect)
{
  TCNT0=0x00;
}

/*
SIGNAL(TIMER2_OVF_vect)
{
}
*/

void sleep_seconds(u08 secs)
{
  u08 i = 0;

  while(0 < secs)
  {
    sleep();
    for(i=0; i<30; i++) { sleep(); }
    secs--;
  }
}

#define RESPDDR DDRD
#define RESPPIN PIND
#define RESPPORT PORTD
#define RESPBIT 2
#define POWERDDR DDRD
#define POWERPORT PORTD
#define POWERBIT 6
#define CMDDDR DDRD
#define CMDPORT PORTD
#define CMDBIT 7

/* 30 ticks/sec * 30 secs/cycle * 4 cycles */
#define RESP_TIMEOUT (30*30*4)

int main(void)
{
  u32 time_out = RESP_TIMEOUT;

  /* Pins initialization */
  cbi(RESPDDR, RESPBIT); sbi(RESPPORT, RESPBIT);
  sbi(POWERDDR, POWERBIT); cbi(POWERPORT, POWERBIT);
  sbi(CMDDDR, CMDBIT); cbi(CMDPORT, CMDBIT);

  /* Timer sleep mode enable */
  sleep_mode();
  sbi(SREG,7);
  timer_start();

  /* Power the phone */
  sleep_seconds(1); sbi(POWERPORT, POWERBIT);
  /* Wait for start sequence */
  sleep_seconds(2);
  /* Switch ON the phone */
  sbi(CMDPORT, CMDBIT); sleep_seconds(3); cbi(CMDPORT, CMDBIT);

  while(1)
  {
    /* Check if the phone answer on the LOST UART */
    if(bit_is_clear(RESPPIN, RESPBIT))
    {
      /* 30 ticks/sec * 30 secs/cycle * 4 cycles */
      time_out = RESP_TIMEOUT;
    }
    else
    {
      /* It does not answered */
      if(0 < time_out) { time_out--; }
    }
    /* Now time is over */
    if(0 == time_out)
    {
      /* Unpower the phone */
      cbi(CMDPORT, CMDBIT);
      cbi(POWERPORT, POWERBIT);
      /* Power the phone */
      sleep_seconds(2); sbi(POWERPORT, POWERBIT);
      /* Wait for start sequence */
      sleep_seconds(2);
      /* Switch ON the phone */
      sbi(CMDPORT, CMDBIT); sleep_seconds(3); cbi(CMDPORT, CMDBIT);
      /* Reset timer */
      time_out = RESP_TIMEOUT;
    }
    sleep();
  }
  return 0;
}
