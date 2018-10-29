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

function printSelectOptionMinMax(id, minNb, maxNb)
{
  var elt;
  var i;
  elt = document.getElementById(id);
  if(elt)
  {
    elt.length = Number(maxNb) - Number(minNb);
    for(i=Number(minNb); i<Number(maxNb); i++)
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
