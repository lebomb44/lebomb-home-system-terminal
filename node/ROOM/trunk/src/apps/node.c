#include "../global.h"
#include "../devices/eeprom.h"
#include "../devices/i2c.h"
#include "../devices/uart.h"
#include "node.h"
#include <avr/eeprom.h>

EEMEM u08 type    = 0x01; /* @ 0 */
EEMEM u08 version = 0x01; /* @ 1 */
EEMEM u08 adress  = 0x06; /* @ 2 */

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

EEMEM u08 ir_type = 0x00; /* @ 25 */
EEMEM u08 ir_cmd0 = 0x00; /* @ 26 */
EEMEM u08 ir_cmd1 = 0x00; /* @ 27 */

EEMEM u08 light[NODE_LIGHT_MAX] = { 0,0,0,0,0,0,0,0,0,0 };
EEMEM u08 shutter[NODE_SHUTTER_MAX] = { 0,0,0,0,0,0,0,0,0,0 };
EEMEM u08 heater[NODE_HEATER_MAX] = { 0,0,0,0,0,0,0,0,0,0 };
EEMEM u08 elec[NODE_ELEC_MAX] = { 0,0,0,0,0,0,0,0,0,0 };

u08 node[NODE_REG_MAX];

void node_init(void)
{
  u08 i=0;
  for(i=0; i<NODE_REG_MAX; i++)
  {
    node[i] = eeprom_read(i);
  }
  i2c_adr_set(node[NODE_REG_ADRESS]);

uart_printf((u08*)"type=%d\n",node[NODE_REG_TYPE]);
uart_printf((u08*)"version=%d\n",node[NODE_REG_VERSION]);
uart_printf((u08*)"adress=%d\n",node[NODE_REG_ADRESS]);
}
