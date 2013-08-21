#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>
#include <dev/reset.h>

#include <pro/httpd.h>

#include "../../devices/i2c.h"
#include "../../devices/adc.h"
#include "../../services/web.h"
#include "rooms.h"

/**************************************************/
/* Type                  : ROOM                   */
/* Version               : v1.0                   */
/* Adresse               : @                      */
/* Status                :                        */
/**************************************************/

#define ROOM_SLA 10

enum ROOM_REG_T
{
  ROOM_REG_TYPE = 0,
  ROOM_REG_VERSION,
  ROOM_REG_ADRESS,

  ROOM_REG_TEMP_VALUE,
  ROOM_REG_TEMP_MAX_TH,
  ROOM_REG_TEMP_MAX_CONTROL,
  ROOM_REG_TEMP_MAX_TRIG,
  ROOM_REG_TEMP_MIN_TH,
  ROOM_REG_TEMP_MIN_CONTROL,
  ROOM_REG_TEMP_MIN_TRIG,

  ROOM_REG_HUM_STATUS,
  ROOM_REG_HUM_CONTROL,
  ROOM_REG_HUM_TRIG,

  ROOM_REG_SMOKE_STATUS,
  ROOM_REG_SMOKE_CONTROL,
  ROOM_REG_SMOKE_TRIG,

  ROOM_REG_PERI_STATUS,
  ROOM_REG_PERI_CONTROL,
  ROOM_REG_PERI_TRIG,

  ROOM_REG_VOL_STATUS,
  ROOM_REG_VOL_CONTROL,
  ROOM_REG_VOL_TRIG,

  ROOM_REG_SIM_STATUS,
  ROOM_REG_SIM_CONTROL,
  ROOM_REG_SIM_TRIG,

  ROOM_REG_LIGHT,
  ROOM_REG_SHUTTER = ROOM_REG_LIGHT   + ROOM_LIGHT_MAX,
  ROOM_REG_HEATER  = ROOM_REG_SHUTTER + ROOM_SHUTTER_MAX,
  ROOM_REG_ELEC    = ROOM_REG_HEATER  + ROOM_HEATER_MAX,

  ROOM_REG_IR_TX_TYPE = ROOM_REG_ELEC + ROOM_ELEC_MAX,
  ROOM_REG_IR_TX_SRC_ADDR,
  ROOM_REG_IR_TX_DEST_ADDR,
  ROOM_REG_IR_TX_CMD,
  ROOM_REG_IR_TX_CTRL,
  ROOM_REG_IR_TX_DATA,
  ROOM_REG_IR_TX_ACK = ROOM_REG_IR_TX_DATA + ROOM_IR_DATA_NB,

  ROOM_REG_IR_RX_TYPE,
  ROOM_REG_IR_RX_SRC_ADDR,
  ROOM_REG_IR_RX_DEST_ADDR,
  ROOM_REG_IR_RX_CMD,
  ROOM_REG_IR_RX_CTRL,
  ROOM_REG_IR_RX_DATA,
  ROOM_REG_IR_RX_ACK = ROOM_REG_IR_RX_DATA + ROOM_IR_DATA_NB,

  ROOM_REG_RF_TX_TYPE,
  ROOM_REG_RF_TX_SRC_ADDR,
  ROOM_REG_RF_TX_DEST_ADDR,
  ROOM_REG_RF_TX_CMD,
  ROOM_REG_RF_TX_CTRL,
  ROOM_REG_RF_TX_DATA,
  ROOM_REG_RF_TX_ACK = ROOM_REG_RF_TX_DATA + ROOM_RF_DATA_NB,

  ROOM_REG_RF_RX_TYPE,
  ROOM_REG_RF_RX_SRC_ADDR,
  ROOM_REG_RF_RX_DEST_ADDR,
  ROOM_REG_RF_RX_CMD,
  ROOM_REG_RF_RX_CTRL,
  ROOM_REG_RF_RX_DATA,
  ROOM_REG_RF_RX_ACK = ROOM_REG_RF_RX_DATA + ROOM_RF_DATA_NB,

  ROOM_REG_CLIM,

  ROOM_REG_MAX
};

