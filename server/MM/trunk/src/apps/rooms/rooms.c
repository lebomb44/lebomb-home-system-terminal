#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../devices/i2c.h"
#include "../../devices/adc.h"
//#include "../../services/http.h"
#include "../../services/web.h"
#include "rooms.h"

/**************************************************/
/* Type                  : ROOM                   */
/* Version               : v1.0                   */
/* Adresse               : @                      */
/* Status                :                        */
/**************************************************/

#define ROOM_SLA 2
#define ROOM_LIGHT_MAX 10
#define ROOM_SHUTTER_MAX 10
#define ROOM_HEATER_MAX 10
#define ROOM_ELEC_MAX 10

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

  ROOM_REG_IR_TYPE,
  ROOM_REG_IR_CMD0,
  ROOM_REG_IR_CMD1,

  ROOM_REG_LIGHT,
  ROOM_REG_SHUTTER = ROOM_REG_LIGHT   + ROOM_LIGHT_MAX,
  ROOM_REG_HEATER  = ROOM_REG_SHUTTER + ROOM_SHUTTER_MAX,
  ROOM_REG_ELEC    = ROOM_REG_HEATER  + ROOM_HEATER_MAX,
  ROOM_REG_MAX     = ROOM_REG_ELEC    + ROOM_ELEC_MAX
};

uint8_t room_list[ROOM_MAX][ROOM_REG_MAX];
uint8_t room_error[ROOM_MAX];

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

uint8_t room_type_get              (ROOM_N_T room) { return room_list[room][ROOM_REG_TYPE            ]; }
uint8_t room_version_get           (ROOM_N_T room) { return room_list[room][ROOM_REG_VERSION         ]; }
uint8_t room_adress_get            (ROOM_N_T room) { return room_list[room][ROOM_REG_ADRESS          ]; }

uint8_t room_error_status_get      (ROOM_N_T room) { return room_error[room]; }
uint8_t rooms_error_status_get     (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_error_status_get(i)     ) { return 1; } } return 0; }

uint8_t room_temp_value_get        (ROOM_N_T room) { return room_list[room][ROOM_REG_TEMP_VALUE      ]; }
uint8_t room_temp_max_th_get       (ROOM_N_T room) { return room_list[room][ROOM_REG_TEMP_MAX_TH     ]; }
uint8_t room_temp_max_control_get  (ROOM_N_T room) { return room_list[room][ROOM_REG_TEMP_MAX_CONTROL]; }
uint8_t room_temp_max_trig_get     (ROOM_N_T room) { return room_list[room][ROOM_REG_TEMP_MAX_TRIG   ]; }
uint8_t rooms_temp_max_trig_get    (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_temp_max_trig_get(i)    ) { return 1; } } return 0; }
uint8_t room_temp_min_th_get       (ROOM_N_T room) { return room_list[room][ROOM_REG_TEMP_MIN_TH     ]; }
uint8_t room_temp_min_control_get  (ROOM_N_T room) { return room_list[room][ROOM_REG_TEMP_MIN_CONTROL]; }
uint8_t room_temp_min_trig_get     (ROOM_N_T room) { return room_list[room][ROOM_REG_TEMP_MIN_TRIG   ]; }
uint8_t rooms_temp_min_trig_get    (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_temp_min_trig_get(i)    ) { return 1; } } return 0; }

uint8_t room_hum_status_get        (ROOM_N_T room) { return room_list[room][ROOM_REG_HUM_STATUS      ]; }
uint8_t rooms_hum_status_get       (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_hum_status_get(i)       ) { return 1; } } return 0; }
uint8_t room_hum_control_get       (ROOM_N_T room) { return room_list[room][ROOM_REG_HUM_CONTROL     ]; }
uint8_t room_hum_trig_get          (ROOM_N_T room) { return room_list[room][ROOM_REG_HUM_TRIG        ]; }
uint8_t rooms_hum_trig_get         (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_hum_trig_get(i)         ) { return 1; } } return 0; }

uint8_t room_smoke_status_get      (ROOM_N_T room) { return room_list[room][ROOM_REG_SMOKE_STATUS    ]; }
uint8_t rooms_smoke_status_get     (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_smoke_status_get(i)     ) { return 1; } } return 0; }
uint8_t room_smoke_control_get     (ROOM_N_T room) { return room_list[room][ROOM_REG_SMOKE_CONTROL   ]; }
uint8_t room_smoke_trig_get        (ROOM_N_T room) { return room_list[room][ROOM_REG_SMOKE_TRIG      ]; }
uint8_t rooms_smoke_trig_get       (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_smoke_trig_get(i)       ) { return 1; } } return 0; }

