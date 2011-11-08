var ROOM_SHUTTER_UP   = 1
var ROOM_SHUTTER_STOP = 2
var ROOM_SHUTTER_DOWN = 3

var ROOM_SALON    = 0;
var ROOM_CUISINE   = 1;
var ROOM_BUREAU   = 2;
var ROOM_TERRASSE = 3;
var ROOM_C1       = 4;
var ROOM_C2       = 5;
var ROOM_C3       = 6;
var ROOM_C4       = 7;
var ROOM_WC       = 8;
var ROOM_MAX      = 9;
var ROOM_LIGHT_MAX   = 10;
var ROOM_SHUTTER_MAX = 10;
var ROOM_HEATER_MAX  = 10;
var ROOM_ELEC_MAX    = 10;
var url_room="cgi/rooms.cgi?room=";

function lost_rooms_xml_get(xml)
{
  var i=0;
  var j=0;
  for(i=0; i<ROOM_MAX; i++)
  {
    lost_innerHTML_update(xml, "Room"+String(i), "Error_Trig");
    lost_trig2bg_update(xml, "Room"+String(i), "Error");

    lost_innerHTML_update(xml, "Room"+String(i), "Type");
    lost_innerHTML_update(xml, "Room"+String(i), "Version");
    lost_innerHTML_update(xml, "Room"+String(i), "Adress");

    lost_innerHTML_F2C_update(xml, "Room"+String(i), "Temp_Max");
    lost_innerHTML_update(xml, "Room"+String(i), "Temp_Max_Ctrl");
    lost_trig2bg_update(xml, "Room"+String(i), "Temp_Max");
    lost_innerHTML_F2C_update(xml, "Room"+String(i), "Temp_Max_Th");

    lost_innerHTML_F2C_update(xml, "Room"+String(i), "Temp_Min");
    lost_innerHTML_update(xml, "Room"+String(i), "Temp_Min_Ctrl");
    lost_trig2bg_update(xml, "Room"+String(i), "Temp_Min");
    lost_innerHTML_F2C_update(xml, "Room"+String(i), "Temp_Min_Th");

    lost_innerHTML_update(xml, "Room"+String(i), "Hum");
    lost_innerHTML_update(xml, "Room"+String(i), "Hum_Ctrl");
    lost_trig2bg_update(xml, "Room"+String(i), "Hum");

    lost_innerHTML_update(xml, "Room"+String(i), "Smoke");
    lost_innerHTML_update(xml, "Room"+String(i), "Smoke_Ctrl");
    lost_trig2bg_update(xml, "Room"+String(i), "Smoke");

    lost_innerHTML_update(xml, "Room"+String(i), "Perimeter");
    lost_innerHTML_update(xml, "Room"+String(i), "Perimeter_Ctrl");
    lost_trig2bg_update(xml, "Room"+String(i), "Perimeter");

    lost_innerHTML_update(xml, "Room"+String(i), "Volume");
    lost_innerHTML_update(xml, "Room"+String(i), "Volume_Ctrl");
    lost_trig2bg_update(xml, "Room"+String(i), "Volume");

    lost_innerHTML_update(xml, "Room"+String(i), "Simulation");
    lost_innerHTML_update(xml, "Room"+String(i), "Simulation_Ctrl");

    for(j=0; j<ROOM_LIGHT_MAX; j++)
    {
      lost_ck_update(xml, "Room"+String(i), "Light"+String(j));
    }
    for(j=0; j<ROOM_SHUTTER_MAX; j++)
    {
      lost_ck_update(xml, "Room"+String(i), "Shutter"+String(j));
    }
    for(j=0; j<ROOM_HEATER_MAX; j++)
    {
      lost_ck_update(xml, "Room"+String(i), "Heater"+String(j));
    }
    for(j=0; j<ROOM_ELEC_MAX; j++)
    {
      lost_ck_update(xml, "Room"+String(i), "Elec"+String(j));
    }
  }
}

/* ********** SET ********** */
function lost_room_light_set(room, no)
{
  lost_set(url_room+String(room)+"&light="+String(no)+"&value="+String(Number(document.getElementById("Room"+String(room)+"_Light"+String(no)).checked)));
}

function lost_room_light_all_set(value)
{
  lost_set(url_room+String(ROOM_MAX)+"&light="+String(ROOM_LIGHT_MAX)+"&value="+String(value));
}

function lost_room_shutter_set(room, no, value)
{
  lost_set(url_room+String(room)+"&shutter="+String(no)+"&value="+String(value));
}

function lost_room_shutter_all_set(value)
{
  lost_room_shutter_set(ROOM_MAX, ROOM_HEATER_MAX, value);
}

function lost_room_heater_set(room, no)
{
  lost_set(url_room+String(room)+"&heater="+String(no)+"&value="+String(Number(document.getElementById("Room"+String(room)+"_Heater"+String(no)).checked)));
}

function lost_room_heater_all_set(value)
{
  lost_set(url_room+String(ROOM_MAX)+"&heater="+String(ROOM_HEATER_MAX)+"&value="+String(value));
}

function lost_room_elec_set(room, no)
{
  lost_set(url_room+String(room)+"&elec="+String(no)+"&value="+String(Number(document.getElementById("Room"+String(room)+"_Elec"+String(no)).checked)));
}

function lost_room_elec_all_set(value)
{
  lost_set(url_room+String(ROOM_MAX)+"&elec="+String(ROOM_ELEC_MAX)+"&value="+String(value));
}