uint8_t room_list[ROOM_MAX][ROOM_REG_MAX];
uint8_t room_error[ROOM_MAX];
const char* room_name[ROOM_MAX] = ROOM_NAMES;

uint8_t rooms_init(void)
{
  uint8_t i = 0;
  uint8_t j = 0;

  for(i=0; i<ROOM_MAX; i++)
  {
    room_error[i] = 0;
    for(j=0; j<ROOM_REG_MAX; j++)
    {
      room_list[i][j] = 0;
    }
  }

  NutThreadCreate("RoomD"  , RoomD  , 0, 512);
  NutRegisterCgi("rooms.cgi", rooms_form);

  return 0;
}

const char* room_name_get(ROOM_N_T room)
{
  if(ROOM_MAX > room) { return room_name[room]; }
  else { return NULL; }
}

uint8_t room_type_get              (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_TYPE            ]; } else { return 0; } }
uint8_t room_version_get           (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_VERSION         ]; } else { return 0; } }
uint8_t room_adress_get            (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_ADRESS          ]; } else { return 0; } }

uint8_t room_error_status_get      (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_error[room]; } else { return 0; } }
uint8_t rooms_error_status_get     (ROOM_N_T* room) { uint8_t i = 0; uint8_t error = 0; for(i=0; i<ROOM_MAX; i++) { error = room_error_status_get(i); if(error) { if(room != NULL) { *room = i; } return error; } } return 0; }

uint8_t room_temp_value_get        (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_TEMP_VALUE      ]; } else { return 0; } }
uint8_t rooms_temp_max_value_get   (ROOM_N_T* room) { uint8_t i = 0; uint8_t temp = 0; uint8_t temp_max = 0; for(i=0; i<ROOM_MAX; i++) { temp = room_temp_value_get(i); if(temp > temp_max) { temp_max = temp; if(room != NULL) { *room = i; } } } return temp_max; }
uint8_t room_temp_max_th_get       (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_TEMP_MAX_TH     ]; } else { return 0; } }
uint8_t room_temp_max_control_get  (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_TEMP_MAX_CONTROL]; } else { return 0; } }
uint8_t room_temp_max_trig_get     (ROOM_N_T room ) { uint8_t trig = 0; if(ROOM_MAX > room) { trig = room_list[room][ROOM_REG_TEMP_MAX_TRIG]; if(trig & 0xFE) { return 0; } else { return trig; } } else { return 0; } }
uint8_t rooms_temp_max_trig_get    (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_temp_max_trig_get(i)) { if(room != NULL) { *room = i; } return 1; } } return 0; }
uint8_t rooms_temp_min_value_get   (ROOM_N_T* room) { uint8_t i = 0; uint8_t temp = 0; uint8_t temp_min = 0xFF; for(i=0; i<ROOM_MAX; i++) { temp = room_temp_value_get(i); if(temp < temp_min) { temp_min = temp; if(room != NULL) { *room = i; } } } return temp_min; }
uint8_t room_temp_min_th_get       (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_TEMP_MIN_TH     ]; } else { return 0; } }
uint8_t room_temp_min_control_get  (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_TEMP_MIN_CONTROL]; } else { return 0; } }
uint8_t room_temp_min_trig_get     (ROOM_N_T room ) { uint8_t trig = 0; if(ROOM_MAX > room) { trig = room_list[room][ROOM_REG_TEMP_MIN_TRIG]; if(trig & 0xFE) { return 0; } else { return trig; } } else { return 0; } }
uint8_t rooms_temp_min_trig_get    (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_temp_min_trig_get(i)) { if(room != NULL) { *room = i; } return 1; } } return 0; }

uint8_t room_hum_status_get        (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_HUM_STATUS      ]; } else { return 0; } }
uint8_t rooms_hum_status_get       (ROOM_N_T* room) { uint8_t i = 0;; for(i=0; i<ROOM_MAX; i++) { if(room_hum_status_get(i)) { if(room != NULL) { *room = i; } return 1; } } return 0; }
uint8_t room_hum_control_get       (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_HUM_CONTROL     ]; } else { return 0; } }
uint8_t room_hum_trig_get          (ROOM_N_T room ) { uint8_t trig = 0; if(ROOM_MAX > room) { trig = room_list[room][ROOM_REG_HUM_TRIG]; if(trig & 0xFE) { return 0; } else { return trig; } } else { return 0; } }
uint8_t rooms_hum_trig_get         (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_hum_trig_get(i)) { if(room != NULL) { *room = i; } return 1; } } return 0; }

