var lost_path = "http://lebomb.free.fr/LOST/";
var lost_icons_path = lost_path + "icons/";

function lost_getXHR()
{
  var xhr = null;
  if(window.XMLHttpRequest) // Firefox et autres
  {
    xhr = new XMLHttpRequest();
  }
  else
  {
    if(window.ActiveXObject)
    { // Internet Explorer 
      try
      {
        xhr = new ActiveXObject("Msxml2.XMLHTTP");
      }
      catch (e)
      {
        xhr = new ActiveXObject("Microsoft.XMLHTTP");
      }
    }
    else
    { // XMLHttpRequest non supporte par le navigateur
      alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest..."); 
      xhr = false;
    }
  }
  return xhr;
}

function lost_set(url)
{
  var xhr = lost_getXHR();
  xhr.onreadystatechange = function() {};
  xhr.open("GET",url,true);
  //xhr.setTimeouts(4);
  xhr.send("");
}

function lost_wa_refresh(elt)
{
  if(elt)
  {
    WA.Refresh(elt);
  }
}

function lost_ck_update(xml, node, id)
{
  var in_id1 = xml.getElementsByTagName(node)[0];
  if(in_id1)
  {
    var in_id2 = in_id1.getElementsByTagName(id)[0];
    if(in_id2)
    {
      var out_id = document.getElementById(node+"_"+id);
      if(out_id)
      {
        out_id.checked=Boolean(Number(in_id2.firstChild.nodeValue));
        lost_wa_refresh(node+"_"+id);
      }
    }
  }
}

function lost_select_update(xml, node, id)
{
  var in_id1 = xml.getElementsByTagName(node)[0];
  if(in_id1)
  {
    var in_id2 = in_id1.getElementsByTagName(id)[0];
    if(in_id2)
    {
      var out_id = document.getElementById(node+"_"+id);
      if(out_id)
      {
        out_id.options[Number(in_id2.firstChild.nodeValue)].selected = true;
        lost_wa_refresh(node+"_"+id);
      }
    }
  }
}

function lost_select_F2C_update(xml, node, id)
{
  var in_id1 = xml.getElementsByTagName(node)[0];
  if(in_id1)
  {
    var in_id2 = in_id1.getElementsByTagName(id)[0];
    if(in_id2)
    {
      var out_id = document.getElementById(node+"_"+id);
      if(out_id)
      {
        var temp = Math.round(((((Number(in_id2.firstChild.nodeValue)*5*100)/1024)-32)*140)/252);
        if((out_id.options[0].value <= temp) && (temp <= out_id.options[out_id.length-1].value))
        {
          out_id.options[temp-out_id.options[0].value].selected = true;
          lost_wa_refresh(node+"_"+id);
        }
      }
    }
  }
}

function lost_innerHTML_update(xml, node, id)
{
  var out_id = document.getElementById(node+"_"+id);
  if(out_id)
  {
	var in_id1 = xml.getElementsByTagName(node)[0];
    if(in_id1)
    {
      var in_id2 = in_id1.getElementsByTagName(id)[0];
      if(in_id2)
      {
        out_id.innerHTML=in_id2.firstChild.nodeValue;
        lost_wa_refresh(node+"_"+id);
      }
      else
      {
        out_id.innerHTML="Unknown";
        lost_wa_refresh(node+"_"+id);
      }
    }
    else
    {
      out_id.innerHTML="Unknown";
      lost_wa_refresh(node+"_"+id);
    }
  }
}

function lost_innerHTML_F2C_update(xml, node, id)
{
  var out_id = document.getElementById(node+"_"+id);
  if(out_id)
  {
    var in_id1 = xml.getElementsByTagName(node)[0];
    if(in_id1)
    {
      var in_id2 = in_id1.getElementsByTagName(id)[0];
      if(in_id2)
      {
        out_id.innerHTML=Math.round(((((((in_id2.firstChild.nodeValue)*5*100)/1024)-32)*140)/252)*10)/10;
        lost_wa_refresh(node+"_"+id);
      }
      else
      {
        out_id.innerHTML="Unknown";
        lost_wa_refresh(node+"_"+id);
      }
    }
    else
    {
      out_id.innerHTML="Unknown";
      lost_wa_refresh(node+"_"+id);
    }
  }
}

function printSelectOption(id, nb)
{
  var elt;
  var i;
  elt = document.getElementById(id);
  if(elt)
  {
    elt.length = nb;
    for(i=0; i<nb; i++)
    {
      elt.options[i].value = i;
      elt.options[i].text = String(i);
    }
  }
}

function lost_trig2bg_update(xml, node, id)
{
  var out_id1 = document.getElementById(node+"_"+id+"_bg");
  var out_id2 = document.getElementById(node+"_"+id+"_Ctrl_bg");
  var out_id3 = document.getElementById(node+"_bg");

  var in_id1 = xml.getElementsByTagName(node)[0];
  if(in_id1)
  {
    var in_id2 = in_id1.getElementsByTagName(id+"_Trig")[0];
    if(in_id2)
    {
      if(Boolean(Number(in_id2.firstChild.nodeValue)) == true)
      {
        if(out_id1) { out_id1.style.backgroundColor = "#FF0000"; }
        if(out_id2) { out_id2.style.backgroundColor = "#FF0000"; }
        if(out_id3) { out_id3.style.backgroundColor = "#FF0000"; }
      }
      else
      {
        if(out_id1) { out_id1.style.backgroundColor = "#FFFFFF"; }
        if(out_id2) { out_id2.style.backgroundColor = "#FFFFFF"; }
      }
    }
    else
    {
      if(out_id1) { out_id1.style.backgroundColor = "#FE8800"; }
      if(out_id2) { out_id2.style.backgroundColor = "#FE8800"; }
      if(out_id3) { out_id3.style.backgroundColor = "#FE8800"; }
    }
  }
  else
  {
    if(out_id1) { out_id1.style.backgroundColor = "#FE8800"; }
    if(out_id2) { out_id2.style.backgroundColor = "#FE8800"; }
    if(out_id3) { out_id3.style.backgroundColor = "#FE8800"; }
  }
}

function lost_elt_bool_update(xml, node, id)
{
  lost_ck_update(xml, node, id+"_Ctrl");
  lost_innerHTML_update(xml, node, id);
  lost_trig2bg_update(xml, node, id);
}

