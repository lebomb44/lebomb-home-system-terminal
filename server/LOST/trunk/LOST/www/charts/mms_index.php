<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="content-type" content="text/html; charset=utf-8" />
  <title>Temperature des Chambres</title>
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.7.2/jquery.min.js" type="text/javascript"></script>
<script src="http://code.highcharts.com/stock/highstock.js" type="text/javascript"></script>
</head>
<body style="font-family: Arial;border: 0 none;">
<script type="text/javascript">

var chart;
var myDate = new Date(0);
var firstDate = new Date(0);
var lastDate = new Date(0);
var firstDateV = new Date(0);
var lastDateV = new Date(0);
var toto;
<?php
if(isset($_GET["nmonth"]))
{
  echo "var nmonth = ".intval($_GET["nmonth"]).";";
}
else
{
  echo "var nmonth = 1;";
}
if(isset($_GET["year"]) && isset($_GET["month"]) && isset($_GET["day"]))
{
  echo "myDate.setUTCDate(".(intval($_GET["day"])).");\n";
  echo "myDate.setUTCFullYear(".(intval($_GET["year"])).");\n";
  echo "myDate.setUTCMonth(".(intval($_GET["month"])-1).");\n";
  echo "myDate.setUTCDate(".(intval($_GET["day"])).");\n";
}
else
{
  $myDate = date("Ymd");
  echo "myDate.setUTCFullYear(".intval(substr($myDate,0,4)).");\n";
  echo "myDate.setUTCMonth(".(intval(substr($myDate,4,2))-1)."-nmonth);\n";
  echo "myDate.setUTCDate(".intval(substr($myDate,6,2)).");\n";
}
?>
myDate.setUTCHours(0);
myDate.setUTCMinutes(0);
myDate.setUTCSeconds(0);
myDate.setUTCMilliseconds(0);
firstDate.setTime(myDate.getTime());
firstDateV.setTime(firstDate.getTime());
lastDate.setTime(firstDate.getTime());
lastDate.setUTCMonth(lastDate.getUTCMonth() + nmonth);
lastDate.setUTCHours(23);
lastDate.setUTCMinutes(59);
lastDate.setUTCSeconds(59);
lastDate.setUTCMilliseconds(999);
lastDateV.setTime(lastDate.getTime());

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

function indexLoading(evt)
{
  var xhr = lost_getXHR();
  var xml;
  var sample;
  var date;
  var dateI;
  var value;
  var nb = 0;
  var i;

  xhr.onreadystatechange = function()
  {
    if((xhr.readyState == 4))
    {
      if(xhr.status == 200)
      {
        xml = xhr.responseXML;
        if(xml)
        {
          while(1)
          {
            sample = xml.getElementsByTagName("sample"+String(nb))[0];
            if(sample)
            {
              nb++;
              date = new Date(String(sample.getElementsByTagName("date")[0].firstChild.nodeValue));
              dateI = date.getTime();

              for(i=0; i<10; i++)
              {
                value = sample.getElementsByTagName("room"+String(i))[0];
                if(value) { chart.series[i].addPoint([dateI,parseInt(value.firstChild.nodeValue)],false); }
              }
              value = sample.getElementsByTagName("safety_ups")[0];
              if(value) { chart.series[i].addPoint([dateI,parseInt(value.firstChild.nodeValue)],false); } i++;
              value = sample.getElementsByTagName("safety_rack")[0];
              if(value) { chart.series[i].addPoint([dateI,parseInt(value.firstChild.nodeValue)],false); } i++;
              value = sample.getElementsByTagName("start")[0];
              if(value) { { chart.series[i].addPoint({x: dateI,title: 'S',text: 'Start'},false); } }
            }
            else
            {
              //chart.redraw();
              //chart.xAxis[0].setExtremes(firstDate.getTime(), lastDate.getTime());
              break;
            }
          }
        }
      }
      else
      {
        xhr.abort();
      }
      myDate.setUTCDate(myDate.getUTCDate()+1);
      if(myDate.getTime() < lastDate.getTime())
      {
        setTimeout("indexLoading()", 1);
      }
      else
      {
        chart.redraw();
        chart.xAxis[0].setExtremes(firstDate.getTime(), lastDate.getTime());
      }
    }
  };
  xhr.open("GET","mms_get.php?table=mms&year="+myDate.getUTCFullYear()+"&month="+(myDate.getUTCMonth()+1)+"&day="+myDate.getUTCDate(),true);
  //xhr.setTimeouts(4000);
  xhr.send("");


}


