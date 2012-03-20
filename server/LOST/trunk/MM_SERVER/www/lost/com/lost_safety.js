var url_safety="cgi/safety.cgi?";

function lost_safety_rooms_error_status_set()
{
  var elt;
  elt = document.getElementById("Safety_Rooms_Error_Ctrl");
  if(elt)
  {
    lost_set(url_safety+"rooms_error_ctrl="+String(Number(elt.checked)));
  }
}

function lost_safety_rooms_temp_max_status_set()
{
  var elt_Ctrl;
  var elt_Th;
  var status;

  elt_Ctrl = document.getElementById("Safety_Rooms_Temp_Max_Ctrl");
  if(elt_Ctrl)
  {
    status = elt_Ctrl.checked;
    elt_Th = document.getElementById("Safety_Rooms_Temp_Max_Th");
    if(elt_Th)
    {
      elt_Th.disabled = status;
      if(status == true)
      { // *5*100)/1024)-32)*140)/252
        lost_set(url_safety+"rooms_temp_max_th="+String(Number((((((elt_Th.value)*252)/140)+32)*1024)/5)/100));
      }
      lost_set(url_safety+"rooms_temp_max_ctrl="+String(Number(status)));
    }
  }
}

function lost_safety_rooms_temp_min_status_set()
{
  var elt_Ctrl;
  var elt_Th;
  var status;

  elt_Ctrl = document.getElementById("Safety_Rooms_Temp_Min_Ctrl");
  if(elt_Ctrl)
  {
    status = elt_Ctrl.checked;
    elt_Th = document.getElementById("Safety_Rooms_Temp_Min_Th");
    if(elt_Th)
    {
      elt_Th.disabled = status;
      if(status == true)
      { // *5*100)/1024)-32)*140)/252
        lost_set(url_safety+"rooms_temp_min_th="+String(Number((((((elt_Th.value)*252)/140)+32)*1024)/5)/100));
      }
      lost_set(url_safety+"rooms_temp_min_ctrl="+String(Number(status)));
    }
  }
}

function lost_safety_rooms_hum_status_set()
{
  var elt;
  elt = document.getElementById("Safety_Rooms_Hum_Ctrl");
  if(elt)
  {
    lost_set(url_safety+"rooms_hum_ctrl="+String(Number(elt.checked)));
  }
}

function lost_safety_rooms_smoke_status_set()
{
  var elt;
  elt = document.getElementById("Safety_Rooms_Smoke_Ctrl");
  if(elt)
  {
    lost_set(url_safety+"rooms_smoke_ctrl="+String(Number(elt.checked)));
  }
}

function lost_safety_ups_temp_status_set()
{
  var elt_Ctrl;
  var elt_Th;
  var status;

  elt_Ctrl = document.getElementById("Safety_UPS_Temp_Ctrl");
  if(elt_Ctrl)
  {
    status = elt_Ctrl.checked;
    elt_Th = document.getElementById("Safety_UPS_Temp_Th");
    if(elt_Th)
    {
      elt_Th.disabled = status;
      if(status == true)
      { // *5*100)/1024)-32)*140)/252
        lost_set(url_safety+"ups_temp_th="+String(Number((((((elt_Th.value)*252)/140)+32)*1024)/5)/100));
      }
      lost_set(url_safety+"ups_temp_ctrl="+String(Number(status)));
    }
  }
}

function lost_safety_ups_power_status_set()
{
  var elt;
  elt = document.getElementById("Safety_UPS_Power_Ctrl");
  if(elt)
  {
    lost_set(url_safety+"ups_power_ctrl="+String(Number(elt.checked)));
  }
}

function lost_safety_rack_temp_status_set()
{
  var elt_Ctrl;
  var elt_Th;
  var status;

  elt_Ctrl = document.getElementById("Safety_RACK_Temp_Ctrl");
  if(elt_Ctrl)
  {
    status = elt_Ctrl.checked;
    elt_Th = document.getElementById("Safety_RACK_Temp_Th");
    if(elt_Th)
    {
      elt_Th.disabled = status;
      if(status == true)
      { // *5*100)/1024)-32)*140)/252
        lost_set(url_safety+"rack_temp_th="+String(Number((((((elt_Th.value)*252)/140)+32)*1024)/5)/100));
      }
      lost_set(url_safety+"rack_temp_ctrl="+String(Number(status)));
    }
  }
}

function lost_safety_rack_alarm_status_set()
{
  var elt;
  elt = document.getElementById("Safety_RACK_Alarm_Ctrl");
  if(elt)
  {
    lost_set(url_safety+"rack_alarm_ctrl="+String(Number(elt.checked)));
  }
}

function lost_safety_http_status_set()
{
  var elt;
  elt = document.getElementById("Safety_HTTP_Ctrl");
  if(elt)
  {
    lost_set(url_safety+"http_ctrl="+String(Number(elt.checked)));
  }
}

function lost_safety_gsm_status_set()
{
  var elt;
  elt = document.getElementById("Safety_GSM_Ctrl");
  if(elt)
  {
    lost_set(url_safety+"gsm_ctrl="+String(Number(elt.checked)));
  }
}

function lost_safety_xml_get(xml)
{
  lost_elt_bool_update(xml, "Safety", "Rooms_Error");
  lost_elt_F2C_update(xml, "Safety", "Rooms_Temp_Max");
  lost_elt_F2C_update(xml, "Safety", "Rooms_Temp_Min");
  lost_elt_bool_update(xml, "Safety", "Rooms_Hum");
  lost_elt_bool_update(xml, "Safety", "Rooms_Smoke");

  lost_elt_F2C_update(xml, "Safety", "UPS_Temp");
  lost_elt_bool_update(xml, "Safety", "UPS_Power");
  lost_elt_F2C_update(xml, "Safety", "RACK_Temp");
  lost_elt_bool_update(xml, "Safety", "RACK_Alarm");
  lost_elt_bool_update(xml, "Safety", "HTTP");
  lost_elt_bool_update(xml, "Safety", "GSM");
}
