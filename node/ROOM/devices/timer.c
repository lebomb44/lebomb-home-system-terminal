#include "../global.h"
#include "timer.h"

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
