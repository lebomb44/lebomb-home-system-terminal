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