uint8_t room_smoke_status_get      (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_SMOKE_STATUS    ]; } else { return 0; } }
uint8_t rooms_smoke_status_get     (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_smoke_status_get(i)) { if(room != NULL) { *room = i; } return 1; } } return 0; }
uint8_t room_smoke_control_get     (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_SMOKE_CONTROL   ]; } else { return 0; } }
uint8_t room_smoke_trig_get        (ROOM_N_T room ) { uint8_t trig = 0; if(ROOM_MAX > room) { trig = room_list[room][ROOM_REG_SMOKE_TRIG]; if(trig & 0xFE) { return 0; } else { return trig; } } else { return 0; } }
uint8_t rooms_smoke_trig_get       (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_smoke_trig_get(i)) { if(room != NULL) { *room = i; } return 1; } } return 0; }

uint8_t room_perimeter_status_get  (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_PERI_STATUS     ]; } else { return 0; } }
uint8_t rooms_perimeter_status_get (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_perimeter_status_get(i) & 0x01 /* FIXME All lines must be checked */ ) { if(room != NULL) { *room = i; } return (room_perimeter_status_get(i) & 0x01); } } return 0; }
uint8_t room_perimeter_control_get (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_PERI_CONTROL    ]; } else { return 0; } }
uint8_t room_perimeter_trig_get    (ROOM_N_T room ) { uint8_t trig = 0; if(ROOM_MAX > room) { trig = room_list[room][ROOM_REG_PERI_TRIG]; if(trig & 0xF8) { return 0; } else { return trig; } } else { return 0; } }
uint8_t rooms_perimeter_trig_get   (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_perimeter_trig_get(i)) { if(room != NULL) { *room = i; } return room_perimeter_trig_get(i); } } return 0; }

uint8_t room_volume_status_get     (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_VOL_STATUS      ]; } else { return 0; } }
uint8_t rooms_volume_status_get    (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_volume_status_get(i)) { if(room != NULL) { *room = i; } return room_volume_status_get(i); } } return 0; }
uint8_t room_volume_control_get    (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_VOL_CONTROL     ]; } else { return 0; } }
uint8_t room_volume_trig_get       (ROOM_N_T room ) { uint8_t trig = 0; if(ROOM_MAX > room) { trig = room_list[room][ROOM_REG_VOL_TRIG]; if(trig & 0xFE) { return 0; } else { return trig; } } else { return 0; } }
uint8_t rooms_volume_trig_get      (ROOM_N_T* room) { uint8_t i = 0; for(i=0; i<ROOM_MAX; i++) { if(room_volume_trig_get(i)) { if(room != NULL) { *room = i; } return room_volume_trig_get(i); } } return 0; }

uint8_t room_simulation_status_get (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_SIM_STATUS      ]; } else { return 0; } }
uint8_t rooms_simulation_status_get(ROOM_N_T* room) { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_simulation_status_get(i)) { if(room != NULL) { *room = i; } return room_simulation_status_get(i); } } return 0; }
uint8_t room_simulation_control_get(ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_SIM_CONTROL     ]; } else { return 0; } }

uint8_t room_clim_get              (ROOM_N_T room ) { if(ROOM_MAX > room) { return room_list[room][ROOM_REG_CLIM            ]; } else { return 0; } }

uint8_t room_light_get             (ROOM_N_T room, uint8_t no) { if((ROOM_MAX > room) && (no < ROOM_LIGHT_MAX  )) { return room_list[room][ROOM_REG_LIGHT   + no]; } else { return 0; } }
uint8_t room_shutter_get           (ROOM_N_T room, uint8_t no) { if((ROOM_MAX > room) && (no < ROOM_SHUTTER_MAX)) { return room_list[room][ROOM_REG_SHUTTER + no]; } else { return 0; } }
uint8_t room_heater_get            (ROOM_N_T room, uint8_t no) { if((ROOM_MAX > room) && (no < ROOM_HEATER_MAX )) { return room_list[room][ROOM_REG_HEATER  + no]; } else { return 0; } }
uint8_t room_elec_get              (ROOM_N_T room, uint8_t no) { if((ROOM_MAX > room) && (no < ROOM_ELEC_MAX   )) { return room_list[room][ROOM_REG_ELEC    + no]; } else { return 0; } }

