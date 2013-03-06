<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="content-type" content="text/html; charset=utf-8" />
  <title>Temperature des Chambres</title>
<?php
// http://www.highcharts.com/stock/demo/
// http://dygraphs.com/tests/range-selector.html
?>
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js" type="text/javascript"></script>
<script src="http://code.highcharts.com/stock/highstock.js" type="text/javascript"></script>
  <script type="text/javascript">
  var chart;
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
  var i;
  xhr.onreadystatechange = function()
  {
    if((xhr.readyState == 4))
    {
      if(xhr.status == 200)
      {
        xml=xhr.responseXML;
        if(xml)
        {
      for(i=0; i<10; i++)
      {
	    console.debug(xml.getElementsByTagName("sample0")[0].getElementsByTagName("date")[0].firstChild.nodeValue);
        chart.series[i].addPoint([Date.UTC(xml.getElementsByTagName("sample0")[0].getElementsByTagName("date")[0].firstChild.nodeValue),xml.getElementsByTagName("sample0")[0].getElementsByTagName("room0")[0].firstChild.nodeValue],false);
      }
      //chart.series[i].addPoint([Date.UTC(".$temp."),".$r['safety_ups_temp']."],false);\n";
	  //$i = $i + 1;
      //chart.series[i].addPoint([Date.UTC(".$temp."),".$r['safety_rack_temp']."],false);\n";
      //$i = $i + 1;
      //if($r['start'] == "1") { echo "chart.series[".$i."].addPoint({x: Date.UTC(".$temp."),title: 'S',text: 'Start'},false);\n"; }
      chart.redraw();
        }
      }
      else
      {
        xhr.abort();
      }
    }
  };
  xhr.open("GET","get_mms.php?year=2013&month=1",true);
  //xhr.setTimeouts(4000);
  xhr.send("");

  //setTimeout("indexLoading()", 10000);
}
var myDate = new Date();
<?php
if(isset($_GET["year"]) && isset($_GET["month"]))
{
  echo "myDate.setUTCFullYear(".(intval($_GET["year"])).");";
  echo "myDate.setUTCMonth(".(intval($_GET["month"])-1).");";
}
?>
myDate.setUTCDate(1);
myDate.setUTCHours(0);
myDate.setUTCMinutes(0);
myDate.setUTCSeconds(0);
myDate.setUTCMilliseconds(0);

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
						{type: 'all',text: 'All'}]
		},
		series: [
			{name: 'Marine', data:[]},{name: 'M&M', data:[]},{name: 'Amis', data:[]},{name: 'Dressing', data:[]},{name: 'Combles', data:[]},
			{name: 'Bureau', data:[]},{name: 'Cuisine', data:[]},{name: 'Celier', data:[]},{name: 'Couloir', data:[]},{name: 'Salon', data:[]},
			{name: 'UPS', data:[]},{name: 'Rack', data:[]},{type: 'flags', name: 'Start', data:[]}
		]
      });
      //chart.redraw();
      indexLoading();
   });

function chart_setInterval(date, interval)
{
  var current_date = Date.UTC(date.getUTCFullYear(), date.getUTCMonth(), date.getUTCDate(), date.getUTCHours());
  chart.xAxis[0].setExtremes(current_date, current_date + interval);
}
function previousYear()
{
  window.location = "<?php if(isset($_GET["year"]) && isset($_GET["month"])) { $year = intval($_GET["year"]); $month = intval($_GET["month"]); }
  							else { $year = intval(date("Y")); $month = intval(date("m")); }
  							echo "?year=".($year-1)."&month=".$month; ?>";
}
function nextYear()
{
  window.location = "<?php if(isset($_GET["year"]) && isset($_GET["month"])) { $year = intval($_GET["year"]); $month = intval($_GET["month"]); }
  							else { $year = intval(date("Y")); $month = intval(date("m")); }
  							echo "?year=".($year+1)."&month=".$month; ?>";
}
function previousMonth()
{
  window.location = "<?php if(isset($_GET["month"]) && isset($_GET["month"])) { $year = intval($_GET["year"]); $month = intval($_GET["month"]); }
  							else { $year = intval(date("Y")); $month = intval(date("m")); }
							if($month == 1) { $month = 12; $year = $year - 1; }
							else { $month = $month - 1; } 
							echo "?year=".$year."&month=".$month; ?>";
}
function nextMonth()
{
  window.location = "<?php if(isset($_GET["month"]) && isset($_GET["month"])) { $year = intval($_GET["year"]); $month = intval($_GET["month"]); }
							else { $year = intval(date("Y")); $month = intval(date("m")); }
							if($month == 12) { $month = 0; $year = $year + 1; }
							else { $month = $month + 1; } 
							echo "?year=".$year."&month=".$month; ?>";
}
function previousDay()
{
  myDate.setUTCDate(Math.max(myDate.getUTCDate()-1,1));

  chart_setInterval(myDate, 1000*3600*24);
}
function nextDay()
{
  myDate.setUTCDate(Math.min(myDate.getUTCDate()+1,<?php
  	if(isset($_GET["month"]) && isset($_GET["month"])) { $year = intval($_GET["year"]); $month = intval($_GET["month"]); }
  	else { $year = intval(date("Y")); $month = intval(date("m")); }
  	echo cal_days_in_month(CAL_GREGORIAN, $month, $year); ?>));

  chart_setInterval(myDate, 1000*3600*24);
}
function previousHour()
{
  myDate.setUTCHours(myDate.getUTCHours()-1);

  chart_setInterval(myDate, 1000*3600);
}
function nextHour()
{
  myDate.setUTCHours(myDate.getUTCHours()+1);

  chart_setInterval(myDate, 1000*3600);
}
   </script>
</head>
<body style="font-family: Arial;border: 0 none;">
<div id="container" style="width: 100%; height: 400px"></div>
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
