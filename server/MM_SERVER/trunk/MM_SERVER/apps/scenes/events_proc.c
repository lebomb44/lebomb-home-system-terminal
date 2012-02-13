#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../rooms/rooms.h"
#include "../../devices/power.h"
#include "events.h"
#include "events_proc.h"

void event_proc_reveil_start(void) { uint8_t i = 0; for(i=0; i<ROOM_SHUTTER_MAX; i++) { rooms_shutter_set(i, ROOM_SHUTTER_UP); } }
void event_proc_couche_start(void) { uint8_t i = 0; for(i=0; i<ROOM_SHUTTER_MAX; i++) { rooms_shutter_set(i, ROOM_SHUTTER_DOWN); } }

void event_proc_wifi_start(void) { power_set(POWER_0, 1); }
void event_proc_wifi_end(void)   { power_set(POWER_0, 0); }

void event_proc_eth_start(void) { power_set(POWER_1, 1); }
void event_proc_eth_end(void)   { power_set(POWER_1, 0); }

void event_proc_power_2_start(void) { power_set(POWER_2, 1); }
void event_proc_power_2_end(void)   { power_set(POWER_2, 0); }

void event_proc_power_3_start(void) { power_set(POWER_3, 1); }
void event_proc_power_3_end(void)   { power_set(POWER_3, 0); }

uint8_t events_proc_init(void)
{
  event_set(EVENT_REVEIL, event_proc_reveil_start, NULL);
  event_set(EVENT_COUCHE, event_proc_couche_start, NULL);
  event_set(EVENT_CHAUFFAGE_SDB, NULL, NULL);
  event_set(EVENT_CHAUFFAGE_CAFE, NULL, NULL);

  event_set(EVENT_LUMIERE_AUTO, NULL, NULL);
  event_set(EVENT_MUSIQUE_AUTO, NULL, NULL);

  event_set(EVENT_POWER_0, event_proc_wifi_start, event_proc_wifi_end);
  event_set(EVENT_POWER_1, event_proc_eth_start , event_proc_eth_end);
  event_set(EVENT_POWER_2, event_proc_power_2_start, event_proc_power_2_end);
  event_set(EVENT_POWER_3, event_proc_power_3_start, event_proc_power_3_end);

  return 0;
}
