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