function lost_elt_F2C_update(xml, node, id)
{
  lost_ck_update(xml, node, id+"_Ctrl");
  lost_innerHTML_F2C_update(xml, node, id);
  var in_id1 = xml.getElementsByTagName(node)[0];
  if(in_id1)
  {
    var in_id2 = in_id1.getElementsByTagName(id+"_Ctrl")[0];
    if(in_id2)
    {
      var out_id = document.getElementById(node+"_"+id+"_Th");
      if(out_id)
      {
        out_id.disabled = Boolean(Number(in_id2.firstChild.nodeValue));
        if(Boolean(Number(in_id2.firstChild.nodeValue)) == true) { lost_select_F2C_update(xml, node, id+"_Th"); }
      }
    }
  }
  lost_trig2bg_update(xml, node, id);
}

function indexLoading(evt)
{
  var xhr = lost_getXHR();
  var xml;
  xhr.onreadystatechange = function()
  {
    if((xhr.readyState == 4))
    {
      if(xhr.status == 200)
      {
        xml=xhr.responseXML;
        if(xml)
        {
          lost_mon_xml_get(xml);
          lost_alarm_xml_get(xml);
          lost_safety_xml_get(xml);
          lost_rooms_xml_get(xml);
          lost_ev_xml_get(xml);
        }
      }
      else
      {
        xhr.abort();
      }
    }
  };
  xhr.open("GET","cgi/get.xml?",true);
  //xhr.setTimeouts(4000);
  xhr.send("");

  setTimeout("indexLoading()", 10000);
}
WA.AddEventListener("load", indexLoading);
//document.onReady=indexLoading();
function lost_mon_xml_get(xml)
{
  var out_id1 = document.getElementById("lost_title");
  var out_id2 = document.getElementById("lost_title");
  if(out_id1 && out_id2)
  {
	var in_id = xml.getElementsByTagName("Mon")[0];
    if(in_id)
    {
      var wday = in_id.getElementsByTagName("wday")[0];
      var mon = in_id.getElementsByTagName("mon")[0];
      var mday = in_id.getElementsByTagName("mday")[0];
      var hour = in_id.getElementsByTagName("hour")[0];
      var min = in_id.getElementsByTagName("min")[0];
      var sec = in_id.getElementsByTagName("sec")[0];
      var year = in_id.getElementsByTagName("year")[0];
      if(wday && mon && mday && hour && min && sec && year)
      {
        out_id1.innerHTML = "LOST "
                         + hour.firstChild.nodeValue + ":"
                         + min.firstChild.nodeValue  + ":"
                         + sec.firstChild.nodeValue  + " "
                         + year.firstChild.nodeValue + "-"
                         + mon.firstChild.nodeValue  + "-"
                         + mday.firstChild.nodeValue;
        out_id2.innerHTML = out_id1.innerHTML;
        lost_wa_refresh("lost_title");
        lost_wa_refresh("waHeadTitle");
      }
      else
      {
        out_id1.innerHTML="Unknown";
        out_id2.innerHTML = out_id1.innerHTML;
        lost_wa_refresh("lost_title");
        lost_wa_refresh("waHeadTitle");
      }
    }
    else
    {
      out_id1.innerHTML="Unknown";
      out_id2.innerHTML = out_id1.innerHTML;
      lost_wa_refresh("lost_title");
      lost_wa_refresh("waHeadTitle");
    }
  }
}
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
var ATM_UNKNOWN    = 0;
var ATM_CINEMA     = 1;
var ATM_ROMANTIQUE = 2;
var ATM_ECO        = 3;
var url_atm="cgi/atm.cgi?atm=";
var url_scene="cgi/scenes.cgi?scene=";

function lost_atm_set(atm)
{
  lost_set(url_atm+String(atm));
}

function lost_scene_set(scene, status)
{
  lost_set(url_scene+String(scene)+"&status="+String(status));
}
var url_safety="cgi/safety.cgi?";

function lost_safety_power_update(xml)
{
  var i=0;
  var out_sc_str;
  var out_sc_id1;
  var out_sc_id2;
  var out_ev_str;
  var out_ev_id1;
  var out_ev_id2;
  var in_id1 = xml.getElementsByTagName("Safety")[0];
  var in_id2;

  for(i=0; i<3; i++)
  {
    if(in_id1) { in_id2 = in_id1.getElementsByTagName("Power"+String(i))[0]; } else { in_id2 = null; }
    out_sc_str = "Scene"+String(EVENT_POWER_0+i)+"_Status";
    out_sc_id1 = document.getElementById(out_sc_str);
    out_sc_id2 = document.getElementById(out_sc_str+"_bg");
    out_ev_str = "Event"+String(EVENT_POWER_0+i)+"_Status";
    out_ev_id1 = document.getElementById(out_ev_str);
    out_ev_id2 = document.getElementById(out_ev_str+"_bg");
    if(out_sc_id1 || out_sc_id2 || out_ev_id1 || out_ev_id2)
    {
      if(in_id2)
      {
        if(in_id2.firstChild.nodeValue == 1)
        {
          if(out_sc_id1) { out_sc_id1.innerHTML = "ON"; }
          if(out_sc_id2) { out_sc_id2.style.backgroundColor = "#FFFF99"; }
          if(out_ev_id1) { out_ev_id1.innerHTML = "ON"; }
          if(out_ev_id2) { out_ev_id2.style.backgroundColor = "#FFFF99"; }
        }
        else
        {
          if(out_sc_id1) { out_sc_id1.innerHTML = "OFF"; }
          if(out_sc_id2) { out_sc_id2.style.backgroundColor = "#000099"; }
          if(out_ev_id1) { out_ev_id1.innerHTML = "OFF"; }
          if(out_ev_id2) { out_ev_id2.style.backgroundColor = "#000099"; }
        }
      }
      else
      {
        if(out_sc_id1) { out_sc_id1.innerHTML = "Unknown"; }
        if(out_sc_id2) { out_sc_id2.style.backgroundColor = "#FE8800"; }
        if(out_ev_id1) { out_ev_id1.innerHTML = "Unknown"; }
        if(out_ev_id2) { out_ev_id2.style.backgroundColor = "#FE8800"; }
      }
      lost_wa_refresh(out_sc_str);
      lost_wa_refresh(out_ev_str);
    }
  }
}

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

  lost_safety_power_update(xml);
}
var ROOM_SHUTTER_UP   = 255
var ROOM_SHUTTER_STOP = 0
var ROOM_SHUTTER_DOWN = 1

