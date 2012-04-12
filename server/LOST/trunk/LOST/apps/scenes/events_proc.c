#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../rooms/rooms.h"
#include "../../devices/power.h"
#include "events.h"
#include "events_proc.h"

void event_proc_shutters_all_start(void)        { uint8_t i = 0; for(i=0; i<ROOM_SHUTTER_MAX; i++) { rooms_shutter_set(i, ROOM_SHUTTER_UP); } }
void event_proc_shutters_all_end(void)          { uint8_t i = 0; for(i=0; i<ROOM_SHUTTER_MAX; i++) { rooms_shutter_set(i, ROOM_SHUTTER_DOWN); } }
void event_proc_shutters_upstairs_start(void)   { room_shutters_set(ROOM_C1, ROOM_SHUTTER_UP); room_shutters_set(ROOM_C2, ROOM_SHUTTER_UP);
                                                  room_shutters_set(ROOM_C3, ROOM_SHUTTER_UP); room_shutters_set(ROOM_C4, ROOM_SHUTTER_UP); }
void event_proc_shutters_upstairs_end(void)     { room_shutters_set(ROOM_C1, ROOM_SHUTTER_DOWN); room_shutters_set(ROOM_C2, ROOM_SHUTTER_DOWN);
                                                  room_shutters_set(ROOM_C3, ROOM_SHUTTER_DOWN); room_shutters_set(ROOM_C4, ROOM_SHUTTER_DOWN); }
void event_proc_shutters_downstairs_start(void) { room_shutters_set(ROOM_BUREAU  , ROOM_SHUTTER_UP); room_shutters_set(ROOM_SALON  , ROOM_SHUTTER_UP);
                                                  room_shutters_set(ROOM_CUISINE , ROOM_SHUTTER_UP); room_shutters_set(ROOM_COULOIR, ROOM_SHUTTER_UP);
                                                  room_shutters_set(ROOM_TERRASSE, ROOM_SHUTTER_UP); }
void event_proc_shutters_downstairs_end(void)   { room_shutters_set(ROOM_BUREAU  , ROOM_SHUTTER_DOWN); room_shutters_set(ROOM_SALON  , ROOM_SHUTTER_DOWN);
                                                  room_shutters_set(ROOM_CUISINE , ROOM_SHUTTER_DOWN); room_shutters_set(ROOM_COULOIR, ROOM_SHUTTER_DOWN);
                                                  room_shutters_set(ROOM_TERRASSE, ROOM_SHUTTER_DOWN); }
void event_proc_shutters_marine_start(void)     { room_shutters_set(ROOM_C1, ROOM_SHUTTER_UP); }
void event_proc_shutters_marine_end(void)       { room_shutters_set(ROOM_C1, ROOM_SHUTTER_DOWN); }
void event_proc_shutters_mm_start(void)         { room_shutters_set(ROOM_C2, ROOM_SHUTTER_UP); }
void event_proc_shutters_mm_end(void)           { room_shutters_set(ROOM_C2, ROOM_SHUTTER_DOWN); }
void event_proc_shutters_friends_start(void)    { room_shutters_set(ROOM_C3, ROOM_SHUTTER_UP); }
void event_proc_shutters_friends_end(void)      { room_shutters_set(ROOM_C3, ROOM_SHUTTER_DOWN); }
void event_proc_shutters_dressing_start(void)   { room_shutters_set(ROOM_C4, ROOM_SHUTTER_UP); }
void event_proc_shutters_dressing_end(void)     { room_shutters_set(ROOM_C4, ROOM_SHUTTER_DOWN); }

void event_proc_wifi_start(void)    { power_set(POWER_0, 1); }
void event_proc_wifi_end(void)      { power_set(POWER_0, 0); }
void event_proc_eth_start(void)     { power_set(POWER_1, 1); }
void event_proc_eth_end(void)       { power_set(POWER_1, 0); }
void event_proc_power_2_start(void) { power_set(POWER_2, 1); }
void event_proc_power_2_end(void)   { power_set(POWER_2, 0); }
void event_proc_power_3_start(void) { power_set(POWER_3, 1); }
void event_proc_power_3_end(void)   { power_set(POWER_3, 0); }

uint8_t events_proc_init(void)
{
  event_set(EVENT_SHUTTERS_ALL       , event_proc_shutters_all_start       , event_proc_shutters_all_end);
  event_set(EVENT_SHUTTERS_UPSTAIRS  , event_proc_shutters_upstairs_start  , event_proc_shutters_upstairs_end);
  event_set(EVENT_SHUTTERS_DOWNSTAIRS, event_proc_shutters_downstairs_start, event_proc_shutters_downstairs_end);
  event_set(EVENT_SHUTTERS_MARINE    , event_proc_shutters_marine_start    , event_proc_shutters_marine_end);
  event_set(EVENT_SHUTTERS_MM        , event_proc_shutters_mm_start        , event_proc_shutters_mm_end);
  event_set(EVENT_SHUTTERS_FRIENDS   , event_proc_shutters_friends_start   , event_proc_shutters_friends_end);
  event_set(EVENT_SHUTTERS_DRESSING  , event_proc_shutters_dressing_start  , event_proc_shutters_dressing_end);

  event_set(EVENT_ALARM_ALL      , NULL, NULL);
  event_set(EVENT_ALARM_PERIMETER, NULL, NULL);
  event_set(EVENT_ALARM_VOLUME   , NULL, NULL);
  event_set(EVENT_SIMU           , NULL, NULL);

  event_set(EVENT_POWER_0, event_proc_wifi_start   , event_proc_wifi_end);
  event_set(EVENT_POWER_1, event_proc_eth_start    , event_proc_eth_end);
  event_set(EVENT_POWER_2, event_proc_power_2_start, event_proc_power_2_end);
  event_set(EVENT_POWER_3, event_proc_power_3_start, event_proc_power_3_end);

  return 0;
}
