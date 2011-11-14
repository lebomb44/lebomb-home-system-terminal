var lost_path = "http://lebomb.free.fr/MM/";
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
  //var i = document.getElementsByTagName(elt);
  //if(i)
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
  var i;
  document.getElementById(id).length = nb;
  for(i=0; i<nb; i++)
  {
    document.getElementById(id).options[i].value = i;
    document.getElementById(id).options[i].text = String(i);
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
document.write("\
<div class=\"iLayer\" id=\"waHome\" title=\"Home\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li id=\"Media_bg\"><a href=\"#_Media\"><img class=\"picto\" src=\""+lost_icons_path+"media.jpg\" alt=\"Media\">Media</a></li>\
            <li id=\"Rooms_bg\"><a href=\"#_Rooms\"><img class=\"picto\" src=\""+lost_icons_path+"home.jpg\" alt=\"Home\">Rooms</a></li>\
            <li id=\"Scenes_bg\"><a href=\"#_Scenes\"><img class=\"picto\" src=\""+lost_icons_path+"scenes.jpg\" alt=\"Scenes\">Scenes</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Safety_bg\"><a href=\"#_Surveillances\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"/>Surveillances</a></li>\
            <li id=\"Alarm_bg\"><a href=\"#_Alarmes\"><img class=\"picto\" src=\""+lost_icons_path+"detector.jpg\"/>Alarmes</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
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
var url_alarm="cgi/alarm.cgi?";

function lost_alarm_perimeter_set()
{
  lost_set(url_alarm+"perimeter_ctrl="+String(Number(document.getElementById("Alarm_Perimeter_Ctrl").checked)));
}

function lost_alarm_volume_set()
{
  lost_set(url_alarm+"volume_ctrl="+String(Number(document.getElementById("Alarm_Volume_Ctrl").checked)));
}

function lost_alarm_simulation_set()
{
  lost_set(url_alarm+"simulation_ctrl="+String(Number(document.getElementById("Alarm_Simulation_Ctrl").checked)));
}

function lost_alarm_xml_get(xml)
{
  lost_elt_bool_update(xml, "Alarm", "Perimeter");
  lost_elt_bool_update(xml, "Alarm", "Volume");
  lost_elt_bool_update(xml, "Alarm", "Simulation");
}
document.write("\
<div class=\"iLayer\" id=\"waAlarmes\" title=\"Alarmes\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Alarmes</legend>\
            <ul class=\"iArrow\">\
                <li id=\"Alarm_Perimeter_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Perimeter_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_perimeter_set();\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><label for=\"Alarm_Perimeter_Ctrl\">Perimetrique</label></li>\
                <li id=\"Alarm_Volume_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Volume_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_volume_set();\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><label for=\"Alarm_Volume_Ctrl\">Volumetrique</label></li>\
                <li id=\"Alarm_Simulation_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Simulation_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_simulation_set();\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><label for=\"Alarm_Simulation_Ctrl\">Simulation de presence</label></li>\
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
var ATM_UNKNOWN    = 0;
var ATM_CINEMA     = 1;
var ATM_ROMANTIQUE = 2;
var ATM_ECO        = 3;
var url_atm="cgi/atm.cgi?atm=";

function lost_atm_set(atm)
{
  lost_set(url_atm+String(atm));
}
document.write("\
<div class=\"iLayer\" id=\"waScenes\" title=\"Scenes\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li class=\"iRadio\"><img class=\"picto\" src=\""+lost_icons_path+"ambiance.jpg\"/>Ambiances\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_CINEMA);\">Cinema</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ROMANTIQUE);\">Romantique</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ECO);\">Economie d\"energie</label>\
            </li>\
            <li><a href=\"#_Evenements\"><img class=\"picto\" src=\""+lost_icons_path+"wakeup.jpg\"/>Evenements</a></li>\
        </ul>\
    </div>\
</div>\
");
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
                <li id=\"Safety_HTTP_bg\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Safety_HTTP\">Unknown</span>Connexion Internet</li>\
                <li id=\"Safety_GSM_bg\"><img class=\"picto\" src=\""+lost_icons_path+"sat.jpg\"><span id=\"Safety_GSM\">Unknown</span>Reseau GSM</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
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
            <li id=\"Room"+String(ROOM_WC)+"_bg\"><a href=\"#_Wc\"><img class=\"picto\" src=\""+lost_icons_path+"wc.jpg\">WC</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_Cameras\"><img class=\"picto\" src=\""+lost_icons_path+"cam.jpg\">Cameras</a></li>\
        </ul>\
        <ul>\
            <li><a href=\"javascript:lost_room_light_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_light_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumieres</li>\
            <li><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            <li><a href=\"javascript:lost_room_heater_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_heater_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</li>\
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
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light2\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,2);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light2\">Gauche</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light3\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,3);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light3\">Centre</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light4\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,4);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light4\">Droite</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Grande Baie</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Petite Baie</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,3,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,3,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Simple</li>\
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
		                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_CUISINE)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_CUISINE,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_CUISINE)+"_Light0\">Plafond</label></li>\
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
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_BUREAU)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_BUREAU,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_BUREAU)+"_Light0\">Plafond</label></li>\
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
<div class=\"iLayer\" id=\"waWc\" title=\"WC\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_WC)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_WC,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_WC)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_WC,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_WC,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_WC,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_WC,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_WC,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_WC,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_WCInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
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
            <li><a href=\"http://bourdilot.no-ip.info:81\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden.jpg\">Salle a manger</a></li>\
            <li><a href=\"http://bourdilot.no-ip.info:82\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden.jpg\">Bureau</a></li>\
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
printRoomInfo(ROOM_WC      , "WC"            );
var SCENE_REVEIL         = 0;
var SCENE_COUCHE         = 1;
var SCENE_CHAUFFAGE_SDB  = 2;
var SCENE_CHAUFFAGE_CAFE = 3;
var SCENE_LUMIERE_AUTO   = 4;
var SCENE_MUSIQUE_AUTO   = 5;
var url_ev="cgi/scenes.cgi?scene=";