var ROOM_CLIM_OFF = 0;
var ROOM_CLIM_ON  = 1;

var ROOM_C1       = 0;
var ROOM_C2       = 1;
var ROOM_C3       = 2;
var ROOM_C4       = 3;
var ROOM_SDB      = 4;
var ROOM_BUREAU   = 5;
var ROOM_SALON    = 6;
var ROOM_CUISINE  = 7;
var ROOM_COULOIR  = 8
var ROOM_TERRASSE = 9;
var ROOM_MAX      = 10;
var ROOM_LIGHT_MAX   = 10;
var ROOM_SHUTTER_MAX = 10;
var ROOM_HEATER_MAX  = 10;
var ROOM_ELEC_MAX    = 10;
var url_room="cgi/rooms.cgi?room=";

function lost_rooms_shutters_update(xml, room)
{
  var i=0;
  var out_str;
  var out_id1;
  var out_id2;
  var in_id1 = xml.getElementsByTagName("Room"+String(room))[0];
  var in_id2;
  if(in_id1)
  {
    in_id2 = in_id1.getElementsByTagName("Perimeter")[0];
  }
  else
  {
    in_id2 = null;
  }
  for(i=0; i<ROOM_SHUTTER_MAX; i++)
  {
    out_str = "Room"+String(room)+"_Shutter"+String(i)+"_Status";
    out_id1 = document.getElementById(out_str);
    out_id2 = document.getElementById(out_str+"_bg");
    if(out_id1)
    {
      if(in_id2)
      {
        if(in_id2.firstChild.nodeValue & (1<<i))
        {
          out_id1.innerHTML = "OUVERT";
          if(out_id2) { out_id2.style.backgroundColor = "#FFFF99"; }
        }
        else
        {
          out_id1.innerHTML = "FERME";
          if(out_id2) { out_id2.style.backgroundColor = "#000099"; }
        }
      }
      else
      {
        out_id1.innerHTML = "Unknown";
        if(out_id2) { out_id2.style.backgroundColor = "#FE8800"; }
      }
      lost_wa_refresh(out_str);
    }
  }
}

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
    lost_rooms_shutters_update(xml, i);

    lost_innerHTML_update(xml, "Room"+String(i), "Volume");
    lost_innerHTML_update(xml, "Room"+String(i), "Volume_Ctrl");
    lost_trig2bg_update(xml, "Room"+String(i), "Volume");

    lost_innerHTML_update(xml, "Room"+String(i), "Simulation");
    lost_innerHTML_update(xml, "Room"+String(i), "Simulation_Ctrl");

    lost_innerHTML_update(xml, "Room"+String(i), "Clim_Cmd");

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
function lost_room_clim_set(room, action)
{
  var elt;
  if(action == ROOM_CLIM_ON)
  {
    elt = document.getElementById("Room"+String(room)+"_Clim_Temp");
    if(elt)
    {
      lost_set(url_room+String(room)+"&clim="+String(Number(elt.value)));
    }
  }
  else
  {
    lost_set(url_room+String(room)+"&clim=0");
  }
}

function lost_room_light_set(room, no)
{
  var elt;
  elt = document.getElementById("Room"+String(room)+"_Light"+String(no));
  if(elt)
  {
    lost_set(url_room+String(room)+"&light="+String(no)+"&value="+String(Number(elt.checked)));
  }
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
  var elt;
  elt = document.getElementById("Room"+String(room)+"_Heater"+String(no));
  if(elt)
  {
    lost_set(url_room+String(room)+"&heater="+String(no)+"&value="+String(Number(elt.checked)));
  }
}

function lost_room_heater_all_set(value)
{
  lost_set(url_room+String(ROOM_MAX)+"&heater="+String(ROOM_HEATER_MAX)+"&value="+String(value));
}

function lost_room_elec_set(room, no)
{
  var elt;
  elt = document.getElementById("Room"+String(room)+"_Elec"+String(no));
  if(elt)
  {
    lost_set(url_room+String(room)+"&elec="+String(no)+"&value="+String(Number(elt.checked)));
  }
}

function lost_room_elec_all_set(value)
{
  lost_set(url_room+String(ROOM_MAX)+"&elec="+String(ROOM_ELEC_MAX)+"&value="+String(value));
}
var EVENT_SHUTTERS_ALL          = 0;
var EVENT_SHUTTERS_UPSTAIRS     = 1;
var EVENT_SHUTTERS_DOWNSTAIRS   = 2;
var EVENT_SHUTTERS_MARINE       = 3;
var EVENT_SHUTTERS_MM           = 4;
var EVENT_SHUTTERS_FRIENDS      = 5;
var EVENT_SHUTTERS_DRESSING     = 6;
var EVENT_ALARM_ALL             = 7;
var EVENT_ALARM_PERIMETER       = 8;
var EVENT_ALARM_VOLUME          = 9;
var EVENT_SIMU                  = 10;
var EVENT_POWER_0               = 11;
var EVENT_POWER_1               = 12;
var EVENT_POWER_2               = 13;
var EVENT_POWER_3               = 14;
var EVENT_ALARM_PERIMETER_CHECK = 15;
var EVENT_MAX                   = 16;

var EVENT_STATUS_OFF = 0;
var EVENT_STATUS_ON  = 1;

var url_ev="cgi/events.cgi?event=";