uint8_t room_perimeter_status_get  (ROOM_N_T room) { return room_list[room][ROOM_REG_PERI_STATUS     ]; }
uint8_t rooms_perimeter_status_get (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_perimeter_status_get(i) ) { return 1; } } return 0; }
uint8_t room_perimeter_control_get (ROOM_N_T room) { return room_list[room][ROOM_REG_PERI_CONTROL    ]; }
uint8_t room_perimeter_trig_get    (ROOM_N_T room) { return room_list[room][ROOM_REG_PERI_TRIG       ]; }
uint8_t rooms_perimeter_trig_get   (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_perimeter_trig_get(i)   ) { return 1; } } return 0; }

uint8_t room_volume_status_get     (ROOM_N_T room) { return room_list[room][ROOM_REG_VOL_STATUS      ]; }
uint8_t rooms_volume_status_get    (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_volume_status_get(i)    ) { return 1; } } return 0; }
uint8_t room_volume_control_get    (ROOM_N_T room) { return room_list[room][ROOM_REG_VOL_CONTROL     ]; }
uint8_t room_volume_trig_get       (ROOM_N_T room) { return room_list[room][ROOM_REG_VOL_TRIG        ]; }
uint8_t rooms_volume_trig_get      (void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_volume_trig_get(i)      ) { return 1; } } return 0; }

uint8_t room_simulation_status_get (ROOM_N_T room) { return room_list[room][ROOM_REG_SIM_STATUS      ]; }
uint8_t rooms_simulation_status_get(void)          { uint8_t i; for(i=0; i<ROOM_MAX; i++) { if(room_simulation_status_get(i)) { return 1; } } return 0; }
uint8_t room_simulation_control_get(ROOM_N_T room) { return room_list[room][ROOM_REG_SIM_CONTROL     ]; }

uint8_t room_light_get             (ROOM_N_T room, uint8_t no) { return room_list[room][ROOM_REG_LIGHT   + no]; }
uint8_t room_shutter_get           (ROOM_N_T room, uint8_t no) { return room_list[room][ROOM_REG_SHUTTER + no]; }
uint8_t room_heater_get            (ROOM_N_T room, uint8_t no) { return room_list[room][ROOM_REG_HEATER  + no]; }
uint8_t room_elec_get              (ROOM_N_T room, uint8_t no) { return room_list[room][ROOM_REG_ELEC    + no]; }

void room_temp_max_th_set        (ROOM_N_T room, uint8_t th     ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MAX_TH     , 1, &th     ); }
void rooms_temp_max_th_set       (               uint8_t th     ) {                    i2c_broadcast_set(      ROOM_REG_TEMP_MAX_TH     , 1, &th     ); }
void room_temp_max_control_set   (ROOM_N_T room, uint8_t control) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MAX_CONTROL, 1, &control); }
void rooms_temp_max_control_set  (               uint8_t control) {                    i2c_broadcast_set(      ROOM_REG_TEMP_MAX_CONTROL, 1, &control); }
void room_temp_max_trig_set      (ROOM_N_T room, uint8_t trig   ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MAX_TRIG   , 1, &trig   ); }
void rooms_temp_max_trig_set     (               uint8_t trig   ) {                    i2c_broadcast_set(      ROOM_REG_TEMP_MAX_TRIG   , 1, &trig   ); }
void room_temp_min_th_set        (ROOM_N_T room, uint8_t th     ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MIN_TH     , 1, &th     ); }
void rooms_temp_min_th_set       (               uint8_t th     ) {                    i2c_broadcast_set(      ROOM_REG_TEMP_MIN_TH     , 1, &th     ); }
void room_temp_min_control_set   (ROOM_N_T room, uint8_t control) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MIN_CONTROL, 1, &control); }
void rooms_temp_min_control_set  (               uint8_t control) {                    i2c_broadcast_set(      ROOM_REG_TEMP_MIN_CONTROL, 1, &control); }
void room_temp_min_trig_set      (ROOM_N_T room, uint8_t trig   ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_TEMP_MIN_TRIG   , 1, &trig   ); }
void rooms_temp_min_trig_set     (               uint8_t trig   ) {                    i2c_broadcast_set(      ROOM_REG_TEMP_MIN_TRIG   , 1, &trig   ); }