void room_temp_max_th_set        (ROOM_N_T room, uint8_t th     ) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MAX_TH     , 1, &th     ); } }
void rooms_temp_max_th_set       (               uint8_t th     ) {                                          i2c_broadcast_set(     ROOM_REG_TEMP_MAX_TH     , 1, &th     ); }
void room_temp_max_control_set   (ROOM_N_T room, uint8_t control) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MAX_CONTROL, 1, &control); } }
void rooms_temp_max_control_set  (               uint8_t control) {                                          i2c_broadcast_set(     ROOM_REG_TEMP_MAX_CONTROL, 1, &control); }
void room_temp_max_trig_set      (ROOM_N_T room, uint8_t trig   ) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MAX_TRIG   , 1, &trig   ); } }
void rooms_temp_max_trig_set     (               uint8_t trig   ) {                                          i2c_broadcast_set(     ROOM_REG_TEMP_MAX_TRIG   , 1, &trig   ); }
void room_temp_min_th_set        (ROOM_N_T room, uint8_t th     ) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MIN_TH     , 1, &th     ); } }
void rooms_temp_min_th_set       (               uint8_t th     ) {                                          i2c_broadcast_set(     ROOM_REG_TEMP_MIN_TH     , 1, &th     ); }
void room_temp_min_control_set   (ROOM_N_T room, uint8_t control) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MIN_CONTROL, 1, &control); } }
void rooms_temp_min_control_set  (               uint8_t control) {                                          i2c_broadcast_set(     ROOM_REG_TEMP_MIN_CONTROL, 1, &control); }
void room_temp_min_trig_set      (ROOM_N_T room, uint8_t trig   ) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MIN_TRIG   , 1, &trig   ); } }
void rooms_temp_min_trig_set     (               uint8_t trig   ) {                                          i2c_broadcast_set(     ROOM_REG_TEMP_MIN_TRIG   , 1, &trig   ); }

void room_hum_control_set        (ROOM_N_T room, uint8_t control) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_HUM_CONTROL     , 1, &control); } }
void rooms_hum_control_set       (               uint8_t control) {                                          i2c_broadcast_set(     ROOM_REG_HUM_CONTROL     , 1, &control); }
void room_hum_trig_set           (ROOM_N_T room, uint8_t trig   ) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_HUM_TRIG        , 1, &trig   ); } }
void rooms_hum_trig_set          (               uint8_t trig   ) {                                          i2c_broadcast_set(     ROOM_REG_HUM_TRIG        , 1, &trig   ); }

void room_smoke_control_set      (ROOM_N_T room, uint8_t control) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_SMOKE_CONTROL   , 1, &control); } }
void rooms_smoke_control_set     (               uint8_t control) {                                          i2c_broadcast_set(     ROOM_REG_SMOKE_CONTROL   , 1, &control); }
void room_smoke_trig_set         (ROOM_N_T room, uint8_t trig   ) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_SMOKE_TRIG      , 1, &trig   ); } }
void rooms_smoke_trig_set        (               uint8_t trig   ) {                                          i2c_broadcast_set(     ROOM_REG_SMOKE_TRIG      , 1, &trig   ); }

void room_perimeter_control_set  (ROOM_N_T room, uint8_t control) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_PERI_CONTROL    , 1, &control); } }
void rooms_perimeter_control_set (               uint8_t control) {                                          i2c_broadcast_set(     ROOM_REG_PERI_CONTROL    , 1, &control); }
void room_perimeter_trig_set     (ROOM_N_T room, uint8_t trig   ) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_PERI_TRIG       , 1, &trig   ); } }
void rooms_perimeter_trig_set    (               uint8_t trig   ) {                                          i2c_broadcast_set(     ROOM_REG_PERI_TRIG       , 1, &trig   ); }

