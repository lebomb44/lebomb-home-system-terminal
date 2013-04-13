#ifndef _NODE_REMOTE_CONFIG_H_
#define _NODE_REMOTE_CONFIG_H_

typedef enum _EVENT_T
{
  EVENT_SHUTTERS_ALL = 0,
  EVENT_SHUTTERS_UPSTAIRS,
  EVENT_SHUTTERS_DOWNSTAIRS,
  EVENT_SHUTTERS_MARINE,
  EVENT_SHUTTERS_MM,
  EVENT_SHUTTERS_FRIENDS,
  EVENT_SHUTTERS_DRESSING,
  EVENT_ALARM_ALL,
  EVENT_ALARM_PERIMETER,
  EVENT_ALARM_VOLUME,
  EVENT_SIMU,
  EVENT_POWER_0,
  EVENT_POWER_1,
  EVENT_POWER_2,
  EVENT_POWER_3,
  EVENT_ALARM_PERIMETER_CHECK,
  EVENT_MAX
} EVENT_T;

/* Global Remote Control */
#ifdef NODE_REMOTE_CONFIG_global
#define NODE_REMOTE_BUTTON1_ON_CMD   EVENT_SHUTTERS_ALL
#define NODE_REMOTE_BUTTON1_ON_DATA  1
#define NODE_REMOTE_BUTTON1_OFF_CMD  EVENT_SHUTTERS_ALL
#define NODE_REMOTE_BUTTON1_OFF_DATA 0
#define NODE_REMOTE_BUTTON2_ON_CMD   EVENT_SHUTTERS_DOWNSTAIRS
#define NODE_REMOTE_BUTTON2_ON_DATA  1
#define NODE_REMOTE_BUTTON2_OFF_CMD  EVENT_SHUTTERS_DOWNSTAIRS
#define NODE_REMOTE_BUTTON2_OFF_DATA 0
#define NODE_REMOTE_BUTTON3_ON_CMD   EVENT_POWER_1
#define NODE_REMOTE_BUTTON3_ON_DATA  1
#define NODE_REMOTE_BUTTON3_OFF_CMD  EVENT_POWER_1
#define NODE_REMOTE_BUTTON3_OFF_DATA 0
#define NODE_REMOTE_BUTTON4_ON_CMD   EVENT_POWER_0
#define NODE_REMOTE_BUTTON4_ON_DATA  1
#define NODE_REMOTE_BUTTON4_OFF_CMD  EVENT_POWER_0
#define NODE_REMOTE_BUTTON4_OFF_DATA 0
#endif

/* Room Remote Control */
#ifdef NODE_REMOTE_CONFIG_c1
#define NODE_REMOTE_BUTTON1_ON_CMD   EVENT_SHUTTERS_MM
#define NODE_REMOTE_BUTTON1_ON_DATA  1
#define NODE_REMOTE_BUTTON1_OFF_CMD  EVENT_SHUTTERS_MM
#define NODE_REMOTE_BUTTON1_OFF_DATA 0
#define NODE_REMOTE_BUTTON2_ON_CMD   EVENT_SHUTTERS_MARINE
#define NODE_REMOTE_BUTTON2_ON_DATA  1
#define NODE_REMOTE_BUTTON2_OFF_CMD  EVENT_SHUTTERS_MARINE
#define NODE_REMOTE_BUTTON2_OFF_DATA 0
#define NODE_REMOTE_BUTTON3_ON_CMD   EVENT_SHUTTERS_UPSTAIRS
#define NODE_REMOTE_BUTTON3_ON_DATA  1
#define NODE_REMOTE_BUTTON3_OFF_CMD  EVENT_SHUTTERS_UPSTAIRS
#define NODE_REMOTE_BUTTON3_OFF_DATA 0
#define NODE_REMOTE_BUTTON4_ON_CMD   EVENT_SHUTTERS_DOWNSTAIRS
#define NODE_REMOTE_BUTTON4_ON_DATA  1
#define NODE_REMOTE_BUTTON4_OFF_CMD  EVENT_SHUTTERS_DOWNSTAIRS
#define NODE_REMOTE_BUTTON4_OFF_DATA 0
#endif

/* Alarm Remote Control */
#ifdef NODE_REMOTE_CONFIG_alarm
#define NODE_REMOTE_BUTTON1_ON_CMD   EVENT_ALARM_PERIMETER
#define NODE_REMOTE_BUTTON1_ON_DATA  1
#define NODE_REMOTE_BUTTON1_OFF_CMD  EVENT_ALARM_PERIMETER
#define NODE_REMOTE_BUTTON1_OFF_DATA 0
#define NODE_REMOTE_BUTTON2_ON_CMD   EVENT_ALARM_PERIMETER
#define NODE_REMOTE_BUTTON2_ON_DATA  1
#define NODE_REMOTE_BUTTON2_OFF_CMD  EVENT_ALARM_PERIMETER
#define NODE_REMOTE_BUTTON2_OFF_DATA 0
#define NODE_REMOTE_BUTTON3_ON_CMD   EVENT_ALARM_VOLUME
#define NODE_REMOTE_BUTTON3_ON_DATA  1
#define NODE_REMOTE_BUTTON3_OFF_CMD  EVENT_ALARM_VOLUME
#define NODE_REMOTE_BUTTON3_OFF_DATA 0
#define NODE_REMOTE_BUTTON4_ON_CMD   EVENT_ALARM_VOLUME
#define NODE_REMOTE_BUTTON4_ON_DATA  1
#define NODE_REMOTE_BUTTON4_OFF_CMD  EVENT_ALARM_VOLUME
#define NODE_REMOTE_BUTTON4_OFF_DATA 0
#endif

#endif