void room_hum_control_set        (ROOM_N_T room, uint8_t control) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_HUM_CONTROL     , 1, &control); }
void rooms_hum_control_set       (               uint8_t control) {                    i2c_broadcast_set(      ROOM_REG_HUM_CONTROL     , 1, &control); }
void room_hum_trig_set           (ROOM_N_T room, uint8_t trig   ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_HUM_TRIG        , 1, &trig   ); }
void rooms_hum_trig_set          (               uint8_t trig   ) {                    i2c_broadcast_set(      ROOM_REG_HUM_TRIG        , 1, &trig   ); }

void room_smoke_control_set      (ROOM_N_T room, uint8_t control) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_SMOKE_CONTROL   , 1, &control); }
void rooms_smoke_control_set     (               uint8_t control) {                    i2c_broadcast_set(      ROOM_REG_SMOKE_CONTROL   , 1, &control); }
void room_smoke_trig_set         (ROOM_N_T room, uint8_t trig   ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_SMOKE_TRIG      , 1, &trig   ); }
void rooms_smoke_trig_set        (               uint8_t trig   ) {                    i2c_broadcast_set(      ROOM_REG_SMOKE_TRIG      , 1, &trig   ); }

void room_perimeter_control_set  (ROOM_N_T room, uint8_t control) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_PERI_CONTROL    , 1, &control); }
void rooms_perimeter_control_set (               uint8_t control) {                    i2c_broadcast_set(      ROOM_REG_PERI_CONTROL    , 1, &control); }
void room_perimeter_trig_set     (ROOM_N_T room, uint8_t trig   ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_PERI_TRIG       , 1, &trig   ); }
void rooms_perimeter_trig_set    (               uint8_t trig   ) {                    i2c_broadcast_set(      ROOM_REG_PERI_TRIG       , 1, &trig   ); }

void room_volume_control_set     (ROOM_N_T room, uint8_t control) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_VOL_CONTROL     , 1, &control); }
void rooms_volume_control_set    (               uint8_t control) {                    i2c_broadcast_set(      ROOM_REG_VOL_CONTROL     , 1, &control); }
void room_volume_trig_set        (ROOM_N_T room, uint8_t trig   ) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_VOL_TRIG        , 1, &trig   ); }
void rooms_volume_trig_set       (               uint8_t trig   ) {                    i2c_broadcast_set(      ROOM_REG_VOL_TRIG        , 1, &trig   ); }

void room_simulation_control_set (ROOM_N_T room, uint8_t control) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_SIM_CONTROL     , 1, &control); }
void rooms_simulation_control_set(               uint8_t control) {                    i2c_broadcast_set(      ROOM_REG_SIM_CONTROL     , 1, &control); }

void room_light_set              (ROOM_N_T room, uint8_t no, uint8_t value) { if(room < ROOM_MAX) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_LIGHT  +no, 1, &value); } else { rooms_light_set(no, value); } }
void rooms_light_set             (               uint8_t no, uint8_t value) {                    i2c_broadcast_set(      ROOM_REG_LIGHT  +no, 1, &value); }
void room_shutter_set            (ROOM_N_T room, uint8_t no, uint8_t value) { if(room < ROOM_MAX) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_SHUTTER+no, 1, &value); } else { rooms_shutter_set(no, value); } }
void rooms_shutter_set           (               uint8_t no, uint8_t value) {                    i2c_broadcast_set(      ROOM_REG_SHUTTER+no, 1, &value); }
void room_heater_set             (ROOM_N_T room, uint8_t no, uint8_t value) { if(room < ROOM_MAX) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_HEATER  +no, 1, &value); } else { rooms_heater_set(no, value); } }
void rooms_heater_set            (               uint8_t no, uint8_t value) {                    i2c_broadcast_set(      ROOM_REG_HEATER  +no, 1, &value); }
void room_elec_set               (ROOM_N_T room, uint8_t no, uint8_t value) { if(room < ROOM_MAX) { room_error[room] = i2c_set(room+ROOM_SLA, ROOM_REG_ELEC    +no, 1, &value); } else { rooms_elec_set(no, value); } }
void rooms_elec_set              (               uint8_t no, uint8_t value) {                    i2c_broadcast_set(      ROOM_REG_ELEC    +no, 1, &value); }

