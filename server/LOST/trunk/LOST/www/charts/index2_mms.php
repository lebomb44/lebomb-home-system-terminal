<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <meta http-equiv="content-type" content="text/html; charset=utf-8" />
  <title>Temperature des Chambres</title>
<?php
// http://www.highcharts.com/stock/demo/
// http://dygraphs.com/tests/range-selector.html
?>
  <script type="text/javascript" src="http://www.google.com/jsapi"></script>
  <script type="text/javascript">
    google.load('visualization', '1', {packages: ['annotatedtimeline']});
    function drawVisualization() {
      var data = new google.visualization.DataTable();
      data.addColumn('date', 'Date');
      data.addColumn('number', 'Marine');
      data.addColumn('number', 'M&M');
      data.addColumn('number', 'Amis');
      data.addColumn('number', 'Dressing');
      data.addColumn('number', 'SdB');
      data.addColumn('number', 'Bureau');
      data.addColumn('number', 'Salon');
      data.addColumn('number', 'Cuisine');
      data.addColumn('number', 'Couloir');
      data.addColumn('number', 'Terrasse');
      data.addColumn('number', 'UPS');
      data.addColumn('number', 'Rack');
      data.addRows([
<?php
  define("NOM","lebomb");         //monnom = login chez free
  define("PASSE","genesis");     // monpasse=votre mot de passe free
  define("SERVEUR","sql.free.fr");// adresse du serveur free
  define("BASE","lebomb");       //nombase = login chez free

  //--Connexion au serveur
  $link = mysql_connect(SERVEUR,NOM,PASSE);

  if(!$link) {echo "Impossible de se connecter au serveur".mysql_error();exit;}
  //--Connexion � la base
  mysql_select_db(BASE,$link);

  $requete= "SELECT * FROM mms WHERE `DATE` BETWEEN '2012-01-01 00:00:00' AND '2012-12-31 23:59:59' ORDER BY DATE";
  $result=mysql_query($requete, $link) or die("Echec de lecture".mysql_error());

  $first = 1;
  while($r=mysql_fetch_array($result, MYSQL_ASSOC))
    //{echo "DATE: $r[DATE] TEMP0: $r[TEMP0] TEMP1: $r[TEMP1] TEMP2: $r[TEMP2] TEMP3: $r[TEMP3]<br>";}
    {
      if($first==1) {$first=0;} else {echo ",";}
      $fullDate = $r[DATE];
      $temp = substr($fullDate, 0, 4).","; // Annee
      $temp .= ((string)(((int)substr($fullDate, 5, 2))-1)).","; // Mois
      $temp .= substr($fullDate, 8, 2).","; // Jour
      $temp .= substr($fullDate, 11, 2).","; // Heure
      $temp .= substr($fullDate, 14, 2).","; // Minute
      $temp .= substr($fullDate, 17, 2); // Second

      echo "[new Date(".$temp."),";
  
      for($i=0; $i<10; $i++)
      {
      	echo $r['room'.sprintf('%02d',$i).'_temp_value'].",";
      }
      echo $r['safety_ups_temp'].",";
      echo $r['safety_rack_temp']."]";
    }
?>
	]);
    
      var annotatedtimeline = new google.visualization.AnnotatedTimeLine(
          document.getElementById('visualization'));
      annotatedtimeline.draw(data, {'dateFormat': 'HH:mm MMMM dd, yyyy'}, {'displayAnnotations': true});
    }
    
    google.setOnLoadCallback(drawVisualization);
  </script>
</head>
<body style="font-family: Arial;border: 0 none;">
<div id="visualization" style="width: 1200px; height: 500px;"></div>
</body>
</html>
