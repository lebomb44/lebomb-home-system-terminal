#include "../global.h"
#include "../config.h"
#include "../devices/eeprom.h"
#include "../devices/i2c.h"
#include "../devices/uart.h"
#include "node.h"
#include <avr/eeprom.h>

EEMEM u08 type    = NODE_ROOM_CONFIG_TYPE; /* @ 0 */
EEMEM u08 version = NODE_ROOM_CONFIG_VERSION; /* @ 1 */
EEMEM u08 address = NODE_ROOM_CONFIG_ADDR; /* @ 2 */

EEMEM u08 temp_value       = 0x00; /* @ 3 */
EEMEM u08 temp_max_th      = 0x00; /* @ 4 */
EEMEM u08 temp_max_control = 0x00; /* @ 5 */
EEMEM u08 temp_max_trig    = 0x00; /* @ 6 */
EEMEM u08 temp_min_th      = 0x00; /* @ 7 */
EEMEM u08 temp_min_control = 0x00; /* @ 8 */
EEMEM u08 temp_min_trig    = 0x00; /* @ 9 */

EEMEM u08 hum_status  = 0x00; /* @ 10 */
EEMEM u08 hum_control = 0x00; /* @ 11 */
EEMEM u08 hum_trig    = 0x00; /* @ 12 */

EEMEM u08 smoke_status  = 0x00; /* @ 13 */
EEMEM u08 smoke_control = 0x00; /* @ 14 */
EEMEM u08 smoke_trig    = 0x00; /* @ 15 */

EEMEM u08 peri_status  = 0x00; /* @ 16 */
EEMEM u08 peri_control = 0x00; /* @ 17 */
EEMEM u08 peri_trig    = 0x00; /* @ 18 */

EEMEM u08 vol_status  = 0x00; /* @ 19 */
EEMEM u08 vol_control = 0x00; /* @ 20 */
EEMEM u08 vol_trig    = 0x00; /* @ 21 */

EEMEM u08 sim_status  = 0x00; /* @ 22 */
EEMEM u08 sim_control = 0x00; /* @ 23 */
EEMEM u08 sim_trig    = 0x00; /* @ 24 */

EEMEM u08 light[NODE_LIGHT_MAX]     = { 0,0,0,0,0,0,0,0,0,0 }; /* @ 25 - 34 */
EEMEM u08 shutter[NODE_SHUTTER_MAX] = { 0,0,0,0,0,0,0,0,0,0 }; /* @ 35 - 44 */
EEMEM u08 heater[NODE_HEATER_MAX]   = { 0,0,0,0,0,0,0,0,0,0 }; /* @ 45 - 54 */
EEMEM u08 elec[NODE_ELEC_MAX]       = { 0,0,0,0,0,0,0,0,0,0 }; /* @ 55 - 64 */

EEMEM u08 ir_tx_type      = 0x00; /* @ 65 */
EEMEM u08 ir_tx_src_addr  = 0x00; /* @ 66 */
EEMEM u08 ir_tx_dest_addr = 0x00; /* @ 67 */
EEMEM u08 ir_tx_cmd       = 0x00; /* @ 68 */
EEMEM u08 ir_tx_ctrl      = 0x00; /* @ 69 */
EEMEM u08 ir_tx_data[NODE_IR_DATA_NB] = { 0,0,0,0,0,0,0,0,0,0 }; /* @ 70 - 79 */
EEMEM u08 ir_tx_ack       = 0x00; /* @ 80 */

EEMEM u08 ir_rx_type      = 0x00; /* @ 81 */
EEMEM u08 ir_rx_src_addr  = 0x00; /* @ 82 */
EEMEM u08 ir_rx_dest_addr = 0x00; /* @ 83 */
EEMEM u08 ir_rx_cmd       = 0x00; /* @ 84 */
EEMEM u08 ir_rx_ctrl      = 0x00; /* @ 85 */
EEMEM u08 ir_rx_data[NODE_IR_DATA_NB] = { 0,0,0,0,0,0,0,0,0,0 }; /* @ 86 - 95 */
EEMEM u08 ir_rx_ack       = 0x00; /* @ 96 */

EEMEM u08 rf_tx_type      = 0x00; /* @ 97 */
EEMEM u08 rf_tx_src_addr  = 0x00; /* @ 98 */
EEMEM u08 rf_tx_dest_addr = 0x00; /* @ 99 */
EEMEM u08 rf_tx_cmd       = 0x00; /* @ 100 */
EEMEM u08 rf_tx_ctrl      = 0x00; /* @ 101 */
EEMEM u08 rf_tx_data[NODE_RF_DATA_NB] = { 0,0,0,0,0,0,0,0,0,0 }; /* @ 102 - 111 */
EEMEM u08 rf_tx_ack       = 0x00; /* @ 112 */

EEMEM u08 rf_rx_type      = 0x00; /* @ 113 */
EEMEM u08 rf_rx_src_addr  = 0x00; /* @ 114 */
EEMEM u08 rf_rx_dest_addr = 0x00; /* @ 115 */
EEMEM u08 rf_rx_cmd       = 0x00; /* @ 116 */
EEMEM u08 rf_rx_ctrl      = 0x00; /* @ 117 */
EEMEM u08 rf_rx_data[NODE_RF_DATA_NB] = { 0,0,0,0,0,0,0,0,0,0 }; /* @ 118 - 127 */
EEMEM u08 rf_rx_ack       = 0x00; /* @ 128 */

EEMEM u08 clim = 0x00; /* @ 129 */

u08 node[NODE_REG_MAX]; /* 130 */

void node_init(void)
{
  u08 i=0;
  for(i=0; i<NODE_REG_MAX; i++)
  {
    node[i] = 0x00; /* eeprom_read(i); */
  }
  node[NODE_REG_TYPE]    = NODE_ROOM_CONFIG_TYPE;
  node[NODE_REG_VERSION] = NODE_ROOM_CONFIG_VERSION;
  node[NODE_REG_ADDRESS]  = NODE_ROOM_CONFIG_ADDR;
  i2c_adr_set(node[NODE_REG_ADDRESS]);
/*
uart_printf((u08*)"type=%d\n",node[NODE_REG_TYPE]);
uart_printf((u08*)"version=%d\n",node[NODE_REG_VERSION]);
uart_printf((u08*)"adress=%d\n",node[NODE_REG_ADRESS]);
*/
}
