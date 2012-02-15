function lost_mon_xml_get(xml)
{
  var out_id = document.getElementById("waHeadTitle");
  if(out_id)
  {
	var in_id = xml.getElementsByTagName("Mon")[0];
    if(in_id1)
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
        out_id.innerHTML = wday.firstChild.nodeValue + " " \
                         + mon.firstChild.nodeValue  + " " \
                         + mday.firstChild.nodeValue + " " \
                         + hour.firstChild.nodeValue + ":" \
                         + min.firstChild.nodeValue  + ":" \
                         + sec.firstChild.nodeValue  + " " \
                         + year.firstChild.nodeValue;
        lost_wa_refresh("waHeadTitle");
      }
      else
      {
        out_id.innerHTML="Unknown";
        lost_wa_refresh("waHeadTitle");
      }
    }
    else
    {
      out_id.innerHTML="Unknown";
      lost_wa_refresh("waHeadTitle");
    }
  }
}