function lost_ev_date_status_update(event)
{
  var elt_St;
  var elt_StStart;
  var elt_HStart;
  var elt_MStart;
  var elt_StEnd;
  var elt_HEnd;
  var elt_MEnd;
  var status;

  elt_St = document.getElementById("Event"+String(event)+"_St");
  elt_StStart = document.getElementById("Event"+String(event)+"_StStart");
  elt_StEnd = document.getElementById("Event"+String(event)+"_StEnd");
  if(elt_St && elt_StStart && elt_StEnd)
  {
    status = elt_St.checked;
    elt_StStart.disabled = status;
    elt_StEnd.disabled = status;
    status = elt_St.checked || !(elt_StStart.checked);
    elt_HStart = document.getElementById("Event"+String(event)+"_HStart");
    if(elt_HStart) { elt_HStart.disabled = status; }
    elt_MStart = document.getElementById("Event"+String(event)+"_MStart")
    if(elt_MStart) { elt_MStart.disabled = status; }
    status = elt_St.checked || !(elt_StEnd.checked);
    elt_HEnd = document.getElementById("Event"+String(event)+"_HEnd")
    if(elt_HEnd) { elt_HEnd.disabled = status; }
    elt_MEnd = document.getElementById("Event"+String(event)+"_MEnd")
    if(elt_MEnd) { elt_MEnd.disabled = status; }
  }
}

function lost_ev_xml_update(xml, event)
{
  var elt;

  lost_ck_update(xml, "Event"+String(event), "St");

  lost_ck_update(xml, "Event"+String(event), "rec1");
  lost_ck_update(xml, "Event"+String(event), "rec2");
  lost_ck_update(xml, "Event"+String(event), "rec3");
  lost_ck_update(xml, "Event"+String(event), "rec4");
  lost_ck_update(xml, "Event"+String(event), "rec5");
  lost_ck_update(xml, "Event"+String(event), "rec6");
  lost_ck_update(xml, "Event"+String(event), "rec0");

  elt = document.getElementById("Event"+String(event)+"_St");
  if(elt)
  {
    if(elt.checked==true)
    {
      lost_ck_update(xml, "Event"+String(event), "StStart");
      lost_select_update(xml, "Event"+String(event), "HStart");
      lost_select_update(xml, "Event"+String(event), "MStart");
      lost_ck_update(xml, "Event"+String(event), "StEnd");
      lost_select_update(xml, "Event"+String(event), "HEnd");
      lost_select_update(xml, "Event"+String(event), "MEnd");
    }
  }
  lost_ev_date_status_update(event);
}

function lost_ev_xml_get(xml)
{
  for(var i=0; i<EVENT_MAX; i++) { lost_ev_xml_update(xml, i); }
}

/* ************* SET ************************ */

function lost_ev_rec_set(event, rec, value)
{
  lost_set(url_ev+String(event)+"&rec="+String(rec)+"&value="+String(value));
}

function lost_ev_date_set(event)
{
  var elt_StStart;
  var elt_HStart;
  var elt_MStart;
  var elt_StEnd;
  var elt_HEnd;
  var elt_MEnd;
  elt_StStart = document.getElementById("Event"+String(event)+"_StStart");
  elt_HStart = document.getElementById("Event"+String(event)+"_HStart");
  elt_MStart = document.getElementById("Event"+String(event)+"_MStart");
  elt_StEnd = document.getElementById("Event"+String(event)+"_StEnd");
  elt_HEnd = document.getElementById("Event"+String(event)+"_HEnd");
  elt_MEnd = document.getElementById("Event"+String(event)+"_MEnd");
  if(elt_StStart && elt_HStart && elt_MStart && elt_StEnd && elt_HEnd && elt_MEnd)
  {
    lost_set(url_ev+String(event)+"&ss="+String(Number(elt_StStart.checked))+"&hs="+String(Number(elt_HStart.value))+"&ms="+String(Number(elt_MStart.value))+"&se="+String(Number(elt_StEnd.checked))+"&he="+String(Number(elt_HEnd.value))+"&me="+String(Number(elt_MEnd.value)));
  }
}

