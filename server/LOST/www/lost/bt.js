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
      if(true == Boolean(Number(in_id2.firstChild.nodeValue)))
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
        if(true == Boolean(Number(in_id2.firstChild.nodeValue))) { lost_select_F2C_update(xml, node, id+"_Th"); }
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
          lost_lbcom_xml_get(xml);
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

  for(i=0; i<4; i++)
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
        if(1 == in_id2.firstChild.nodeValue)
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
      if(true == status)
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
      if(true == status)
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
      if(true == status)
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
      if(true == status)
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
var url_lbcom="cgi/lbcom.cgi?";
var url_lbcom_homeeasyTM="cgi/lbcom_homeeasyTC.cgi?";
var url_lbcom_homeeasyTC="cgi/lbcom_homeeasyTM.cgi?";
var url_lbcom_gsmTC="cgi/lbcom_gsmTC.cgi?";
var url_lbcom_gsmTM="cgi/lbcom_gsmTM.cgi?";
var url_lbcom_bourdilot_freezerTC="cgi/lbcom_bourdilot_freezerTC.cgi?";
var url_lbcom_bourdilot_freezerTM="cgi/lbcom_bourdilot_freezerTM.cgi?";

function lost_lbcom_xml_get(xml)
{
  lost_innerHTML_update(xml, "LbCom_HomeEasyTM", "Manufacturer");
  lost_innerHTML_update(xml, "LbCom_HomeEasyTM", "Group");
  lost_innerHTML_update(xml, "LbCom_HomeEasyTM", "Device");
  lost_innerHTML_update(xml, "LbCom_HomeEasyTM", "Status");
  lost_innerHTML_update(xml, "LbCom_GsmTM", "Init");
  lost_innerHTML_update(xml, "LbCom_GsmTM", "CheckPowerUp");
  lost_innerHTML_update(xml, "LbCom_GsmTM", "SignalStrength_status");
  lost_innerHTML_update(xml, "LbCom_GsmTM", "SignalStrength_value");
  lost_innerHTML_update(xml, "LbCom_Bourdilot_FreezerTM", "Network");
  lost_innerHTML_update(xml, "LbCom_Bourdilot_FreezerTM", "Temp");
}

/* ********** SET ********** */
function lost_lbcom_send()
{
  var src;
  src = document.getElementById("LbCom_Src");
  var dst;
  dst = document.getElementById("LbCom_Dst");
  var cmd;
  cmd = document.getElementById("LbCom_Cmd");
  var dataStr;
  dataStr = document.getElementById("LbCom_Data");
  var data;
  var len = 0;
  if("" == dataStr.value) { len = 0; }
  else
  {
    data = dataStr.value.split(" "); 
    len = data.length;
  }

  var url= url_lbcom+"src="+String(Number(src.value))+"&dst="+String(Number(dst.value))+"&cmd="+String(Number(cmd.value))+"&len="+String(len);
  if(src && dst && cmd && dataStr)
  {
    var i = 0;
    for(i=0; i<len; i++) { url = url + "&data" + ("000"+i).slice(-3) + "=" + String(Number(data[i])); }
    lost_set(url);
  }
}

function lost_lbcom_homeeasytm_codereset() { lost_set(url_lbcom_homeeasyTM+"code_reset=1"); }
function lost_lbcom_homeeasytm_manufacturer_set(manufacturer) { lost_set(url_lbcom_homeeasyTM+"manufacturer="+String(manufacturer)); }
function lost_lbcom_homeeasytm_group_set(group) { lost_set(url_lbcom_gsmTM+"group="+String(group)); }
function lost_lbcom_homeeasytm_device_set(device) { lost_set(url_lbcom_gsmTM+"device="+String(device)); }
function lost_lbcom_homeeasytm_status_set(status) { lost_set(url_lbcom_gsmTM+"status="+String(status)); }
function lost_lbcom_homeeasytc_send()
{
  var manufacturer;
  manufacturer = document.getElementById("HomeEasySend_Manufacturer");
  var group;
  group = document.getElementById("HomeEasySend_Group");
  var device;
  device = document.getElementById("HomeEasySend_Device");
  var status;
  status = document.getElementById("HomeEasySend_Status");

  if(manufacturer && group && device && status)
  {
    lost_set(url_lbcom_gsmTM+"send=1&manufacturer="+String(Number(manufacturer.value))+"&group="+String(Number(group.value))+"&device="+String(Number(device.value))+"&status="+String(Number(status.checked)));
  }
}

