var url_alarm="cgi/alarm.cgi?";

function lost_alarm_perimeter_set()
{
  var elt;
  elt = document.getElementById("Alarm_Perimeter_Ctrl");
  if(elt)
  {
    lost_set(url_alarm+"perimeter_ctrl="+String(Number(elt.checked)));
  }
}

function lost_alarm_volume_set()
{
  var elt;
  elt = document.getElementById("Alarm_Volume_Ctrl");
  if(elt)
  {
    lost_set(url_alarm+"volume_ctrl="+String(Number(elt.checked)));
  }
}

function lost_alarm_simulation_set()
{
  var elt;
  elt = document.getElementById("Alarm_Simulation_Ctrl");
  if(elt)
  {
    lost_set(url_alarm+"simulation_ctrl="+String(Number(elt.checked)));
  }
}

function lost_alarm_xml_get(xml)
{
  lost_elt_bool_update(xml, "Alarm", "Perimeter");
  lost_elt_bool_update(xml, "Alarm", "Volume");
  lost_elt_bool_update(xml, "Alarm", "Simulation");
}