function lost_ev_status_set(event)
{
  var elt;
  elt = document.getElementById("Event"+String(event)+"_St");
  if(elt)
  {
    if(elt.checked == true)
    {
      lost_ev_date_set(event);
    }
    lost_set(url_ev+String(event)+"&status="+String(Number(elt.checked)));
  }
  lost_ev_date_status_update(event);
}
document.write("\
<div class=\"iLayer\" id=\"waHome\" title=\"Home\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li id=\"Event"+String(EVENT_POWER_1)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Event"+String(EVENT_POWER_1)+"_Status\">Unknown</span>Reseau</li>\
            <li id=\"Alarm_bg\"><a href=\"#_Alarmes\"><img class=\"picto\" src=\""+lost_icons_path+"detector.jpg\"/>Alarmes</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Event"+String(EVENT_SHUTTERS_ALL)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_ALL        , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_ALL        , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\"><span id=\"Event"+String(EVENT_SHUTTERS_ALL)+"_Status\">Unknown</span>Tous les Volets</li>\
            <li id=\"Event"+String(EVENT_SHUTTERS_UPSTAIRS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_UPSTAIRS   , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_UPSTAIRS   , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Event"+String(EVENT_SHUTTERS_UPSTAIRS)+"_Status\">Unknown</span>Volets Etage</li>\
            <li id=\"Event"+String(EVENT_SHUTTERS_DOWNSTAIRS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DOWNSTAIRS , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DOWNSTAIRS , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"canape.jpg\"><span id=\"Event"+String(EVENT_SHUTTERS_DOWNSTAIRS)+"_Status\">Unknown</span>Volets Rez de Chaussé</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Room"+String(ROOM_SALON)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter0_Status\">Unknown</span>Salon Grande Baie</li>\
            <li id=\"Room"+String(ROOM_SALON)+"_Shutter1_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter1_Status\">Unknown</span>Salon Petite Baie</li>\
            <li id=\"Room"+String(ROOM_SALON)+"_Shutter2_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter2_Status\">Unknown</span>Salon Simple Baie</li>\
            <li id=\"Room"+String(ROOM_CUISINE)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_CUISINE)+"_Shutter0_Status\">Unknown</span>Cuisine</li>\
            <li id=\"Room"+String(ROOM_BUREAU)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_BUREAU)+"_Shutter0_Status\">Unknown</span>Bureau</li>\
            <li id=\"Room"+String(ROOM_C1)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C1)+"_Shutter0_Status\">Unknown</span>Marine</li>\
            <li id=\"Room"+String(ROOM_C2)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C2)+"_Shutter0_Status\">Unknown</span>M&M</li>\
            <li id=\"Room"+String(ROOM_C3)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C3)+"_Shutter0_Status\">Unknown</span>Amis</li>\
            <li id=\"Room"+String(ROOM_C4)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C4)+"_Shutter0_Status\">Unknown</span>Dressing</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Scenes_bg\"><a href=\"#_Scenes\"><img class=\"picto\" src=\""+lost_icons_path+"scenes.jpg\" alt=\"Scenes\">Scenes</a></li>\
            <li><a href=\"#_Evenements\"><img class=\"picto\" src=\""+lost_icons_path+"wakeup.jpg\"/>Evenements</a></li>\
            <li id=\"Rooms_bg\"><a href=\"#_Rooms\"><img class=\"picto\" src=\""+lost_icons_path+"home.jpg\" alt=\"Home\">Rooms</a></li>\
            <li id=\"Media_bg\"><a href=\"#_Media\"><img class=\"picto\" src=\""+lost_icons_path+"media.jpg\" alt=\"Media\">Media</a></li>\
            <li class=\"iRadio\"><img class=\"picto\" src=\""+lost_icons_path+"ambiance.jpg\"/>Ambiances\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_CINEMA);\">Cinema</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ROMANTIQUE);\">Romantique</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ECO);\">Economie d\"energie</label>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Safety_bg\"><a href=\"#_Surveillances\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"/>Surveillances</a></li>\
            <li><a href=\"cgi/monitor.cgi\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"system.jpg\" alt=\"System\">System</a></li>\
        </ul>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waMedia\" title=\"Media\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li><a href=\"tv.asp\"><img class=\"picto\" src=\""+lost_icons_path+"tv.jpg\" alt=\"TV\">TV</a></li>\
            <li><a href=\"freebox.asp\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"fb.jpg\" alt=\"FB\">Freebox</a></li>\
            <li><a href=\"sat.asp\"><img class=\"picto\" src=\""+lost_icons_path+"sat.jpg\" alt=\"Sat\">Satellite</a></li>\
            <li><a href=\"hifi.asp\"><img class=\"picto\" src=\""+lost_icons_path+"hifi.jpg\" alt=\"Hifi\">Hifi</a></li>\
        </ul>\
    </div>\
</div>\
");
document.write("\
");
document.write("\
<div class=\"iLayer\" id=\"waAlarmes\" title=\"Alarmes\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Alarmes</legend>\
            <ul class=\"iArrow\">\
                <li id=\"Alarm_Perimeter_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Perimeter_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_perimeter_set();\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><label for=\"Alarm_Perimeter_Ctrl\">Perimetrique</label><span id=\"Alarm_Perimeter_Status\">Unknown</span></li>\
                <li id=\"Alarm_Volume_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Volume_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_volume_set();\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><label for=\"Alarm_Volume_Ctrl\">Volumetrique</label><span id=\"Alarm_Volume_Status\">Unknown</span></li>\
                <li id=\"Alarm_Simulation_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Simulation_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_simulation_set();\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><label for=\"Alarm_Simulation_Ctrl\">Simulation de presence</label><span id=\"Alarm_Simulation_Status\">Unknown</span></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_AlarmesInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waAlarmesInfo\" title=\"Alarmes Info\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul>\
                <li id=\"Alarm_Perimeter_bg\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Alarm_Perimeter\">Unknown</span>Perimetrique</li>\
                <li id=\"Alarm_Volume_bg\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Alarm_Volume\">Unknown</span>Volumetrique</li>\
                <li id=\"Alarm_Simulation_bg\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><span id=\"Alarm_Simulation\">Unknown</span>Simulation de presence</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waScenes\" title=\"Scenes\">\
    <div class=\"iMenu\">\
        <legend>Volets</legend>\
        <ul class=\"iArrow\">\
            <li id=\"Scene"+String(EVENT_SHUTTERS_ALL)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_ALL               , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_ALL        , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_ALL)+"_Status\">Unknown</span>Tous</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_UPSTAIRS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_UPSTAIRS     , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_UPSTAIRS   , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_UPSTAIRS)+"_Status\">Unknown</span>Etage</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_DOWNSTAIRS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DOWNSTAIRS , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DOWNSTAIRS , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"canape.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_DOWNSTAIRS)+"_Status\">Unknown</span>Rez de Chaussé</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_MARINE)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_MARINE         , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_MARINE     , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_MARINE)+"_Status\">Unknown</span>Marine</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_MM)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_MM                 , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_MM         , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_MM)+"_Status\">Unknown</span>M&M</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_FRIENDS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_FRIENDS       , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_FRIENDS    , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_FRIENDS)+"_Status\">Unknown</span>Amis</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_DRESSING)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DRESSING     , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DRESSING   , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"dressing.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_DRESSING)+"_Status\">Unknown</span>Dressing</li>\
        </ul>\
        <legend>Alarme</legend>\
        <ul class=\"iArrow\">\
            <li id=\"Scene"+String(EVENT_ALARM_ALL)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_ALARM_ALL                        , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_ALL            , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Scene"+String(EVENT_ALARM_ALL)+"_Status\">Unknown</span>Toutes</li>\
            <li id=\"Scene"+String(EVENT_ALARM_PERIMETER)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER            , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER      , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Scene"+String(EVENT_ALARM_PERIMETER)+"_Status\">Unknown</span>Périmétrique</li>\
            <li id=\"Scene"+String(EVENT_ALARM_PERIMETER_CHECK)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER_CHECK, EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER_CHECK, EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Scene"+String(EVENT_ALARM_PERIMETER_CHECK)+"_Status\">Unknown</span>Périmétrique Auto</li>\
            <li id=\"Scene"+String(EVENT_ALARM_VOLUME)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_ALARM_VOLUME                  , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_VOLUME         , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Scene"+String(EVENT_ALARM_VOLUME)+"_Status\">Unknown</span>Volumétrique</li>\
            <li id=\"Scene"+String(EVENT_SIMU)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SIMU                                  , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SIMU                 , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><span id=\"Scene"+String(EVENT_SIMU)+"_Status\">Unknown</span>Simulation Présence</li>\
        </ul>\
        <legend>Power</legend>\
        <ul class=\"iArrow\">\
            <li id=\"Scene"+String(EVENT_POWER_0)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Scene"+String(EVENT_POWER_0)+"_Status\">Unknown</span>Wifi</li>\
            <li id=\"Scene"+String(EVENT_POWER_1)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Scene"+String(EVENT_POWER_1)+"_Status\">Unknown</span>Reseau</li>\
            <li id=\"Scene"+String(EVENT_POWER_2)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Scene"+String(EVENT_POWER_2)+"_Status\">Unknown</span>POWER 2</li>\
            <li id=\"Scene"+String(EVENT_POWER_3)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Scene"+String(EVENT_POWER_3)+"_Status\">Unknown</span>POWER 3</li>\
        </ul>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waSurveillances\" title=\"Surveillances\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Rooms</legend>\
            <ul>\
                <li id=\"Safety_Rooms_Error_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Error_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_error_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"error.jpg\"><label for=\"Safety_Rooms_Error_Ctrl\">Rooms Error</label></li>\
                <li id=\"Safety_Rooms_Temp_Max_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Temp_Max_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_temp_max_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_Rooms_Temp_Max_Ctrl\">Rooms Temperatures Max</label></li>\
                <li id=\"Safety_Rooms_Temp_Min_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Temp_Min_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_temp_min_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_Rooms_Temp_Min_Ctrl\">Rooms Temperatures Min</label></li>\
                <li id=\"Safety_Rooms_Hum_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Hum_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_hum_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\"><label for=\"Safety_Rooms_Hum_Ctrl\">Rooms Humidites</label></li>\
                <li id=\"Safety_Rooms_Smoke_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Smoke_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_smoke_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"gaz.jpg\"><label for=\"Safety_Rooms_Smoke_Ctrl\">Rooms Fumees</label></li>\
            </ul>\
            <legend>Centrale</legend>\
            <ul>\
                <li id=\"Safety_UPS_Temp_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_UPS_Temp_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_ups_temp_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_UPS_Temp_Ctrl\">UPS Temperature</label></li>\
                <li id=\"Safety_UPS_Power_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_UPS_Power_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_ups_power_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><label for=\"Safety_UPS_Power_Ctrl\">UPS Power</label></li>\
                <li id=\"Safety_RACK_Temp_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_RACK_Temp_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rack_temp_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_RACK_Temp_Ctrl\">RACK Temperature</label></li>\
                <li id=\"Safety_RACK_Alarm_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_RACK_Alarm_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rack_alarm_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><label for=\"Safety_RACK_Alarm_Ctrl\">RACK Alarm</label></li>\
                <li id=\"Safety_HTTP_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_HTTP_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_http_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><label for=\"Safety_HTTP_Ctrl\">Connexion Internet</label></li>\
                <li id=\"Safety_GSM_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_GSM_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_gsm_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"sat.jpg\"><label for=\"Safety_GSM_Ctrl\">Reseau GSM</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_SafetyInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waSafetyInfo\" title=\"Surveillances Info\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul>\
                <li id=\"Safety_Rooms_Error_bg\"><img class=\"picto\" src=\""+lost_icons_path+"error.jpg\"><span id=\"Safety_Rooms_Error\">Unknown</span>Rooms Error</li>\
                <li id=\"Safety_Rooms_Temp_Max_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_Rooms_Temp_Max\">Unknown</span>Rooms Temperature Max</li>\
                <li>Rooms Temperature Max Threshold\
                <SELECT id=\"Safety_Rooms_Temp_Max_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_Rooms_Temp_Max_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_Rooms_Temp_Min_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_Rooms_Temp_Min\">Unknown</span>Rooms Temperature Min</li>\
                <li>Rooms Temperature Min Threshold\
                <SELECT id=\"Safety_Rooms_Temp_Min_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_Rooms_Temp_Min_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_Rooms_Hum_bg\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\"><span id=\"Safety_Rooms_Hum\">Unknown</span>Rooms Humidity</li>\
                <li id=\"Safety_Rooms_Smoke_bg\"><img class=\"picto\" src=\""+lost_icons_path+"gaz.jpg\"><span id=\"Safety_Rooms_Smoke\">Unknown</span>Rooms Smoke</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <ul>\
                <li id=\"Safety_UPS_Temp_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_UPS_Temp\">Unknown</span>UPS Temperature</li>\
                <li>UPS Temperature Threshold\
                <SELECT id=\"Safety_UPS_Temp_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_UPS_Temp_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_UPS_Power_bg\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Safety_UPS_Power\">Unknown</span>UPS Power</li>\
                <li id=\"Safety_RACK_Temp_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_RACK_Temp\">Unknown</span>RACK Temperature</li>\
                <li>RACK Temperature Threshold\
                <SELECT id=\"Safety_RACK_Temp_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_RACK_Temp_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_RACK_Alarm_bg\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Safety_RACK_Alarm\">Unknown</span>RACK Alarm</li>\
                <li id=\"Safety_HTTP_bg\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Safety_HTTP\">Unknown</span>Connexion Internet</li>\
                <li id=\"Safety_GSM_bg\"><img class=\"picto\" src=\""+lost_icons_path+"sat.jpg\"><span id=\"Safety_GSM\">Unknown</span>Reseau GSM</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waRooms\" title=\"Rooms\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li><a href=\""+lost_icons_path+"plan.jpg\"><img class=\"picto\" src=\""+lost_icons_path+"loc.jpg\">Plan</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Room"+String(ROOM_SALON)+"_bg\"><a href=\"#_Salon\"><img class=\"picto\" src=\""+lost_icons_path+"canape.jpg\">Salon</a></li>\
            <li id=\"Room"+String(ROOM_CUISINE)+"_bg\"><a href=\"#_Cuisine\"><img class=\"picto\" src=\""+lost_icons_path+"cuisine.jpg\">Cuisine</a></li>\
            <li id=\"Room"+String(ROOM_BUREAU)+"_bg\"><a href=\"#_Bureau\"><img class=\"picto\" src=\""+lost_icons_path+"bureau.jpg\">Bureau</a></li>\
            <li id=\"Room"+String(ROOM_TERRASSE)+"_bg\"><a href=\"#_Terrasse\"><img class=\"picto\" src=\""+lost_icons_path+"terrasse.jpg\">Terrasse</a></li>\
            <li id=\"Room"+String(ROOM_C1)+"_bg\"><a href=\"#_C1\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre Marine</a></li>\
            <li id=\"Room"+String(ROOM_C2)+"_bg\"><a href=\"#_C2\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre M&M</a></li>\
            <li id=\"Room"+String(ROOM_C3)+"_bg\"><a href=\"#_C3\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre Amis</a></li>\
            <li id=\"Room"+String(ROOM_C4)+"_bg\"><a href=\"#_C4\"><img class=\"picto\" src=\""+lost_icons_path+"dressing.jpg\">Dressing</a></li>\
            <li id=\"Room"+String(ROOM_SDB)+"_bg\"><a href=\"#_Sdb\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\">Salle de Bain</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"http://lebomb.free.fr/LOST/charts/index_mms.php\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\">Courbes de temperature</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_Cameras\"><img class=\"picto\" src=\""+lost_icons_path+"cam.jpg\">Cameras</a></li>\
        </ul>\
        <ul>\
            <li><a href=\"javascript:lost_room_light_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_light_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumieres</li>\
            <li><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_MAX+3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_MAX+3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</li>\
            <li><a href=\"javascript:lost_room_elec_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_elec_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Eqpts Electriques</li>\
        </ul>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waSalon\" title=\"Salon\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>LEDs</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_CUISINE)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_CUISINE,0);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_CUISINE)+"_Light0\">Gauche</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_CUISINE)+"_Light1\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_CUISINE,1);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_CUISINE)+"_Light1\">Centre</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_CUISINE)+"_Light2\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_CUISINE,2);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_CUISINE)+"_Light2\">Droite</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Grande Baie</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Petite Baie</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Simple</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_SalonInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
		<div class=\"iLayer\" id=\"waCuisine\" title=\"Cuisine\">\
		    <div class=\"iMenu\">\
		    <div class=\"iPanel\">\
		        <fieldset>\
		            <legend>Lumieres</legend>\
		            <ul>\
		                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_COULOIR)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_COULOIR,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_COULOIR)+"_Light0\">Plafond</label></li>\
		            </ul>\
		        </fieldset>\
		        <fieldset>\
		            <legend>Ouvertures</legend>\
		            <ul>\
		                <li><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
		            </ul>\
		        </fieldset>\
		        <fieldset>\
		            <legend>Info</legend>\
		            <ul class=\"iArrow\">\
		                <li><a href=\"#_CuisineInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
		            </ul>\
		        </fieldset>\
		    </div>\
		    </div>\
		</div>\
		");
