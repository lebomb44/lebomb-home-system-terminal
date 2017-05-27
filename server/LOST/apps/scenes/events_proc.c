#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alarm.h"
#include "../../devices/power.h"
#include "events.h"
#include "events_proc.h"

void event_proc_alarm_all_start(void)             { alarm_perimeter_set(ALARM_TYPE_ON_MANUAL); alarm_volume_set(ALARM_TYPE_ON_MANUAL); }
void event_proc_alarm_all_end(void)               { alarm_perimeter_set(ALARM_TYPE_OFF_MANUAL); alarm_volume_set(ALARM_TYPE_OFF_MANUAL); }
void event_proc_alarm_perimeter_start(void)       { alarm_perimeter_set(ALARM_TYPE_ON_MANUAL); }
void event_proc_alarm_perimeter_end(void)         { alarm_perimeter_set(ALARM_TYPE_OFF_MANUAL); }
void event_proc_alarm_perimeter_check_start(void) { alarm_perimeter_set(ALARM_TYPE_ON_AUTO); }
void event_proc_alarm_perimeter_check_end(void)   { alarm_perimeter_set(ALARM_TYPE_OFF_AUTO); }
void event_proc_alarm_volume_start(void)          { alarm_volume_set(ALARM_TYPE_ON_MANUAL); }
void event_proc_alarm_volume_end(void)            { alarm_volume_set(ALARM_TYPE_OFF_MANUAL); }
void event_proc_alarm_simulation_start(void)      { alarm_simulation_set(ALARM_TYPE_ON_AUTO); }
void event_proc_alarm_simulation_end(void)        { alarm_simulation_set(ALARM_TYPE_OFF_AUTO); }

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
  event_set(EVENT_ALARM_ALL            , &event_proc_alarm_all_start            , &event_proc_alarm_all_end);
  event_set(EVENT_ALARM_PERIMETER      , &event_proc_alarm_perimeter_start      , &event_proc_alarm_perimeter_end);
  event_set(EVENT_ALARM_PERIMETER_CHECK, &event_proc_alarm_perimeter_check_start, &event_proc_alarm_perimeter_check_end);
  event_set(EVENT_ALARM_VOLUME         , &event_proc_alarm_volume_start         , &event_proc_alarm_volume_end);
  event_set(EVENT_SIMU                 , &event_proc_alarm_simulation_start     , &event_proc_alarm_simulation_end);

  event_set(EVENT_POWER_0, &event_proc_wifi_start   , &event_proc_wifi_end);
  event_set(EVENT_POWER_1, &event_proc_eth_start    , &event_proc_eth_end);
  event_set(EVENT_POWER_2, &event_proc_power_2_start, &event_proc_power_2_end);
  event_set(EVENT_POWER_3, &event_proc_power_3_start, &event_proc_power_3_end);

  return 0;
}
