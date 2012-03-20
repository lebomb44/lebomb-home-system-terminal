var EVENT_REVEIL         = 0;
var EVENT_COUCHE         = 1;
var EVENT_CHAUFFAGE_SDB  = 2;
var EVENT_CHAUFFAGE_CAFE = 3;
var EVENT_LUMIERE_AUTO   = 4;
var EVENT_MUSIQUE_AUTO   = 5;
var EVENT_POWER_0        = 6;
var EVENT_POWER_1        = 7;
var EVENT_POWER_2        = 8;
var EVENT_POWER_3        = 9;
var EVENT_MAX            = 10;

var EVENT_STATUS_OFF = 0;
var EVENT_STATUS_ON  = 1;

var url_ev="cgi/events.cgi?event=";

function lost_ev_date_status_update(event)
{
  var elt_St;
  var elt_HStart;
  var elt_MStart;
  var elt_HEnd;
  var elt_MEnd;
  var status;

  elt_St = document.getElementById("Event"+String(event)+"_St");
  if(elt_St)
  {
    status = elt_St.checked;
    elt_HStart = document.getElementById("Event"+String(event)+"_HStart");
    if(elt_HStart) { elt_HStart.disabled = status; }
    elt_MStart = document.getElementById("Event"+String(event)+"_MStart")
    if(elt_MStart) { elt_MStart.disabled = status; }
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
      lost_select_update(xml, "Event"+String(event), "HStart");
      lost_select_update(xml, "Event"+String(event), "MStart");
      lost_select_update(xml, "Event"+String(event), "HEnd");
      lost_select_update(xml, "Event"+String(event), "MEnd");
    }
  }
  lost_ev_date_status_update(event);
}

function lost_ev_xml_get(xml)
{
  lost_ev_xml_update(xml, EVENT_REVEIL);
  lost_ev_xml_update(xml, EVENT_COUCHE);
  lost_ev_xml_update(xml, EVENT_CHAUFFAGE_SDB);
  lost_ev_xml_update(xml, EVENT_CHAUFFAGE_CAFE);
  lost_ev_xml_update(xml, EVENT_LUMIERE_AUTO);
  lost_ev_xml_update(xml, EVENT_MUSIQUE_AUTO);
  lost_ev_xml_update(xml, EVENT_POWER_0);
  lost_ev_xml_update(xml, EVENT_POWER_1);
  lost_ev_xml_update(xml, EVENT_POWER_2);
  lost_ev_xml_update(xml, EVENT_POWER_3);
}

/* ************* SET ************************ */

function lost_ev_rec_set(event, rec, value)
{
  lost_set(url_ev+String(event)+"&rec="+String(rec)+"&value="+String(value));
}

function lost_ev_date_set(event)
{
  var elt_HStart;
  var elt_MStart;
  var elt_HEnd;
  var elt_MEnd;
  elt_HStart = document.getElementById("Event"+String(event)+"_HStart");
  elt_MStart = document.getElementById("Event"+String(event)+"_MStart")
  elt_HEnd = document.getElementById("Event"+String(event)+"_HEnd");
  elt_MEnd = document.getElementById("Event"+String(event)+"_MEnd");
  if(elt_HStart && elt_MStart && elt_HEnd && elt_MEnd)
  {
    lost_set(url_ev+String(event)+"&hs="+String(Number(elt_HStart.value))+"&ms="+String(Number(elt_MStart.value))+"&he="+String(Number(elt_HEnd.value))+"&me="+String(Number(elt_MEnd.value)));
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
