var url_safety="cgi/safety.cgi?";

function lost_safety_rooms_error_status_set()
{
  lost_set(url_safety+"rooms_error_ctrl="+String(Number(document.getElementById("Safety_Rooms_Error_Ctrl").checked)));
}

function lost_safety_rooms_temp_max_status_set()
{
  var status = document.getElementById("Safety_Rooms_Temp_Max_Ctrl").checked;
  document.getElementById("Safety_Rooms_Temp_Max_Th").disabled = status;
  if(status==true)
  { // *5*100)/1024)-32)*140)/252
    lost_set(url_safety+"rooms_temp_max_th="+String(Number((((((document.getElementById("Safety_Rooms_Temp_Max_Th").value)*252)/140)+32)*1024)/5)/100));
  }
  lost_set(url_safety+"rooms_temp_max_ctrl="+String(Number(status)));
}

function lost_safety_rooms_temp_min_status_set()
{
  var status = document.getElementById("Safety_Rooms_Temp_Min_Ctrl").checked;
  document.getElementById("Safety_Rooms_Temp_Min_Th").disabled = status;
  if(status==true)
  { // *5*100)/1024)-32)*140)/252
    lost_set(url_safety+"rooms_temp_min_th="+String(Number((((((document.getElementById("Safety_Rooms_Temp_Min_Th").value)*252)/140)+32)*1024)/5)/100));
  }
  lost_set(url_safety+"rooms_temp_min_ctrl="+String(Number(status)));
}

function lost_safety_rooms_hum_status_set()
{
  lost_set(url_safety+"rooms_hum_ctrl="+String(Number(document.getElementById("Safety_Rooms_Hum_Ctrl").checked)));
}

function lost_safety_rooms_smoke_status_set()
{
  lost_set(url_safety+"rooms_smoke_ctrl="+String(Number(document.getElementById("Safety_Rooms_Smoke_Ctrl").checked)));
}

function lost_safety_ups_temp_status_set()
{
  var status = document.getElementById("Safety_UPS_Temp_Ctrl").checked;
  document.getElementById("Safety_UPS_Temp_Th").disabled = status;
  if(status==true)
  { // *5*100)/1024)-32)*140)/252
    lost_set(url_safety+"ups_temp_th="+String(Number((((((document.getElementById("Safety_UPS_Temp_Th").value)*252)/140)+32)*1024)/5)/100));
  }
  lost_set(url_safety+"ups_temp_ctrl="+String(Number(status)));
}

function lost_safety_ups_power_status_set()
{
  lost_set(url_safety+"ups_power_ctrl="+String(Number(document.getElementById("Safety_UPS_Power_Ctrl").checked)));
}

function lost_safety_ups_power_threshold_set()
{
  lost_set(url_safety+"ups_power_th="+String(Number(document.getElementById("Safety_UPS_Power_Th").checked)));
}

function lost_safety_http_status_set()
{
  lost_set(url_safety+"http_ctrl="+String(Number(document.getElementById("Safety_HTTP_Ctrl").checked)));
}

function lost_safety_gsm_status_set()
{
  lost_set(url_safety+"gsm_ctrl="+String(Number(document.getElementById("Safety_GSM_Ctrl").checked)));
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
  lost_elt_bool_update(xml, "Safety", "HTTP");
  lost_elt_bool_update(xml, "Safety", "GSM");
}
