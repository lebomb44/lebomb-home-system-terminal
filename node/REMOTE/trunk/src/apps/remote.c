#include "../global.h"
#include "../devices/uart.h"
#include "node.h"
#include "remote.h"

void remote_init(void)
{
  /* Buttons */
  cbi(DDRC,0); sbi(PORTC,0);
  cbi(DDRC,1); sbi(PORTC,1);
  cbi(DDRC,2); sbi(PORTC,2);
  cbi(DDRC,3); sbi(PORTC,3);
  cbi(DDRC,4); sbi(PORTC,4);
  cbi(DDRC,5); sbi(PORTC,5);
  cbi(DDRD,6); sbi(PORTD,6);
  cbi(DDRD,7); sbi(PORTD,7);

  /* LED */
  cbi(DDRB,0); cbi(PORTB,0);
}

#define REMOTE_HEADER_SIZE       (1 + NODE_REG_RF_TX_CTRL - NODE_REG_RF_TX_SRC_ADDR)
#define REMOTE_REG_LB_TX_DATA_NB (1 + REMOTE_HEADER_SIZE - 1)
#define REMOTE_REG_LB_TX_CKSUM   (REMOTE_REG_LB_TX_DATA_NB + buff[REMOTE_REG_LB_TX_DATA_NB] + 1)

#define REMOTE_CMD_SCENE 1

void remote_cycle(void)
{
  u08 i = 0;
  u08 buff[1 + REMOTE_HEADER_SIZE + NODE_RF_DATA_NB + 1] = { 0 };

  /* Set LED ON */
  sbi(PORTB,0);

  /* Set synchro word */
  buff[0] = 0xAA;
  /* Set source address */
  buff[1] = 101;
  /* Set destination address */
  buff[2] = 1;
  /* Set command */
  buff[3] = REMOTE_CMD_SCENE;
  /* Set number of data words */
  buff[REMOTE_REG_LB_TX_DATA_NB] = 2;
  /* Get the pressed button */
  /* Button 0 */
  if(!bit_is_set(PINC,0)) { buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0; }
  /* Button 1 */
  if(!bit_is_set(PINC,1)) { buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0; }
  /* Button 2 */
  if(!bit_is_set(PINC,2)) { buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0; }
  /* Button 3 */
  if(!bit_is_set(PINC,3)) { buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0; }
  /* Button 4 */
  if(!bit_is_set(PINC,4)) { buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0; }
  /* Button 5 */
  if(!bit_is_set(PINC,5)) { buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0; }
  /* Button 6 */
  if(!bit_is_set(PIND,6)) { buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0; }
  /* Button 7 */
  if(!bit_is_set(PIND,7)) { buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0; }
  /* Set SCENE ON */
  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 1;
  /* Erase checksum */
  buff[REMOTE_REG_LB_TX_CKSUM] = 0;
  /* Compute checksum */
  for(i=0; i<(REMOTE_HEADER_SIZE + buff[REMOTE_REG_LB_TX_DATA_NB]); i++) { buff[REMOTE_REG_LB_TX_CKSUM] = buff[REMOTE_REG_LB_TX_CKSUM] + buff[1+i]; }
  /* Send the frame 5 times */
  for(i=0; i<5; i++) { uart_send(buff, 1 + REMOTE_HEADER_SIZE + buff[REMOTE_REG_LB_TX_DATA_NB] + 1); }

  /* Set LED OFF */
  cbi(PORTB,0);
}