uint8_t rooms_temp_max_value_get(void)
{
  uint8_t i=0;
  uint8_t temp=0;
  uint8_t temp_max=0;

  for(i=0; i<ROOM_MAX; i++)
  {
    temp=room_temp_value_get(i);
    if(temp>temp_max) {temp_max=temp;}
  }
  return temp_max;
}

uint8_t rooms_temp_min_value_get(void)
{
  uint8_t i=0;
  uint8_t temp=0;
  uint8_t temp_min=0;

  for(i=0; i<ROOM_MAX; i++)
  {
    temp=room_temp_value_get(i);
    if(temp<temp_min) {temp_min=temp;}
  }
  return temp_min;
}


THREAD(RoomD, arg)
{
  uint8_t i = 0;

  NutThreadSetPriority(26);

  while(1)
  {
    for(i=0; i<ROOM_MAX; i++)
    {
      room_error[i] = i2c_get(ROOM_SLA+i, 0, ROOM_REG_MAX, &room_list[i][0]);
    }
    NutSleep(1000);
  }
}

int rooms_form(FILE * stream, REQUEST * req)
{
  char* room_s=0;
  unsigned int room=0;
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
  NutHttpSendHeaderBot(stream, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    room_s = NutHttpGetParameter(req, "room");
    if(room_s)
    {
      room = strtoul(room_s, NULL, 10);
      if((0 <= room) && (room <= ROOM_MAX))
      {
        light_s = NutHttpGetParameter(req, "light");
        shutter_s = NutHttpGetParameter(req, "shutter");
        heater_s = NutHttpGetParameter(req, "heater");
        elec_s = NutHttpGetParameter(req, "elec");
        value_s = NutHttpGetParameter(req, "value");
        if(light_s && value_s)
        {
          light = strtoul(light_s, NULL, 10);
          if(value_s[0] == '?') { fprintf(stream, "%d", room_light_get(room, light)); }
          else
          {
            if(light < ROOM_LIGHT_MAX)
            {
              room_light_set(room, light, strtoul(value_s, NULL, 10));
            }
            else
            {
              for(light=0; light<ROOM_LIGHT_MAX; light++)
              {
                room_light_set(room, light, strtoul(value_s, NULL, 10));
              }
            }
          }
        }
        if(shutter_s && value_s)
        {
          shutter = strtoul(shutter_s, NULL, 10);
          if(value_s[0] == '?') { fprintf(stream, "%d", room_shutter_get(room, shutter)); }
          else
          {
            if(shutter < ROOM_SHUTTER_MAX)
            {
              room_shutter_set(room, shutter, strtoul(value_s, NULL, 10));
            }
            else
            {
              for(shutter=0; shutter<ROOM_SHUTTER_MAX; shutter++)
              {
                room_shutter_set(room, shutter, strtoul(value_s, NULL, 10));
              }
            }
          }
        }
        if(heater_s && value_s)
        {
          heater = strtoul(heater_s, NULL, 10);
          if(value_s[0] == '?') { fprintf(stream, "%d", room_heater_get(room, heater)); }
          else
          {
            if(heater < ROOM_HEATER_MAX)
            {
              room_heater_set(room, heater, strtoul(value_s, NULL, 10));
            }
            else
            {
              for(heater=0; heater<ROOM_HEATER_MAX; heater++)
              {
                room_heater_set(room, heater, strtoul(value_s, NULL, 10));
              }
            }
          }
        }
        if(elec_s && value_s)
        {
          elec = strtoul(elec_s, NULL, 10);
          if(value_s[0] == '?') { fprintf(stream, "%d", room_elec_get(room, elec)); }
          else
          {
            if(elec < ROOM_ELEC_MAX)
            {
              room_elec_set(room, elec, strtoul(value_s, NULL, 10));
            }
            else
            {
              for(elec=0; elec<ROOM_ELEC_MAX; elec++)
              {
                room_elec_set(room, elec, strtoul(value_s, NULL, 10));
              }
            }
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
  uint8_t i=0;
  uint8_t j=0;
  char room_xml[10];
  char arg_xml[20];

  for(i=0; i<ROOM_MAX; i++)
  {
    sprintf(room_xml, "Room%d", i);
    fprintf_XML_elt_header(room_xml, stream);
    fprintf_XML_elt_int("Error_Trig"     , room_error[i]                 , stream);
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