function lost_ev_date_status_update(event)
{
  var status = document.getElementById("Event"+String(event)+"_St").checked;
  document.getElementById("Event"+String(event)+"_HStart").disabled=status;
  document.getElementById("Event"+String(event)+"_MStart").disabled=status;
  document.getElementById("Event"+String(event)+"_HEnd").disabled=status;
  document.getElementById("Event"+String(event)+"_MEnd").disabled=status;
}

function lost_ev_xml_update(xml, event)
{
  lost_ck_update(xml, "Event"+String(event), "St");

  lost_ck_update(xml, "Event"+String(event), "rec1");
  lost_ck_update(xml, "Event"+String(event), "rec2");
  lost_ck_update(xml, "Event"+String(event), "rec3");
  lost_ck_update(xml, "Event"+String(event), "rec4");
  lost_ck_update(xml, "Event"+String(event), "rec5");
  lost_ck_update(xml, "Event"+String(event), "rec6");
  lost_ck_update(xml, "Event"+String(event), "rec0");

  if(document.getElementById("Event"+String(event)+"_St").checked==true)
  {
    lost_select_update(xml, "Event"+String(event), "HStart");
    lost_select_update(xml, "Event"+String(event), "MStart");
    lost_select_update(xml, "Event"+String(event), "HEnd");
    lost_select_update(xml, "Event"+String(event), "MEnd");
  }
  lost_ev_date_status_update(event);
}

function lost_ev_xml_get(xml)
{
  lost_ev_xml_update(xml, SCENE_REVEIL);
  lost_ev_xml_update(xml, SCENE_COUCHE);
  lost_ev_xml_update(xml, SCENE_CHAUFFAGE_SDB);
  lost_ev_xml_update(xml, SCENE_CHAUFFAGE_CAFE);
  lost_ev_xml_update(xml, SCENE_LUMIERE_AUTO);
  lost_ev_xml_update(xml, SCENE_MUSIQUE_AUTO);
}

/* ************* SET ************************ */

function lost_ev_rec_set(event, rec, value)
{
  lost_set(url_ev+String(event)+"&rec="+String(rec)+"&value="+String(value));
}

function lost_ev_date_set(event)
{
  lost_set(url_ev+String(event)+"&hs="+String(Number(document.getElementById("Event"+String(event)+"_HStart").value)));
  lost_set(url_ev+String(event)+"&ms="+String(Number(document.getElementById("Event"+String(event)+"_MStart").value)));
  lost_set(url_ev+String(event)+"&he="+String(Number(document.getElementById("Event"+String(event)+"_HEnd").value)));
  lost_set(url_ev+String(event)+"&me="+String(Number(document.getElementById("Event"+String(event)+"_MEnd").value)));
}

function lost_ev_status_set(event)
{
  lost_set(url_ev+String(event)+"&status="+String(Number(document.getElementById("Event"+String(event)+"_St").checked)));
  lost_ev_date_status_update(event);
  if(document.getElementById("Event"+String(event)+"_St").checked == true)
  {
    lost_ev_date_set(event);
  }
}
document.write("\
<div class=\"iLayer\" id=\"waEvenements\" title=\"Evenements\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Rooms</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+SCENE_REVEIL+"\"><img class=\"picto\" src=\""+lost_icons_path+"sunrise.jpg\">Reveil</a></li>\
                <li><a href=\"#_Event"+SCENE_COUCHE+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Couche</a></li>\
                <li><a href=\"#_Event"+SCENE_CHAUFFAGE_SDB+"\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\">Chauffage Salle de bain</a></li>\
                <li><a href=\"#_Event"+SCENE_CHAUFFAGE_CAFE+"\"><img class=\"picto\" src=\""+lost_icons_path+"coffee.jpg\">Chauffage Cafe</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Modes</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+SCENE_LUMIERE_AUTO+"\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumiere automatique</a></li>\
                <li><a href=\"#_Event"+SCENE_MUSIQUE_AUTO+"\"><img class=\"picto\" src=\""+lost_icons_path+"hifi.jpg\">Musique automatique</a></li>\
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
                <li>Depart : Heure / Minute\
                <SELECT id=\"Event"+String(event)+"_HStart\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_HStart\",24);</script></SELECT>\
                <SELECT id=\"Event"+String(event)+"_MStart\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_MStart\",60);</script></SELECT>\
                </li>\
            </ul>\
            <ul>\
                <li>Fin : Heure / Minute\
                <SELECT id=\"Event"+String(event)+"_HEnd\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_HEnd\",24);</script></SELECT>\
                <SELECT id=\"Event"+String(event)+"_MEnd\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_MEnd\",60);</script></SELECT>\
                </li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
}

printEventInfo(SCENE_REVEIL        , "Reveil"                 );
printEventInfo(SCENE_COUCHE        , "Couche"                 );
printEventInfo(SCENE_CHAUFFAGE_SDB , "Chauffage Salle de Bain");
printEventInfo(SCENE_CHAUFFAGE_CAFE, "Chauffage Cafe"         );
printEventInfo(SCENE_LUMIERE_AUTO  , "Lumiere automatique"    );
printEventInfo(SCENE_MUSIQUE_AUTO  , "Musique automatique"    );
