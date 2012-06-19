var EVENT_SHUTTERS_ALL        = 0;
var EVENT_SHUTTERS_UPSTAIRS   = 1;
var EVENT_SHUTTERS_DOWNSTAIRS = 2;
var EVENT_SHUTTERS_MARINE     = 3;
var EVENT_SHUTTERS_MM         = 4;
var EVENT_SHUTTERS_FRIENDS    = 5;
var EVENT_SHUTTERS_DRESSING   = 6;
var EVENT_ALARM_ALL           = 7;
var EVENT_ALARM_PERIMETER     = 8;
var EVENT_ALARM_VOLUME        = 9;
var EVENT_SIMU                = 10;
var EVENT_POWER_0             = 11;
var EVENT_POWER_1             = 12;
var EVENT_POWER_2             = 13;
var EVENT_POWER_3             = 14;
var EVENT_MAX                 = 15;

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