function lost_lbcom_gsmtm_init_set(init) { lost_set(url_lbcom_gsmTM+"init="+String(init)); }
function lost_lbcom_gsmtc_init_get() { lost_set(url_lbcom_gsmTC+"init=1"); }
function lost_lbcom_gsmtm_checkpowerup_set(checkpowerup) { lost_set(url_lbcom_gsmTM+"checkpowerup="+String(checkpowerup)); }
function lost_lbcom_gsmtc_checkpowerup_get() { lost_set(url_lbcom_gsmTC+"checkpowerup=1"); }
function lost_lbcom_gsmtm_signalstrength_set(status, value) { lost_set(url_lbcom_gsmTM+"signalstrength=1&status="+String(status)+"&value="+String(value)); }
function lost_lbcom_gsmtc_signalstrength_get() { lost_set(url_lbcom_gsmTC+"getsignalstrength=1"); }
function lost_lbcom_gsmtm_sendsms_status_set(status) { lost_set(url_lbcom_gsmTM+"sendsms="+String(status)); }
function lost_lbcom_gsmtc_sendsms()
{
  var phone;
  phone = document.getElementById("GsmSendSMS_Phone");
  var msg;
  msg = document.getElementById("GsmSendSMS_Msg");

  if(phone && msg)
  {
    lost_set(url_lbcom_gsmTC+"sendsms=1&phone="+String(phone.value)+"&msg="+String(msg.value));
  }
}

function lost_lbcom_bourdilot_freezertm_network_set(network) { lost_set(url_lbcom_bourdilot_freezerTM+"network="+String(network)); }
function lost_lbcom_bourdilot_freezertc_network_get() { lost_set(url_lbcom_bourdilot_freezerTC+"network=1"); }
function lost_lbcom_bourdilot_freezertm_temp_set(temp) { lost_set(url_lbcom_bourdilot_freezerTM+"temp="+String(temp)); }
function lost_lbcom_bourdilot_freezertc_temp_get() { lost_set(url_lbcom_bourdilot_freezerTC+"temp=1"); }

var ROOM_SHUTTER_UP   = 255
var ROOM_SHUTTER_STOP = 0
var ROOM_SHUTTER_DOWN = 1

var ROOM_CLIM_OFF = 0;
var ROOM_CLIM_ON  = 1;

