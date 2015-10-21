var url_alarm="cgi/alarm.cgi?";

function lost_alarm_update(xml, type)
{
  var out_str;
  var out_id;
  var in_id1 = xml.getElementsByTagName("Alarm")[0];
  var in_id2;
  if(in_id1)
  {
    in_id2 = in_id1.getElementsByTagName(type+"_Ctrl")[0];
  }
  else
  {
    in_id2 = null;
  }
  out_str = "Alarm_"+type+"_Status";
  out_id = document.getElementById(out_str);
  if(out_id)
  {
    if(in_id2)
    {
      if(in_id2.firstChild.nodeValue > 0)
      {
        if(in_id2.firstChild.nodeValue == 1)
        {
          out_id.innerHTML = "Running&nbsp;";
        }
        else
        {
          out_id.innerHTML = "Starting in "+in_id2.firstChild.nodeValue+"s&nbsp;";
        }
      }
      else
      {
        out_id.innerHTML = "";
      }
    }
    else
    {
      out_id.innerHTML = "Unknown&nbsp;";
    }
    lost_wa_refresh(out_str);
  }
}

function lost_alarm_xml_get(xml)
{
  lost_elt_bool_update(xml, "Alarm", "Perimeter");
  lost_elt_bool_update(xml, "Alarm", "Volume");
  lost_elt_bool_update(xml, "Alarm", "Simulation");

  lost_alarm_update(xml, "Perimeter");
  lost_alarm_update(xml, "Volume");
  lost_alarm_update(xml, "Simulation");
}

/* ********** SET ********** */
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
