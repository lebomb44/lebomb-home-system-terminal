#ifndef _ROOMS_H_
#define _ROOMS_H_

#include <stdio.h>
#include <pro/httpd.h>

__BEGIN_DECLS

typedef enum _ROOM_N_T
{
  ROOM_SALON = 0,
  ROOM_BUREAU,
  ROOM_TERRASSE,
  ROOM_C1,
  ROOM_C2,
  ROOM_C3,
  ROOM_C4,
  ROOM_WC,
  ROOM_MAX
} ROOM_N_T;


extern uint8_t rooms_init(void);

extern uint8_t room_type_get              (ROOM_N_T room);
extern uint8_t room_version_get           (ROOM_N_T room);
extern uint8_t room_addr_get              (ROOM_N_T room);

extern uint8_t room_error_status_get      (ROOM_N_T room);
extern uint8_t rooms_error_status_get     (void);

extern uint8_t room_temp_value_get        (ROOM_N_T room);
extern uint8_t room_temp_max_th_get       (ROOM_N_T room);
extern uint8_t room_temp_max_control_get  (ROOM_N_T room);
extern uint8_t room_temp_max_trig_get     (ROOM_N_T room);
extern uint8_t rooms_temp_max_trig_get    (void);
extern uint8_t room_temp_min_th_get       (ROOM_N_T room);
extern uint8_t room_temp_min_control_get  (ROOM_N_T room);
extern uint8_t room_temp_min_trig_get     (ROOM_N_T room);
extern uint8_t rooms_temp_min_trig_get    (void);

extern uint8_t room_hum_status_get        (ROOM_N_T room);
extern uint8_t rooms_hum_status_get       (void);
extern uint8_t room_hum_control_get       (ROOM_N_T room);
extern uint8_t room_hum_trig_get          (ROOM_N_T room);
extern uint8_t rooms_hum_trig_get         (void);

extern uint8_t room_smoke_status_get      (ROOM_N_T room);
extern uint8_t rooms_smoke_status_get     (void);
extern uint8_t room_smoke_control_get     (ROOM_N_T room);
extern uint8_t room_smoke_trig_get        (ROOM_N_T room);
extern uint8_t rooms_smoke_trig_get       (void);

extern uint8_t room_perimeter_status_get  (ROOM_N_T room);
extern uint8_t rooms_perimeter_status_get (void);
extern uint8_t room_perimeter_control_get (ROOM_N_T room);
extern uint8_t room_perimeter_trig_get    (ROOM_N_T room);

extern uint8_t room_volume_status_get     (ROOM_N_T room);
extern uint8_t rooms_volume_status_get    (void);
extern uint8_t room_volume_control_get    (ROOM_N_T room);
extern uint8_t room_volume_trig_get       (ROOM_N_T room);

extern uint8_t room_simulation_status_get (ROOM_N_T room);
extern uint8_t rooms_simulation_status_get(void);
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
extern uint8_t rooms_perimeter_trig_get (void);

extern void room_volume_control_set     (ROOM_N_T room, uint8_t control);
extern void rooms_volume_control_set    (               uint8_t control);
extern void room_volume_trig_set        (ROOM_N_T room, uint8_t trig   );
extern void rooms_volume_trig_set       (               uint8_t trig   );
extern uint8_t rooms_volume_trig_get    (void);

extern void room_simulation_control_set (ROOM_N_T room, uint8_t control);
extern void rooms_simulation_control_set(               uint8_t control);

extern void room_light_set              (ROOM_N_T room, uint8_t no, uint8_t value);
extern void rooms_light_set             (               uint8_t no, uint8_t value);
extern void room_shutter_set            (ROOM_N_T room, uint8_t no, uint8_t value);
extern void rooms_shutter_set           (               uint8_t no, uint8_t value);
extern void room_heater_set             (ROOM_N_T room, uint8_t no, uint8_t value);
extern void rooms_heater_set            (               uint8_t no, uint8_t value);
extern void room_elec_set               (ROOM_N_T room, uint8_t no, uint8_t value);
extern void rooms_elec_set              (               uint8_t no, uint8_t value);

extern uint8_t rooms_temp_max_value_get(void);
extern uint8_t rooms_temp_min_value_get(void);

extern void RoomD(void *arg) __attribute__ ((noreturn));
extern int rooms_form(FILE * stream, REQUEST * req);
extern int rooms_xml_get(FILE * stream);

__END_DECLS

#endif