void room_volume_control_set     (ROOM_N_T room, uint8_t control) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_VOL_CONTROL     , 1, &control); } }
void rooms_volume_control_set    (               uint8_t control) {                    i2c_broadcast_set(      ROOM_REG_VOL_CONTROL     , 1, &control); }
void room_volume_trig_set        (ROOM_N_T room, uint8_t trig   ) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_VOL_TRIG        , 1, &trig   ); } }
void rooms_volume_trig_set       (               uint8_t trig   ) {                                          i2c_broadcast_set(     ROOM_REG_VOL_TRIG        , 1, &trig   ); }

void room_simulation_control_set (ROOM_N_T room, uint8_t control) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_SIM_CONTROL     , 1, &control); } }
void rooms_simulation_control_set(               uint8_t control) {                                          i2c_broadcast_set(     ROOM_REG_SIM_CONTROL     , 1, &control); }

void room_ir_set (ROOM_N_T room, uint8_t type, uint8_t cmd0, uint8_t cmd1, uint8_t cmd2)
{
  uint8_t ir_buff[4] = {0};
  if(ROOM_MAX > room)
  {
    ir_buff[0] = type; ir_buff[1] = cmd0; ir_buff[2] = cmd1; ir_buff[3] = cmd2;
    room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_IR_TX_TYPE, 4, &ir_buff[0]);
  }
}
void rooms_ir_set(uint8_t type, uint8_t cmd0, uint8_t cmd1, uint8_t cmd2)
{
  uint8_t ir_buff[4] = {0};
  ir_buff[0] = type; ir_buff[1] = cmd0; ir_buff[2] = cmd1; ir_buff[3] = cmd2;
  i2c_broadcast_set(ROOM_REG_IR_TX_TYPE, 4, &ir_buff[0]);
}

void room_clim_set (ROOM_N_T room, uint8_t temp) { if(ROOM_MAX > room) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_CLIM, 1, &temp); } }
void rooms_clim_set(               uint8_t temp) {                                          i2c_broadcast_set(     ROOM_REG_CLIM, 1, &temp); }

void room_light_set              (ROOM_N_T room, uint8_t no, uint8_t value) { if((ROOM_MAX > room) && (no < ROOM_LIGHT_MAX  )) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_LIGHT   +no, 1, &value); } else { rooms_light_set(no, value); } }
void rooms_light_set             (               uint8_t no, uint8_t value) { if(                      no < ROOM_LIGHT_MAX   ) {                    i2c_broadcast_set(     ROOM_REG_LIGHT   +no, 1, &value); } }
void room_shutter_set            (ROOM_N_T room, uint8_t no, uint8_t value) { if(ROOM_MAX > room) { if(no < ROOM_SHUTTER_MAX ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_SHUTTER +no, 1, &value); } else { room_shutters_set(room, value); } } else { rooms_shutter_set(no, value); } }
void rooms_shutter_set           (               uint8_t no, uint8_t value) { uint8_t i = 0; for(i=0; i<ROOM_MAX;         i++) { room_shutter_set(i   , no, value); } }
void room_shutters_set           (ROOM_N_T room,             uint8_t value) { uint8_t i = 0; for(i=0; i<ROOM_SHUTTER_MAX; i++) { room_shutter_set(room, i , value); } }
void rooms_shutters_set          (                           uint8_t value) { uint8_t i = 0; for(i=0; i<ROOM_SHUTTER_MAX; i++) { rooms_shutter_set(     i , value); } }
void room_heater_set             (ROOM_N_T room, uint8_t no, uint8_t value) { if((ROOM_MAX > room) && (no < ROOM_HEATER_MAX )) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_HEATER  +no, 1, &value); } else { rooms_heater_set(no, value); } }
void rooms_heater_set            (               uint8_t no, uint8_t value) { if(                      no < ROOM_HEATER_MAX  ) {                    i2c_broadcast_set(     ROOM_REG_HEATER  +no, 1, &value); } }
void room_elec_set               (ROOM_N_T room, uint8_t no, uint8_t value) { if((ROOM_MAX > room) && (no < ROOM_ELEC_MAX   )) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_ELEC    +no, 1, &value); } else { rooms_elec_set(no, value); } }
void rooms_elec_set              (               uint8_t no, uint8_t value) { if(                      no < ROOM_ELEC_MAX    ) {                    i2c_broadcast_set(     ROOM_REG_ELEC    +no, 1, &value); } }

