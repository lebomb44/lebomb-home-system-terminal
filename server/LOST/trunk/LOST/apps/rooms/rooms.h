#ifndef _ROOMS_H_
#define _ROOMS_H_

#include <stdio.h>
#include <sys/thread.h>
#include <pro/httpd.h>

__BEGIN_DECLS

typedef enum _ROOM_N_T
{
  ROOM_C1 = 0,   /* Marine */
  ROOM_C2,       /* M&M */
  ROOM_C3,       /* Amis */
  ROOM_C4,       /* Dressing */
  ROOM_COMBLES,  /* Combles */
  ROOM_BUREAU,   /* Bureau */
  ROOM_SALON,    /* Salon */
  ROOM_CUISINE,  /* Cuisine */
  ROOM_COULOIR,  /* Couloir */
  ROOM_SALON2,   /* Salon2 */
  ROOM_MAX
} ROOM_N_T;

#define ROOM_LIGHT_MAX 10
#define ROOM_SHUTTER_MAX 10
#define ROOM_HEATER_MAX 10
#define ROOM_ELEC_MAX 10
#define ROOM_IR_DATA_NB 10
#define ROOM_RF_DATA_NB 10

#define ROOM_SHUTTER_UP 255
#define ROOM_SHUTTER_STOP 0
#define ROOM_SHUTTER_DOWN 1

extern uint8_t rooms_init(void);

extern uint8_t room_type_get              (ROOM_N_T room);
extern uint8_t room_version_get           (ROOM_N_T room);
extern uint8_t room_addr_get              (ROOM_N_T room);

extern uint8_t room_error_status_get      (ROOM_N_T room);
extern uint8_t rooms_error_status_get     (ROOM_N_T* room);

extern uint8_t room_temp_value_get        (ROOM_N_T room);
extern uint8_t rooms_temp_max_value_get   (ROOM_N_T* room);
extern uint8_t room_temp_max_th_get       (ROOM_N_T room);
extern uint8_t room_temp_max_control_get  (ROOM_N_T room);
extern uint8_t room_temp_max_trig_get     (ROOM_N_T room);
extern uint8_t rooms_temp_max_trig_get    (ROOM_N_T* room);
extern uint8_t rooms_temp_min_value_get   (ROOM_N_T* room);
extern uint8_t room_temp_min_th_get       (ROOM_N_T room);
extern uint8_t room_temp_min_control_get  (ROOM_N_T room);
extern uint8_t room_temp_min_trig_get     (ROOM_N_T room);
extern uint8_t rooms_temp_min_trig_get    (ROOM_N_T* room);

extern uint8_t room_hum_status_get        (ROOM_N_T room);
extern uint8_t rooms_hum_status_get       (ROOM_N_T* room);
extern uint8_t room_hum_control_get       (ROOM_N_T room);
extern uint8_t room_hum_trig_get          (ROOM_N_T room);
extern uint8_t rooms_hum_trig_get         (ROOM_N_T* room);

extern uint8_t room_smoke_status_get      (ROOM_N_T room);
extern uint8_t rooms_smoke_status_get     (ROOM_N_T* room);
extern uint8_t room_smoke_control_get     (ROOM_N_T room);
extern uint8_t room_smoke_trig_get        (ROOM_N_T room);
extern uint8_t rooms_smoke_trig_get       (ROOM_N_T* room);

extern uint8_t room_perimeter_status_get  (ROOM_N_T room);
extern uint8_t rooms_perimeter_status_get (ROOM_N_T* room);
extern uint8_t room_perimeter_control_get (ROOM_N_T room);
extern uint8_t room_perimeter_trig_get    (ROOM_N_T room);

extern uint8_t room_volume_status_get     (ROOM_N_T room);
extern uint8_t rooms_volume_status_get    (ROOM_N_T* room);
extern uint8_t room_volume_control_get    (ROOM_N_T room);
extern uint8_t room_volume_trig_get       (ROOM_N_T room);

