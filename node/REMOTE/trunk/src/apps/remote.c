#include "../global.h"
#include "../devices/uart.h"
#include "node.h"
#include "../config.h"
#include "remote.h"

void remote_init(void)
{
  /* Buttons */
  cbi(DDRC,0); sbi(PORTC,0);
  cbi(DDRD,6); sbi(PORTD,6);
  cbi(DDRC,1); sbi(PORTC,1);
  cbi(DDRD,5); sbi(PORTD,5);
  cbi(DDRC,2); sbi(PORTC,2);
  cbi(DDRB,0); sbi(PORTB,0);
  cbi(DDRC,4); sbi(PORTC,4);
  cbi(DDRB,1); sbi(PORTB,1);
}

#define REMOTE_HEADER_SIZE       (4)
#define REMOTE_REG_LB_TX_DATA_NB (1 + REMOTE_HEADER_SIZE - 1)
#define REMOTE_REG_LB_TX_CKSUM   (REMOTE_REG_LB_TX_DATA_NB + buff[REMOTE_REG_LB_TX_DATA_NB] + 1)

#define REMOTE_CMD_SCENE 1

void remote_cycle(void)
{
  u08 scene = 0;
  u08 state = 0;
  u08 i = 0;
  u08 buff[1 + REMOTE_HEADER_SIZE + NODE_RF_DATA_NB + 1] = { 0 };

  /* Get the pressed button */

  /* Button 1 ON */
  if(!bit_is_set(PINC,0)) { /* SCENE 0 */ scene = 0xCA + NODE_REMOTE_BUTTON1_ON_CMD;   /* STATE ON */  state = 0xCA + NODE_REMOTE_BUTTON1_ON_DATA; }
  /* Button 1 OFF */
  if(!bit_is_set(PIND,6)) { /* SCENE 1 */ scene = 0xCA + NODE_REMOTE_BUTTON1_OFF_CMD;   /* STATE OFF */  state = 0xCA + NODE_REMOTE_BUTTON1_OFF_DATA; }
  /* Button 2 ON */
  if(!bit_is_set(PINC,1)) { /* SCENE 2 */ scene = 0xCA + NODE_REMOTE_BUTTON2_ON_CMD;   /* STATE ON */  state = 0xCA + NODE_REMOTE_BUTTON2_ON_DATA; }
  /* Button 2 OFF */
  if(!bit_is_set(PIND,5)) { /* SCENE 2 */ scene = 0xCA + NODE_REMOTE_BUTTON2_OFF_CMD;   /* STATE OFF */  state = 0xCA + NODE_REMOTE_BUTTON2_OFF_DATA; }
  /* Button 3 ON */
  if(!bit_is_set(PINC,2)) { /* SCENE 3 */ scene = 0xCA + NODE_REMOTE_BUTTON3_ON_CMD;   /* STATE ON */  state = 0xCA + NODE_REMOTE_BUTTON3_ON_DATA; }
  /* Button 3 OFF */
  if(!bit_is_set(PINB,0)) { /* SCENE 3 */ scene = 0xCA + NODE_REMOTE_BUTTON3_OFF_CMD;   /* STATE OFF */  state = 0xCA + NODE_REMOTE_BUTTON3_OFF_DATA; }
  /* Button 4 ON */
  if(!bit_is_set(PINC,4)) { /* SCENE 4 */ scene = 0xCA + NODE_REMOTE_BUTTON4_ON_CMD;   /* STATE ON */  state = 0xCA + NODE_REMOTE_BUTTON4_ON_DATA; }
  /* Button 4 OFF */
  if(!bit_is_set(PINB,1)) { /* SCENE 4 */ scene = 0xCA + NODE_REMOTE_BUTTON4_OFF_CMD;   /* STATE OFF */  state = 0xCA + NODE_REMOTE_BUTTON4_OFF_DATA; }

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
  /* Set the SCENE number */
  buff[REMOTE_REG_LB_TX_DATA_NB+1] = scene;
  /* Set the state */
  buff[REMOTE_REG_LB_TX_DATA_NB+2] = state;
  /* Erase checksum */
  buff[REMOTE_REG_LB_TX_CKSUM] = 0;
  /* Compute checksum */
  for(i=0; i<(REMOTE_HEADER_SIZE + buff[REMOTE_REG_LB_TX_DATA_NB]); i++) { buff[REMOTE_REG_LB_TX_CKSUM] = buff[REMOTE_REG_LB_TX_CKSUM] + buff[1+i]; }
  /* Send the frame 10 times */
  while(1) { uart_send(buff, 1 + REMOTE_HEADER_SIZE + buff[REMOTE_REG_LB_TX_DATA_NB] + 1); }
}