var ROOM_C1       = 0;
var ROOM_C2       = 1;
var ROOM_C3       = 2;
var ROOM_C4       = 3;
var ROOM_COMBLES  = 4;
var ROOM_BUREAU   = 5;
var ROOM_SALON    = 6;
var ROOM_CUISINE  = 7;
var ROOM_COULOIR  = 8;
var ROOM_SALON2   = 9;
var ROOM_TERRASSE = 10;
var ROOM_MAX      = 11;
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
var EVENT_SHUTTERS_C1           = 3;
var EVENT_SHUTTERS_C2           = 4;
var EVENT_SHUTTERS_C3           = 5;
var EVENT_SHUTTERS_C4           = 6;
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
    if(true == elt.checked)
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
    if(true == elt.checked)
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
            <li id=\"Rooms_bg\"><a href=\"#_Rooms\"><img class=\"picto\" src=\""+lost_icons_path+"home.jpg\" alt=\"Home\">Rooms</a></li>\
            <li id=\"Scenes_bg\"><a href=\"#_Scenes\"><img class=\"picto\" src=\""+lost_icons_path+"scenes.jpg\" alt=\"Scenes\">Scenes</a></li>\
            <li><a href=\"#_Evenements\"><img class=\"picto\" src=\""+lost_icons_path+"wakeup.jpg\"/>Evenements</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Safety_bg\"><a href=\"#_Surveillances\"><img class=\"picto\" src=\""+lost_icons_path+"safety.jpg\"/>Surveillances</a></li>\
            <li id=\"Alarm_bg\"><a href=\"#_Alarmes\"><img class=\"picto\" src=\""+lost_icons_path+"detector.jpg\"/>Alarmes</a></li>\
            <li id=\"Communications_bg\"><a href=\"#_Communications\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"/>Communications</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"cgi/monitor.cgi\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"system.jpg\" alt=\"System\">System</a></li>\
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
        <legend>Power</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Wifi</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Ethernet</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">POWER 2</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">POWER 3</li>\
        </ul>\
        <legend>Alarm</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER_CHECK, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER_CHECK, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm check</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm perimeter</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_ALARM_VOLUME, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_VOLUME, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm volume</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_ALARM_ALL, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_ALL, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm all</li>\
        </ul>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waSurveillances\" title=\"Surveillances\">\
    <div class=\"iPanel\">\
        <fieldset>\
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
<div class=\"iLayer\" id=\"waCommunications\" title=\"Communications\">\
    <div class=\"iMenu\">\
        <legend>HomeEasy</legend>\
        <ul>\
            <li id=\"LbCom_HomeEasyTM_Manufacturer_bg\"><img class=\"picto\" src=\""+lost_icons_path+"manufacturer.jpg\"><span id=\"LbCom_HomeEasyTM_Manufacturer\">Unknown</span>Manufacturer</li>\
            <li id=\"LbCom_HomeEasyTM_Group_bg\"><img class=\"picto\" src=\""+lost_icons_path+"group.jpg\"><span id=\"LbCom_HomeEasyTM_Group\">Unknown</span>Group</li>\
            <li id=\"LbCom_HomeEasyTM_Device_bg\"><img class=\"picto\" src=\""+lost_icons_path+"device.jpg\"><span id=\"LbCom_HomeEasyTM_Device\">Unknown</span>Device</li>\
            <li id=\"LbCom_HomeEasyTM_Status_bg\"><img class=\"picto\" src=\""+lost_icons_path+"status.jpg\"><span id=\"LbCom_HomeEasyTM_Status\">Unknown</span>Status</li>\
            <li id=\"LbCom_HomeEasyTM_CodeReset_bg\"><a href=\"javascript:lost_lbcom_homeeasytm_codereset();\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"reset.jpg\"><span id=\"LbCom_HomeEasyTM_CodeReset\"></span>CodeReset</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_HomeEasySend\"><img class=\"picto\" src=\""+lost_icons_path+"send.jpg\"/>Send</a></li>\
        </ul>\
        <legend>GSM</legend>\
        <ul>\
            <li id=\"LbCom_GsmTM_Init_bg\"><a href=\"javascript:lost_lbcom_gsmtc_init_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_gsmtm_init_set(0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"init.jpg\"><span id=\"LbCom_GsmTM_Init\">Unknown</span>Init</li>\
            <li id=\"LbCom_GsmTM_CheckPowerUp_bg\"><a href=\"javascript:lost_lbcom_gsmtc_checkpowerup_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_gsmtm_checkpowerup_set(0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"powerup.jpg\"><span id=\"LbCom_GsmTM_CheckPowerUp\">Unknown</span>CheckPowerUp</li>\
            <li id=\"LbCom_GsmTM_SignalStrength_status_bg\"><a href=\"javascript:lost_lbcom_gsmtc_signalstrength_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_gsmtm_signalstrength_set(0, 0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"status.jpg\"><span id=\"LbCom_GsmTM_SignalStrength_status\">Unknown</span>Signal Strength Status</li>\
            <li id=\"LbCom_GsmTM_SignalStrength_value_bg\"><a href=\"javascript:lost_lbcom_gsmtc_signalstrength_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_gsmtm_signalstrength_set(0, 0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"signalstrength.jpg\"><span id=\"LbCom_GsmTM_SignalStrength_value\">Unknown</span>Signal Strength Value</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_GsmSendSMS\"><img class=\"picto\" src=\""+lost_icons_path+"send.jpg\"/>Send</a></li>\
        </ul>\
        <legend>Freezer</legend>\
        <ul>\
            <li id=\"LbCom_Bourdilot_FreezerTM_Network_bg\"><a href=\"javascript:lost_lbcom_bourdilot_freezertc_network_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_bourdilot_freezertm_network_set(0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"LbCom_Bourdilot_FreezerTM_Network\">Unknown</span>Network</li>\
            <li id=\"LbCom_Bourdilot_FreezerTM_Temp_bg\"><a href=\"javascript:lost_lbcom_bourdilot_freezertc_temp_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_bourdilot_freezertm_temp_set(444);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"LbCom_Bourdilot_FreezerTM_Temp\">Unknown</span>Temperature</li>\
        </ul>\
        <legend>LbCom</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_LbComSend\"><img class=\"picto\" src=\""+lost_icons_path+"send.jpg\"/>Send</a></li>\
        </ul>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waHomeEasySend\" title=\"Home Easy Send\">\
    <div class=\"iMenu\">\
        <legend>HomeEasy Code</legend>\
        <ul>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"manufacturer.jpg\"><label>Manufacturer</label><input type=\"text\" id=\"HomeEasySend_Manufacturer\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"group.jpg\"><label>Group</label><input type=\"text\" id=\"HomeEasySend_Group\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"device.jpg\"><label>Device</label><input type=\"text\" id=\"HomeEasySend_Device\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"status.jpg\"><input type=\"checkbox\" id=\"HomeEasySend_Status\" class=\"iToggle\" title=\"ON|OFF\"><label for=\"HomeEasySend_Status\">Status</label></li>\
        </ul>\
        <input type=\"button\" class=\"iPush iBCancel\" value=\"Send\" style=\"width:100%\" onClick=\"lost_lbcom_homeeasytc_send();\"/>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waGsmSendSMS\" title=\"Send SMS\">\
    <div class=\"iMenu\">\
        <legend>SMS</legend>\
        <ul>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"phone.jpg\"><label>Phone</label><input type=\"text\" id=\"GsmSendSMS_Phone\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"msg.jpg\"><label>Message</label><input type=\"text\" id=\"GsmSendSMS_Msg\"/></li>\
        </ul>\
        <input type=\"button\" class=\"iPush iBCancel\" value=\"Send\" style=\"width:100%\" onClick=\"lost_lbcom_gsmtc_sendsms();\"/>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waLbComSend\" title=\"LbCom Send\">\
    <div class=\"iMenu\">\
        <legend>LbCom Frame</legend>\
        <ul>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"out.jpg\"><label>Source</label><input type=\"text\" id=\"LbCom_Src\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"in.jpg\"><label>Destination</label><input type=\"text\" id=\"LbCom_Dst\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"cmd.jpg\"><label>Command</label><input type=\"text\" id=\"LbCom_Cmd\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"data.jpg\"><label>Data</label><input type=\"text\" id=\"LbCom_Data\"/></li>\
        </ul>\
        <input type=\"button\" class=\"iPush iBCancel\" value=\"Send\" style=\"width:100%\" onClick=\"lost_lbcom_send();\"/>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waRooms\" title=\"Rooms\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li><a href=\"#_Cameras\"><img class=\"picto\" src=\""+lost_icons_path+"cam.jpg\">Cameras</a></li>\
        </ul>\
        <ul>\
            <li><a href=\"javascript:lost_room_light_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_light_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumieres</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_MAX+3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_MAX+3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</li>\
            <li><a href=\"javascript:lost_room_elec_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_elec_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Eqpts Electriques</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"http://lebomb.free.fr/LOST/charts/chart.php?tab=bt\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\">Courbes de temperature</a></li>\
        </ul>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waCameras\" title=\"Cameras\">\
    <div class=\"iMenu\">\
        <ul>\
            <li><a href=\"http://bourdilot.no-ip.org:81\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V5_5.jpg\">Salle a manger</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:82\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V2_2.jpg\">Couloir</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:83\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V5_5.jpg\">Cuisine</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:84\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V3_3.jpg\">Arriere</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:85\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V3_3.jpg\">Avant</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:86\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"rpicam.jpg\">Chambre</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:87\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"rpicam.jpg\">Galerie</a></li>\
        </ul>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waEvenements\" title=\"Evenements\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Power</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_POWER_0+"\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Wifi</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_1+"\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Ethernet</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_2+"\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Power 2</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_3+"\"><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Alarm</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_ALARM_PERIMETER_CHECK+"\"><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm check</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_PERIMETER+"\"><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm perimeter</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_VOLUME+"\"><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm volume</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_ALL+"\"><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm all</a></li>\
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

printEventInfo(EVENT_POWER_0       , "Wifi"                   );
printEventInfo(EVENT_POWER_1       , "Ethernet"               );
printEventInfo(EVENT_POWER_2       , "Power 2"                );
printEventInfo(EVENT_POWER_3       , "Chauffage"              );
printEventInfo(EVENT_ALARM_PERIMETER_CHECK, "Alarm check"     );
printEventInfo(EVENT_ALARM_PERIMETER      , "Alarm perimeter" );
printEventInfo(EVENT_ALARM_VOLUME         , "Alarm volume"    );
printEventInfo(EVENT_ALARM_ALL            , "Alarm all"       );

