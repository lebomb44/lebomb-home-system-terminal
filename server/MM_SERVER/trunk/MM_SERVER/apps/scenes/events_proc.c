#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../rooms/rooms.h"
#include "../../devices/power.h"
#include "events.h"
#include "events_proc.h"

void event_proc_reveil_start(void)
{
  uint8_t i = 0;
  for(i=0; i<ROOM_SHUTTER_MAX; i++) { rooms_shutter_set(i, ROOM_SHUTTER_UP); }
}

void event_proc_couche_start(void)
{
  uint8_t i = 0;
  for(i=0; i<ROOM_SHUTTER_MAX; i++) { rooms_shutter_set(i, ROOM_SHUTTER_DOWN); }
}

void event_proc_wifi_start(void)
{
  power_set(POWER_0, 1);
}

void event_proc_wifi_end(void)
{
  power_set(POWER_0, 0);
}

uint8_t events_proc_init(void)
{
  event_set(EVENT_REVEIL, event_proc_reveil_start, NULL);
  event_set(EVENT_COUCHE, event_proc_couche_start, NULL);
  event_set(EVENT_MUSIQUE_AUTO, event_proc_wifi_start, event_proc_wifi_end);

  return 0;
}
