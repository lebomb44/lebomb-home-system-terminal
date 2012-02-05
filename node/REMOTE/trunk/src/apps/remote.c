#include "../global.h"
#include "../devices/uart.h"
#include "node.h"
#include "remote.h"

void remote_init(void)
{
  /* Buttons */
  cbi(DDRD,4); sbi(PORTD,4);
  cbi(DDRD,6); sbi(PORTD,6);
  cbi(DDRD,3); sbi(PORTD,3);
  cbi(DDRD,5); sbi(PORTD,5);
  cbi(DDRD,2); sbi(PORTD,2);
  cbi(DDRB,7); sbi(PORTB,7);
  cbi(DDRD,1); sbi(PORTD,1);
  cbi(DDRB,6); sbi(PORTB,6);

  /* LED */
  sbi(DDRB,0); sbi(PORTB,0);
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
  /* Button 1 ON */
  if(!bit_is_set(PIND,4)) { /* SCENE 0 */ buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0;   /* SCENE ON */  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 1; }
  /* Button 1 OFF */
  if(!bit_is_set(PIND,6)) { /* SCENE 0 */ buff[REMOTE_REG_LB_TX_DATA_NB+1] = 0;   /* SCENE OFF */  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 0; }
  /* Button 2 ON */
  if(!bit_is_set(PIND,3)) { /* SCENE 1 */ buff[REMOTE_REG_LB_TX_DATA_NB+1] = 1;   /* SCENE ON */  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 1; }
  /* Button 2 OFF */
  if(!bit_is_set(PIND,5)) { /* SCENE 1 */ buff[REMOTE_REG_LB_TX_DATA_NB+1] = 1;   /* SCENE OFF */  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 0; }
  /* Button 3 ON */
  if(!bit_is_set(PIND,2)) { /* SCENE 2 */ buff[REMOTE_REG_LB_TX_DATA_NB+1] = 2;   /* SCENE ON */  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 1; }
  /* Button 3 OFF */
  if(!bit_is_set(PINB,7)) { /* SCENE 2 */ buff[REMOTE_REG_LB_TX_DATA_NB+1] = 2;   /* SCENE OFF */  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 0; }
  /* Button 4 ON */
  if(!bit_is_set(PIND,1)) { /* SCENE 3 */ buff[REMOTE_REG_LB_TX_DATA_NB+1] = 3;   /* SCENE ON */  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 1; }
  /* Button 4 OFF */
  if(!bit_is_set(PINB,6)) { /* SCENE 3 */ buff[REMOTE_REG_LB_TX_DATA_NB+1] = 3;   /* SCENE OFF */  buff[REMOTE_REG_LB_TX_DATA_NB+2] = 0; }
  /* Erase checksum */
  buff[REMOTE_REG_LB_TX_CKSUM] = 0;
  /* Compute checksum */
  for(i=0; i<(REMOTE_HEADER_SIZE + buff[REMOTE_REG_LB_TX_DATA_NB]); i++) { buff[REMOTE_REG_LB_TX_CKSUM] = buff[REMOTE_REG_LB_TX_CKSUM] + buff[1+i]; }
  /* Send the frame 10 times */
  for(i=0; i<10; i++) { uart_send(buff, 1 + REMOTE_HEADER_SIZE + buff[REMOTE_REG_LB_TX_DATA_NB] + 1); }

  /* Set LED OFF */
  sbi(PORTB,0);
}
