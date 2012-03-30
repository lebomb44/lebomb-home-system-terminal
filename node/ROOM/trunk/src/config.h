#ifndef _NODE_ROOM_CONFIG_H_
#define _NODE_ROOM_CONFIG_H_

#define NODE_ROOM_CONFIG_HEATER_BUT     { 255, 255, 255 }
#define NODE_ROOM_CONFIG_HEATER_RELAY   { 255, 255, 255 }
#define NODE_ROOM_CONFIG_ELEC_BUT       { 255, 255, 255 }
#define NODE_ROOM_CONFIG_ELEC_RELAY     { 255, 255, 255 }

#ifdef NODE_ROOM_CONFIG_mms_salon
#define NODE_ROOM_CONFIG_TYPE               0x01
#define NODE_ROOM_CONFIG_VERSION            0x01
#define NODE_ROOM_CONFIG_ADDR               (10+6)
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 255, 255, 255 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 255, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 2, 4 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 3, 5 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 2, 4 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 3, 5 }
#endif

#ifdef NODE_ROOM_CONFIG_mms_cuisine
#define NODE_ROOM_CONFIG_TYPE               0x01
#define NODE_ROOM_CONFIG_VERSION            0x01
#define NODE_ROOM_CONFIG_ADDR               (10+7)
#define NODE_ROOM_CONFIG_LIGHT_BUT          { 2, 3, 4 }
#define NODE_ROOM_CONFIG_LIGHT_RELAY        { 2, 3, 4 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_UP     { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN   { 1, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_UP   { 0, 255, 255 }
#define NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN { 1, 255, 255 }
#endif

#endif
/*
  ROOM_C1 = 0,
  ROOM_C2,
  ROOM_C3,
  ROOM_C4,
  ROOM_SDB,
  ROOM_BUREAU,
  ROOM_SALON,
  ROOM_CUISINE,
  ROOM_COULOIR,
  ROOM_TERRASSE,
*/