extern uint8_t room_simulation_status_get (ROOM_N_T room);
extern uint8_t rooms_simulation_status_get(ROOM_N_T* room);
extern uint8_t room_simulation_control_get(ROOM_N_T room);

extern uint8_t room_light_get             (ROOM_N_T room, uint8_t no);
extern uint8_t room_shutter_get           (ROOM_N_T room, uint8_t no);
extern uint8_t room_heater_get            (ROOM_N_T room, uint8_t no);
extern uint8_t room_elec_get              (ROOM_N_T room, uint8_t no);

extern void room_temp_max_th_set        (ROOM_N_T room, uint8_t th     );
extern void rooms_temp_max_th_set       (               uint8_t th     );
extern void room_temp_max_control_set   (ROOM_N_T room, uint8_t control);
extern void rooms_temp_max_control_set  (               uint8_t control);
extern void room_temp_max_trig_set      (ROOM_N_T room, uint8_t trig   );
extern void rooms_temp_max_trig_set     (               uint8_t trig   );
extern void room_temp_min_th_set        (ROOM_N_T room, uint8_t th     );
extern void rooms_temp_min_th_set       (               uint8_t th     );
extern void room_temp_min_control_set   (ROOM_N_T room, uint8_t control);
extern void rooms_temp_min_control_set  (               uint8_t control);
extern void room_temp_min_trig_set      (ROOM_N_T room, uint8_t trig   );
extern void rooms_temp_min_trig_set     (               uint8_t trig   );

extern void room_hum_control_set        (ROOM_N_T room, uint8_t control);
extern void rooms_hum_control_set       (               uint8_t control);
extern void room_hum_trig_set           (ROOM_N_T room, uint8_t trig   );
extern void rooms_hum_trig_set          (               uint8_t trig   );

extern void room_smoke_control_set      (ROOM_N_T room, uint8_t control);
extern void rooms_smoke_control_set     (               uint8_t control);
extern void room_smoke_trig_set         (ROOM_N_T room, uint8_t trig   );
extern void rooms_smoke_trig_set        (               uint8_t trig   );

extern void room_perimeter_control_set  (ROOM_N_T room, uint8_t control);
extern void rooms_perimeter_control_set (               uint8_t control);
extern void room_perimeter_trig_set     (ROOM_N_T room, uint8_t trig   );
extern void rooms_perimeter_trig_set    (               uint8_t trig   );
extern uint8_t rooms_perimeter_trig_get (ROOM_N_T* room);

extern void room_volume_control_set     (ROOM_N_T room, uint8_t control);
extern void rooms_volume_control_set    (               uint8_t control);
extern void room_volume_trig_set        (ROOM_N_T room, uint8_t trig   );
extern void rooms_volume_trig_set       (               uint8_t trig   );
extern uint8_t rooms_volume_trig_get    (ROOM_N_T* room);

extern void room_simulation_control_set (ROOM_N_T room, uint8_t control);
extern void rooms_simulation_control_set(               uint8_t control);

extern void room_light_set              (ROOM_N_T room, uint8_t no, uint8_t value);
extern void rooms_light_set             (               uint8_t no, uint8_t value);
extern void room_shutter_set            (ROOM_N_T room, uint8_t no, uint8_t value);
extern void rooms_shutter_set           (               uint8_t no, uint8_t value);
extern void room_shutters_set           (ROOM_N_T room,             uint8_t value);
extern void rooms_shutters_set          (                           uint8_t value);
extern void room_heater_set             (ROOM_N_T room, uint8_t no, uint8_t value);
extern void rooms_heater_set            (               uint8_t no, uint8_t value);
extern void room_elec_set               (ROOM_N_T room, uint8_t no, uint8_t value);
extern void rooms_elec_set              (               uint8_t no, uint8_t value);

extern void RoomD(void *arg) __attribute__ ((noreturn));
extern int rooms_form(FILE * stream, REQUEST * req);
extern int rooms_xml_get(FILE * stream);

__END_DECLS

#endif
