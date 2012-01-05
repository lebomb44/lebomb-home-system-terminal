#include "../global.h"
#include "../devices/uart.h"
#include "rfif.h"
#include "node.h"

#define PROT_RF_LB 1
#define PROT_START 1
#define PROT_FINISHED 0

void rfif_init(void)
{
  node[NODE_REG_RF_TX_ACK] = PROT_FINISHED;
}

#define RFIF_HEADER_SIZE       (1 + NODE_REG_IR_TX_CTRL - NODE_REG_IR_TX_SRC_ADDR)
#define RFIF_REG_LB_TX_DATA_NB (1+NODE_REG_RF_TX_CTRL-NODE_REG_RF_TX_SRC_ADDR)
#define RFIF_REG_LB_CKSUM      (1 + 4 + buff[RFIF_REG_LB_TX_DATA_NB])

void rfif_cycle(void)
{
  u08 i = 0;
  u08 buff[1 + 4 + NODE_RF_DATA_NB + 1] = { 0 };

  if(node[NODE_REG_RF_TX_ACK] == PROT_START)
  {
    if(node[NODE_REG_IR_TX_TYPE] == PROT_RF_LB)
    {
      /* Set synchro word */
      buff[0] = 0xAA;
      /* Copy all data from I2C registers */
      for(i=0; i<(RFIF_HEADER_SIZE + NODE_RF_DATA_NB); i++) { buff[1+i] = node[NODE_REG_IR_TX_SRC_ADDR+i]; }
      /* Check data number register */
      if(buff[RFIF_REG_LB_TX_DATA_NB] > NODE_RF_DATA_NB) { buff[RFIF_REG_LB_TX_DATA_NB] = NODE_RF_DATA_NB; }
      /* Erase checksum */
      buff[RFIF_HEADER_SIZE + buff[RFIF_REG_LB_TX_DATA_NB]] = 0;
      /* Compute checksum */
      for(i=0; i<(RFIF_HEADER_SIZE + buff[RFIF_REG_LB_TX_DATA_NB]); i++) { buff[RFIF_REG_LB_CKSUM] = buff[RFIF_REG_LB_CKSUM] + buff[1+i]; }
      /* Send the frame */
      uart_send(buff, 1 + RFIF_HEADER_SIZE + buff[RFIF_REG_LB_TX_DATA_NB] + 1);
      /* Ack the command on I2C bus */
      node[NODE_REG_RF_TX_ACK] = PROT_FINISHED;
    }
  }
}