THREAD(RoomD, arg)
{
  uint8_t trig_reset = 0;
  uint8_t i = 0;

  arg = arg;
  NutThreadSetPriority(106);

  while(1)
  {
    /* Acquire all the rooms */
    for(i=0; i<ROOM_MAX; i++)
    {
      room_error[i] = i2c_get(ROOM_SLA+i, 0, ROOM_REG_MAX, &room_list[i][0]);
      NutSleep(1);
    }

    NutSleep(10000);
  }
}

int rooms_form(FILE * stream, REQUEST * req)
{
  char* room_s=0;
  unsigned int room=0;
  char* ir_type_s=0;
  char* ir_cmd0_s=0;
  char* ir_cmd1_s=0;
  char* ir_cmd2_s=0;
  char* clim_s=0;
  char* light_s=0;
  unsigned int light=0;
  char* shutter_s=0;
  unsigned int shutter=0;
  char* value_s=0;
  unsigned int heater=0;
  char* heater_s=0;
  unsigned int elec=0;
  char* elec_s=0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    room_s = NutHttpGetParameter(req, "room");
    if(room_s)
    {
      room = strtoul(room_s, NULL, 10);
      if(ROOM_MAX >= room)
      {
        ir_type_s = NutHttpGetParameter(req, "ir_type");
        clim_s    = NutHttpGetParameter(req, "clim");
        light_s   = NutHttpGetParameter(req, "light");
        shutter_s = NutHttpGetParameter(req, "shutter");
        heater_s  = NutHttpGetParameter(req, "heater");
        elec_s    = NutHttpGetParameter(req, "elec");
        value_s   = NutHttpGetParameter(req, "value");
        /* FIXME : Do you think that we need this debug commands for ever ? */
        if(ir_type_s)
        {
          ir_cmd0_s = NutHttpGetParameter(req, "ir_cmd0");
          ir_cmd1_s = NutHttpGetParameter(req, "ir_cmd1");
          ir_cmd2_s = NutHttpGetParameter(req, "ir_cmd2");
          if(ir_cmd0_s && ir_cmd1_s && ir_cmd2_s)
          {
            room_ir_set(room, strtoul(ir_type_s, NULL, 10), strtoul(ir_cmd0_s, NULL, 10), strtoul(ir_cmd1_s, NULL, 10), strtoul(ir_cmd2_s, NULL, 10));
          }
        }
        if(clim_s)
        {
          if('?' == value_s[0]) { fprintf(stream, "%d", room_clim_get(room)); }
          else
          {
            room_clim_set(room, strtoul(clim_s, NULL, 10));
          }
        }
        if(light_s && value_s)
        {
          light = strtoul(light_s, NULL, 10);
          if('?' == value_s[0]) { fprintf(stream, "%d", room_light_get(room, light)); }
          else
          {
            room_light_set(room, light, strtoul(value_s, NULL, 10));
          }
        }
        if(shutter_s && value_s)
        {
          shutter = strtoul(shutter_s, NULL, 10);
          if('?' == value_s[0]) { fprintf(stream, "%d", room_shutter_get(room, shutter)); }
          else
          {
            room_shutter_set(room, shutter, strtoul(value_s, NULL, 10));
          }
        }
        if(heater_s && value_s)
        {
          heater = strtoul(heater_s, NULL, 10);
          if('?' == value_s[0]) { fprintf(stream, "%d", room_heater_get(room, heater)); }
          else
          {
            room_heater_set(room, heater, strtoul(value_s, NULL, 10));
          }
        }
        if(elec_s && value_s)
        {
          elec = strtoul(elec_s, NULL, 10);
          if('?' == value_s[0]) { fprintf(stream, "%d", room_elec_get(room, elec)); }
          else
          {
            room_elec_set(room, elec, strtoul(value_s, NULL, 10));
          }
        }
      }
    }
    fflush(stream);
  }
  return 0;
}

