#ifndef _NODE_ROOM_CONFIG_H_
#define _NODE_ROOM_CONFIG_H_

#define PB2_IR_USED       1
#define PB2_BUTTON_USED   2
#define PB2_LIGHT_ST_USED 3

#define NODE_ROOM_CONFIG_TYPE           0x01
#define NODE_ROOM_CONFIG_VERSION        0x01
#define NODE_ROOM_CONFIG_HEATER_BUT     { 255, 255, 255 }
#define NODE_ROOM_CONFIG_HEATER_RELAY   { 255, 255, 255 }
#define NODE_ROOM_CONFIG_ELEC_BUT       { 255, 255, 255 }
#define NODE_ROOM_CONFIG_ELEC_RELAY     { 255, 255, 255 }

/* Marine */
#ifdef NODE_ROOM_CONFIG_mms_c1
#define NODE_ROOM_CONFIG_ADDR               (10+0)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_IR_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

/* M&M */
#ifdef NODE_ROOM_CONFIG_mms_c2
#define NODE_ROOM_CONFIG_ADDR               (10+1)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_IR_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

/* Amis */
#ifdef NODE_ROOM_CONFIG_mms_c3
#define NODE_ROOM_CONFIG_ADDR               (10+2)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_IR_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

/* Dressing */
#ifdef NODE_ROOM_CONFIG_mms_c4
#define NODE_ROOM_CONFIG_ADDR               (10+3)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_IR_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

/* Combles */
#ifdef NODE_ROOM_CONFIG_mms_combles
#define NODE_ROOM_CONFIG_ADDR               (10+4)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_LIGHT_ST_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

/* Bureau */
#ifdef NODE_ROOM_CONFIG_mms_bureau
#define NODE_ROOM_CONFIG_ADDR               (10+5)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_IR_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

/* Salon */
#ifdef NODE_ROOM_CONFIG_mms_salon
#define NODE_ROOM_CONFIG_ADDR               (10+6)
#define PB2_USAGE                           PB2_BUTTON_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 2, 4 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 3, 5 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 2, 4 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 3, 5 }
#endif

/* Cuisine */
#ifdef NODE_ROOM_CONFIG_mms_cuisine
#define NODE_ROOM_CONFIG_ADDR               (10+7)
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 2, 3, 4 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 2, 3, 4 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

/* Couloir */
#ifdef NODE_ROOM_CONFIG_mms_couloir
#define NODE_ROOM_CONFIG_ADDR               (10+8)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_IR_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

/* Salon2 */
#ifdef NODE_ROOM_CONFIG_mms_salon2
#define NODE_ROOM_CONFIG_ADDR               (10+9)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_IR_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 255, 255, 255 }
#endif

/* Terrasse */
#ifdef NODE_ROOM_CONFIG_mms_terrasse
#define NODE_ROOM_CONFIG_ADDR               (10+10)
#define QUARTZ_USED
#define PB2_USAGE                           PB2_IR_USED
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

#endif
