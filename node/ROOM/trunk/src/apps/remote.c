#include "../global.h"
#include "../devices/uart.h"
#include "remote.h"
#include "node.h"

#define PROT_RF_LB 1
#define PROT_START 1
#define PROT_FINISHED 0

void remote_init(void)
{
  node[NODE_REG_RF_TX_ACK] = PROT_FINISHED;
}

#define REMOTE_HEADER_SIZE       (1 + NODE_REG_RF_TX_CTRL - NODE_REG_RF_TX_SRC_ADDR)
#define REMOTE_REG_LB_TX_DATA_NB (1 + REMOTE_HEADER_SIZE - 1)
#define REMOTE_REG_LB_TX_CKSUM   (REMOTE_REG_LB_TX_DATA_NB + buff[REMOTE_REG_LB_TX_DATA_NB] + 1)

void remote_cycle(void)
{
  u08 i = 0;
  u08 buff[1 + REMOTE_HEADER_SIZE + NODE_RF_DATA_NB + 1] = { 0 };

  if(node[NODE_REG_RF_TX_ACK] == PROT_START)
  {
    if(node[NODE_REG_RF_TX_TYPE] == PROT_RF_LB)
    {
      /* Set synchro word */
      buff[0] = 0xAA;
      /* Copy all data from I2C registers */
      for(i=0; i<(REMOTE_HEADER_SIZE + NODE_RF_DATA_NB); i++) { buff[1+i] = node[NODE_REG_RF_TX_SRC_ADDR+i]; }
      /* Check data number register */
      if(buff[REMOTE_REG_LB_TX_DATA_NB] > NODE_RF_DATA_NB) { buff[REMOTE_REG_LB_TX_DATA_NB] = NODE_RF_DATA_NB; }
      /* Erase checksum */
      buff[REMOTE_REG_LB_TX_CKSUM] = 0;
      /* Compute checksum */
      for(i=0; i<(REMOTE_HEADER_SIZE + buff[REMOTE_REG_LB_TX_DATA_NB]); i++) { buff[REMOTE_REG_LB_TX_CKSUM] = buff[REMOTE_REG_LB_TX_CKSUM] + buff[1+i]; }
      /* Send the frame 5 times */
      for(i=0; i<5; i++) { uart_send(buff, 1 + REMOTE_HEADER_SIZE + buff[REMOTE_REG_LB_TX_DATA_NB] + 1); }
    }
    /* Ack the command on I2C bus */
    node[NODE_REG_RF_TX_ACK] = PROT_FINISHED;
  }
}