document.write("\
<div class=\"iLayer\" id=\"waBureau\" title=\"Bureau\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_COULOIR)+"_Light1\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_COULOIR,1);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_COULOIR)+"_Light1\">Plafond</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_COULOIR)+"_Light2\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_COULOIR,2);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_COULOIR)+"_Light2\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_BureauInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waTerrasse\" title=\"Terrasse\">\
		    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_TERRASSE)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_TERRASSE,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_TERRASSE)+"_Light0\">Phare</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_TerrasseInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC1\" title=\"Chambre Marine\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C1)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C1,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C1)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Climatisation</legend>\
            <ul>\
                <li>Temperature\
                <SELECT id=\"Room"+String(ROOM_C1)+"_Clim_Temp\"><script language=\"Javascript\">printSelectOption(\"Room"+String(ROOM_C1)+"_Clim_Temp\",99);</script></SELECT>\
                </li>\
                <li><a href=\"javascript:lost_room_clim_set(ROOM_C1,ROOM_CLIM_ON);\" class=\"iButton iBAction\" style=\"width:60px\">ON</a><a href=\"javascript:lost_room_clim_set(ROOM_C1,ROOM_CLIM_OFF);\" class=\"iButton iBWarn\" style=\"width:60px\">OFF</a><img class=\"picto\" src=\""+lost_icons_path+"clim.jpg\">Commande</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Chambre MarineInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC2\" title=\"Chambre M&M\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C2)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C2,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C2)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Chambre M&MInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC3\" title=\"Chambre Amis\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C3)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C3,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C3)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Chambre AmisInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC4\" title=\"Dressing\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C4)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C4,0,this);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C4)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_DressingInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waSdb\" title=\"Salle de Bain\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SDB)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SDB,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_SDB)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_SDBInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waCameras\" title=\"Cameras\">\
    <div class=\"iMenu\">\
        <ul>\
            <li><a href=\"http://bourdilot.no-ip.info:81\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V2_2.jpg\">Salle a manger</a></li>\
            <li><a href=\"http://bourdilot.no-ip.info:82\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V2_2.jpg\">Bureau</a></li>\
            <li><a href=\"http://bourdilot.no-ip.info:83\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"wvc54gca.jpg\">Exterieur</a></li>\
        </ul>\
    </div>\
</div>\
");

