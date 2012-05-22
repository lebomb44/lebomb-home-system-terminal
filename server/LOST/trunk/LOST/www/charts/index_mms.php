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

  $requete= "SELECT * FROM mms WHERE `DATE` BETWEEN '2012-01-01 00:00:00' AND '2012-12-31 23:59:59' ORDER BY DATE";
  $result=mysql_query($requete, $link) or die("Echec de lecture".mysql_error());

  $first = 1;
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
   </script>
</head>
<body style="font-family: Arial;border: 0 none;">
<div id="container" style="width: 100%; height: 400px"></div>
</body>
</html>