int rooms_xml_get(FILE * stream)
{
  uint8_t i = 0;
  uint8_t j = 0;
  char room_xml[10];
  char arg_xml[20];

  for(i=0; i<ROOM_MAX; i++)
  {
    sprintf(room_xml, "Room%d", i);
    fprintf_XML_elt_header(room_xml, stream);
    fprintf_XML_elt_int("Error_Trig"     , room_error_status_get(i)      , stream);
    fprintf_XML_elt_int("Type"           , room_type_get(i)              , stream);
    fprintf_XML_elt_int("Version"        , room_version_get(i)           , stream);
    fprintf_XML_elt_int("Adress"         , room_adress_get(i)            , stream);

    fprintf_XML_elt_int("Temp_Max"       , room_temp_value_get(i)        , stream);
    fprintf_XML_elt_int("Temp_Max_Th"    , room_temp_max_th_get(i)       , stream);
    fprintf_XML_elt_int("Temp_Max_Ctrl"  , room_temp_max_control_get(i)  , stream);
    fprintf_XML_elt_int("Temp_Max_Trig"  , room_temp_max_trig_get(i)     , stream);
    fprintf_XML_elt_int("Temp_Min"       , room_temp_value_get(i)        , stream);
    fprintf_XML_elt_int("Temp_Min_Th"    , room_temp_min_th_get(i)       , stream);
    fprintf_XML_elt_int("Temp_Min_Ctrl"  , room_temp_min_control_get(i)  , stream);
    fprintf_XML_elt_int("Temp_Min_Trig"  , room_temp_min_trig_get(i)     , stream);

    fprintf_XML_elt_int("Hum"            , room_hum_status_get(i)        , stream);
    fprintf_XML_elt_int("Hum_Ctrl"       , room_hum_control_get(i)       , stream);
    fprintf_XML_elt_int("Hum_Trig"       , room_hum_trig_get(i)          , stream);

    fprintf_XML_elt_int("Smoke"          , room_smoke_status_get(i)      , stream);
    fprintf_XML_elt_int("Smoke_Ctrl"     , room_smoke_control_get(i)     , stream);
    fprintf_XML_elt_int("Smoke_Trig"     , room_smoke_trig_get(i)        , stream);

    fprintf_XML_elt_int("Perimeter"      , room_perimeter_status_get(i)  , stream);
    fprintf_XML_elt_int("Perimeter_Ctrl" , room_perimeter_control_get(i) , stream);
    fprintf_XML_elt_int("Perimeter_Trig" , room_perimeter_trig_get(i)    , stream);

    fprintf_XML_elt_int("Volume"         , room_volume_status_get(i)     , stream);
    fprintf_XML_elt_int("Volume_Ctrl"    , room_volume_control_get(i)    , stream);
    fprintf_XML_elt_int("Volume_Trig"    , room_volume_trig_get(i)       , stream);

    fprintf_XML_elt_int("Simulation"     , room_simulation_status_get(i) , stream);
    fprintf_XML_elt_int("Simulation_Ctrl", room_simulation_control_get(i), stream);

    fprintf_XML_elt_int("Clim_Cmd"       , room_clim_get(i)              , stream);

    for(j=0; j<ROOM_LIGHT_MAX; j++)
    {
      sprintf(arg_xml, "Light%d", j);
      fprintf_XML_elt_int(arg_xml, room_light_get(i, j), stream);
    }
    for(j=0; j<ROOM_SHUTTER_MAX; j++)
    {
      sprintf(arg_xml, "Shutter%d", j);
      fprintf_XML_elt_int(arg_xml, room_shutter_get(i, j), stream);
    }
    for(j=0; j<ROOM_HEATER_MAX; j++)
    {
      sprintf(arg_xml, "Heater%d", j);
      fprintf_XML_elt_int(arg_xml, room_heater_get(i, j), stream);
    }
    for(j=0; j<ROOM_ELEC_MAX; j++)
    {
      sprintf(arg_xml, "Elec%d", j);
      fprintf_XML_elt_int(arg_xml, room_elec_get(i, j), stream);
    }
    fprintf_XML_elt_trailer(room_xml, stream);
  }
  return 0;
}