function printRoomInfo(room, name)
{
document.write("\
<div class=\"iLayer\" id=\"wa"+name+"Info\" title=\""+name+"\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul>\
                <li id=\"Room"+String(room)+"_Error_bg\"><span id=\"Room"+String(room)+"_Error_Trig\">Unknown</span>Error</li>\
            </ul>\
            <ul>\
                <li><span id=\"Room"+String(room)+"_Type\">Unknown</span>Type</li>\
                <li><span id=\"Room"+String(room)+"_Version\">Unknown</span>Version</li>\
                <li><span id=\"Room"+String(room)+"_Adress\">Unknown</span>Adresse</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Temp_Max_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Max\">Unknown</span>Temperature Max</li>\
                <li id=\"Room"+String(room)+"_Temp_Max_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Max_Ctrl\">Unknown</span>Temperature Max Control</li>\
                <li id=\"Room"+String(room)+"_Temp_Max_Th_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Max_Th\">Unknown</span>Temperature Max Threshold</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Temp_Min_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Min\">Unknown</span>Temperature Min</li>\
                <li id=\"Room"+String(room)+"_Temp_Min_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Min_Ctrl\">Unknown</span>Temperature Min Control</li>\
                <li id=\"Room"+String(room)+"_Temp_Min_Th_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Min_Th\">Unknown</span>Temperature Min Threshold</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Hum_bg\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\"><span id=\"Room"+String(room)+"_Hum\">Unknown</span>Humidite</li>\
                <li id=\"Room"+String(room)+"_Hum_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\"><span id=\"Room"+String(room)+"_Hum_Ctrl\">Unknown</span>Humidite Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Smoke_bg\"><img class=\"picto\" src=\""+lost_icons_path+"gaz.jpg\"><span id=\"Room"+String(room)+"_Smoke\">Unknown</span>Smoke</li>\
                <li id=\"Room"+String(room)+"_Smoke_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"gaz.jpg\"><span id=\"Room"+String(room)+"_Smoke_Ctrl\">Unknown</span>Smoke Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Perimeter_bg\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Room"+String(room)+"_Perimeter\">Unknown</span>Perimeter</li>\
                <li id=\"Room"+String(room)+"_Perimeter_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Room"+String(room)+"_Perimeter_Ctrl\">Unknown</span>Perimeter Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Volume_bg\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Room"+String(room)+"_Volume\">Unknown</span>Volume</li>\
                <li id=\"Room"+String(room)+"_Volume_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Room"+String(room)+"_Volume_Ctrl\">Unknown</span>Volume Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Simulation_bg\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><span id=\"Room"+String(room)+"_Simulation\">Unknown</span>Simulation</li>\
                <li id=\"Room"+String(room)+"_Simulation_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><span id=\"Room"+String(room)+"_Simulation_Ctrl\">Unknown</span>Simulation Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Clim_Cmd_bg\"><img class=\"picto\" src=\""+lost_icons_path+"clim.jpg\"><span id=\"Room"+String(room)+"_Clim_Cmd\">Unknown</span>Climatisation</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
}

printRoomInfo(ROOM_SALON   , "Salon"         );
printRoomInfo(ROOM_CUISINE , "Cuisine"       );
printRoomInfo(ROOM_BUREAU  , "Bureau"        );
printRoomInfo(ROOM_TERRASSE, "Terrasse"      );
printRoomInfo(ROOM_C1      , "Chambre Marine");
printRoomInfo(ROOM_C2      , "Chambre M&M"   );
printRoomInfo(ROOM_C3      , "Chambre Amis"  );
printRoomInfo(ROOM_C4      , "Dressing"      );
printRoomInfo(ROOM_SDB     , "SDB"           );
document.write("\
<div class=\"iLayer\" id=\"waEvenements\" title=\"Evenements\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Volets</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_ALL+"\"><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Tous</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_UPSTAIRS+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Etage</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_DOWNSTAIRS+"\"><img class=\"picto\" src=\""+lost_icons_path+"canape.jpg\">Rez de Chaussé</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_MARINE+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Marine</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_MM+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">M&M</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_FRIENDS+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Amis</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_DRESSING+"\"><img class=\"picto\" src=\""+lost_icons_path+"dressing.jpg\">Dressing</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Alarme</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_ALARM_ALL+"\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\">Toutes</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_PERIMETER+"\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\">Périmétrique</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_PERIMETER_CHECK+"\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\">Périmétrique Auto</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_VOLUME+"\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\">Volumétrique</a></li>\
                <li><a href=\"#_Event"+EVENT_SIMU+"\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\">Simulation Presence</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Power</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_POWER_0+"\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Wifi</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_1+"\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Ethernet</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_2+"\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Power 2</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_3+"\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Power 3</a></li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");

function printEventInfo(event, name)
{
document.write("\
<div class=\"iLayer\" id=\"waEvent"+event+"\" title=\""+name+"\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_St\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_status_set("+String(event)+");\"><label for=\"Event"+String(event)+"_St\">Status</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Recurrences</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec1\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 1, Number(checked));\"><label for=\"Event"+String(event)+"_rec1\">Lundi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec2\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 2, Number(checked));\"><label for=\"Event"+String(event)+"_rec2\">Mardi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec3\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 3, Number(checked));\"><label for=\"Event"+String(event)+"_rec3\">Mercredi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec4\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 4, Number(checked));\"><label for=\"Event"+String(event)+"_rec4\">Jeudi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec5\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 5, Number(checked));\"><label for=\"Event"+String(event)+"_rec5\">Vendredi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec6\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 6, Number(checked));\"><label for=\"Event"+String(event)+"_rec6\">Samedi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 0, Number(checked));\"><label for=\"Event"+String(event)+"_rec0\">Dimanche</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Horloges</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_StStart\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_date_status_update("+String(event)+");\"><label for=\"Event"+String(event)+"_StStart\">Depart : Heure / Minute</label></li>\
                <li>\
                <SELECT id=\"Event"+String(event)+"_HStart\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_HStart\",24);</script></SELECT>\
                <SELECT id=\"Event"+String(event)+"_MStart\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_MStart\",60);</script></SELECT>\
                </li>\
            </ul>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_StEnd\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_date_status_update("+String(event)+");\"><label for=\"Event"+String(event)+"_StEnd\">Fin : Heure / Minute</label></li>\
                <li>\
                <SELECT id=\"Event"+String(event)+"_HEnd\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_HEnd\",24);</script></SELECT>\
                <SELECT id=\"Event"+String(event)+"_MEnd\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_MEnd\",60);</script></SELECT>\
                </li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
}

printEventInfo(EVENT_SHUTTERS_ALL         , "Tous"               );
printEventInfo(EVENT_SHUTTERS_UPSTAIRS    , "Etage"              );
printEventInfo(EVENT_SHUTTERS_DOWNSTAIRS  , "Rez de Chaussé"     );
printEventInfo(EVENT_SHUTTERS_MARINE      , "Marine"             );
printEventInfo(EVENT_SHUTTERS_MM          , "M&M"                );
printEventInfo(EVENT_SHUTTERS_FRIENDS     , "Amis"               );
printEventInfo(EVENT_SHUTTERS_DRESSING    , "Dressing"           );
printEventInfo(EVENT_ALARM_ALL            , "Toutes"             );
printEventInfo(EVENT_ALARM_PERIMETER_CHECK, "Perimetrique"       );
printEventInfo(EVENT_ALARM_PERIMETER      , "Perimetrique Auto"  );
printEventInfo(EVENT_ALARM_VOLUME         , "Volumetrique"       );
printEventInfo(EVENT_SIMU                 , "Simulation Presence");
printEventInfo(EVENT_POWER_0              , "Wifi"               );
printEventInfo(EVENT_POWER_1              , "Ethernet"           );
printEventInfo(EVENT_POWER_2              , "Power 2"            );
printEventInfo(EVENT_POWER_3              , "Power 3"            );