$(document).ready(function() {
  chart = new Highcharts.StockChart({
    chart: {
      renderTo: 'container',
      type: 'line'
    },
    xAxis: {
      ordinal: false
    },
    rangeSelector: {
      buttons: [{type: 'day',count: 1,text: '1d'},
                {type: 'month',count: 1,text: '1m'},
                {type: 'month',count: 3,text: '3m'},
                {type: 'month',count: 6,text: '6m'},
                {type: 'ytd',text: 'YTD'},
                {type: 'year',count: 1,text: '1y'},
                {type: 'all',text: 'All'}],
      selected: 1
    },
    series: [
      {name: 'Marine', data:[]},{name: 'M&M', data:[]},{name: 'Amis', data:[]},{name: 'Dressing', data:[]},{name: 'Combles', data:[]},
      {name: 'Bureau', data:[]},{name: 'Cuisine', data:[]},{name: 'Celier', data:[]},{name: 'Couloir', data:[]},{name: 'Salon', data:[]},
      {name: 'UPS', data:[]},{name: 'Rack', data:[]},{type: 'flags', name: 'Start', data:[]}
    ]
  });
  chart.redraw();
  indexLoading();
});

function chart_setInterval(f,l)
{
  chart.xAxis[0].setExtremes(f.getTime(),l.getTime(),true);
}
function build_url(date)
{
  return "mms_index.php?table=mms&year="+date.getUTCFullYear()+"&month="+(date.getUTCMonth()+1)+"&day="+date.getUTCDate()+"&nmonth="+nmonth;
}
function previousYear()
{
  var date = new Date();
  date.setTime(firstDate.getTime());
  date.setUTCFullYear(date.getUTCFullYear()-1);
  window.location = build_url(date);
}
function nextYear()
{
  var date = new Date();
  date.setTime(firstDate.getTime());
  date.setUTCFullYear(date.getUTCFullYear()+1);
  window.location = build_url(date);
}
function previousMonth()
{
  var date = new Date();
  date.setTime(firstDate.getTime());
  date.setUTCMonth(date.getUTCMonth()-1);
  window.location = build_url(date);
}
function nextMonth()
{
  var date = new Date();
  date.setTime(firstDate.getTime());
  date.setUTCMonth(date.getUTCMonth()+1);
  window.location = build_url(date);
}
function previousDay()
{
  var date = new Date();
  date.setTime(firstDateV.getTime());
  date.setUTCDate(date.getUTCDate()-1);
  date.setUTCHours(0);

  if(date.getTime() < firstDate.getTime())
  {
    date.setTime(firstDate.getTime());
  }
  firstDateV.setTime(date.getTime());
  lastDateV.setTime(firstDateV.getTime());
  lastDateV.setUTCDate(lastDateV.getUTCDate()+1);
  chart_setInterval(firstDateV, lastDateV);
}
function nextDay()
{
  var date = new Date();
  date.setTime(firstDateV.getTime());
  date.setUTCDate(date.getUTCDate()+1);
  date.setUTCHours(0);

  if(date.getTime() <= lastDate.getTime())
  {
    firstDateV.setTime(date.getTime());
    lastDateV.setTime(firstDateV.getTime());
    lastDateV.setUTCDate(lastDateV.getUTCDate()+1);
    chart_setInterval(firstDateV, lastDateV);
  }
}
function previousHour()
{
  var date = new Date();
  date.setTime(firstDateV.getTime());
  date.setUTCHours(date.getUTCHours()-1);

  if(date.getTime() < firstDate.getTime())
  {
    date.setTime(firstDate.getTime());
  }
  firstDateV.setTime(date.getTime());
  lastDateV.setTime(firstDateV.getTime());
  lastDateV.setUTCHours(lastDateV.getUTCHours()+1);
  chart_setInterval(firstDateV, lastDateV);
}
function nextHour()
{
  var date = new Date();
  date.setTime(firstDateV.getTime());
  date.setUTCHours(date.getUTCHours()+1);

  if(date.getTime() <= lastDate.getTime())
  {
    firstDateV.setTime(date.getTime());
    lastDateV.setTime(firstDateV.getTime());
    lastDateV.setUTCHours(firstDateV.getUTCHours()+1);
    chart_setInterval(firstDateV, lastDateV);
  }
}
   </script>

<div id="container" style="min-width: 400px; height: 400px; margin: 0 auto"></div>
<table width="100%">
 <tr>
  <td align="left"><input type="button" onClick="previousYear()" value="Annee Precedente"></td>
  <td align="right"><input type="button" onClick="nextYear()" value="Annee Suivante"></td>
 </tr>
 <tr>
  <td align="left"><input type="button" onClick="previousMonth()" value="Mois Precedent"></td>
  <td align="right"><input type="button" onClick="nextMonth()" value="Mois Suivant"></td>
 </tr>
 <tr>
  <td align="left"><input type="button" onClick="previousDay()" value="Jour Precedent"></td>
  <td align="right"><input type="button" onClick="nextDay()" value="Jour Suivant"></td>
 </tr>
 <tr>
  <td align="left"><input type="button" onClick="previousHour()" value="Heure Precedente"></td>
  <td align="right"><input type="button" onClick="nextHour()" value="Heure Suivante"></td>
 </tr>
</table>
</body>
</html>
