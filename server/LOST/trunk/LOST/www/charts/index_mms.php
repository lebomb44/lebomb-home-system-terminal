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
var myDate = new Date();
<?php
if(isset($_GET["year"]))
{
  echo "myDate.setUTCFullYear(".$_GET["year"].");";
  echo "myDate.setUTCMonth(0);";
  echo "myDate.setUTCDate(1);";
  echo "myDate.setUTCHours(0);";
}
?>
myDate.setUTCMinutes(0);
myDate.setUTCSeconds(0);
myDate.setUTCMilliseconds(0);
var chart; // globally available
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
			{name: 'Marine', data:[]},{name: 'M&M', data:[]},{name: 'Amis', data:[]},{name: 'Dressing', data:[]},{name: 'SdB', data:[]},
			{name: 'Bureau', data:[]},{name: 'Salon', data:[]},{name: 'Cuisine', data:[]},{name: 'Couloir', data:[]},{name: 'Terrasse', data:[]},
			{name: 'UPS', data:[]},{name: 'Rack', data:[]}
		]
      });
<?php
  define("NOM","lebomb");         //monnom = login chez free
  define("PASSE","genesis");     // monpasse=votre mot de passe free
  define("SERVEUR","sql.free.fr");// adresse du serveur free
  define("BASE","lebomb");       //nombase = login chez free

  //--Connexion au serveur
  $link = mysql_connect(SERVEUR,NOM,PASSE);

  if(!$link) {echo "Impossible de se connecter au serveur".mysql_error();exit;}
  //--Connexion ? la base
  mysql_select_db(BASE,$link);

  if(isset($_GET["year"])) { $year = $_GET["year"]; } else { $year = date("Y"); }
  $requete  = "SELECT * FROM mms WHERE `DATE` BETWEEN '".$year."-01-01 00:00:00' AND '".$year."-12-31 23:59:59' ORDER BY DATE";
  $result=mysql_query($requete, $link) or die("Echec de lecture".mysql_error());

  //$first = 1;
  while($r=mysql_fetch_array($result, MYSQL_ASSOC))
    //{echo "DATE: $r[DATE] TEMP0: $r[TEMP0] TEMP1: $r[TEMP1] TEMP2: $r[TEMP2] TEMP3: $r[TEMP3]<br>";}
    {
      //if($first==1) {$first=0;} else {echo ",";}
      $fullDate = $r[DATE];
      $temp = substr($fullDate, 0, 4).","; // Annee
      $temp .= ((string)(((int)substr($fullDate, 5, 2))-1)).","; // Mois
      $temp .= substr($fullDate, 8, 2).","; // Jour
      $temp .= substr($fullDate, 11, 2).","; // Heure
      $temp .= substr($fullDate, 14, 2).","; // Minute
      $temp .= substr($fullDate, 17, 2); // Second

      for($i=0; $i<10; $i++)
      {
		echo "chart.series[".$i."].addPoint([Date.UTC(".$temp."),".$r['room'.sprintf('%02d',$i).'_temp_value']."],false);\n";
      	//echo $r['room'.sprintf('%02d',$i).'_temp_value'].",";
      }
	  echo "chart.series[".$i."].addPoint([Date.UTC(".$temp."),".$r['safety_ups_temp']."],false);\n";
      //echo $r['safety_ups_temp'].",";
	  $i = $i + 1;
	  echo "chart.series[".$i."].addPoint([Date.UTC(".$temp."),".$r['safety_rack_temp']."],false);\n";
      //echo $r['safety_rack_temp']."]";
    }
	echo "chart.redraw();\n";
?>
   });
function chart_setInterval(date, interval)
{
  var current_date = Date.UTC(date.getUTCFullYear(), date.getUTCMonth(), date.getUTCDate(), date.getUTCHours());
  chart.xAxis[0].setExtremes(current_date, current_date + interval);
}
function previousYear()
{
  window.location = "<?php if(isset($_GET["year"])) { $year = $_GET["year"]; } else { $year = date("Y"); } echo "?year=".(intval($year)-1); ?>";
}
function nextYear()
{
  window.location = "<?php if(isset($_GET["year"])) { $year = $_GET["year"]; } else { $year = date("Y"); } echo "?year=".(intval($year)+1); ?>";
}
function previousMonth()
{
  myDate.setUTCMonth(myDate.getUTCMonth()-1);
  myDate.setUTCDate(1);

  chart_setInterval(myDate, 1000*3600*24*31);
}
function nextMonth()
{
  myDate.setUTCMonth(myDate.getUTCMonth()+1);
  myDate.setUTCDate(1);

  chart_setInterval(myDate, 1000*3600*24*31);
}
function previousDay()
{
  myDate.setUTCDate(myDate.getUTCDate()-1);
  myDate.setUTCHours(0);

  chart_setInterval(myDate, 1000*3600*24);
}
function nextDay()
{
  myDate.setUTCDate(myDate.getUTCDate()+1);
  myDate.setUTCHours(0);

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
