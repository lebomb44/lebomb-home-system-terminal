<?php
  header ("Content-Type:text/xml\n");
  if(!isset($_GET["year"]) || !isset($_GET["month"]))
  {
    echo "Arguments year and month not set"; exit();
  }

  define("NOM","lebomb");         //monnom = login chez free
  define("PASSE","genesis");     // monpasse=votre mot de passe free
  define("SERVEUR","sql.free.fr");// adresse du serveur free
  define("BASE","lebomb");       //nombase = login chez free

  //--Connexion au serveur
  $link = mysql_connect(SERVEUR,NOM,PASSE);
  if(!$link) { echo "Impossible de se connecter au serveur".mysql_error(); exit; }
  //--Connexion ? la base
  $result = mysql_select_db(BASE,$link);
  if(!$result) { echo "mysql_select_db bad returned value".mysql_error(); exit(); }

  $year = intval($_GET["year"]); $month = intval($_GET["month"]);
  $requete  = "SELECT * FROM mms WHERE `DATE` BETWEEN '".$year."-".sprintf('%02d',$month)."-01 00:00:00' AND '".$year."-".sprintf('%02d',$month)."-31 23:59:59' ORDER BY DATE LIMIT 0,100";
  $result = mysql_query($requete, $link);
  if(!$result) { echo "mysql_query bad returned value".mysql_error(); exit(); }
//echo "//".$requete."\n";
  echo "<?xml version='1.0' encoding='UTF-8'?>";
  echo "<Lost>";
  $nb = 0;
  while($r=mysql_fetch_array($result, MYSQL_ASSOC))
    //{echo "DATE: $r[DATE] TEMP0: $r[TEMP0] TEMP1: $r[TEMP1] TEMP2: $r[TEMP2] TEMP3: $r[TEMP3]<br>";}
    {
      $fullDate = $r[DATE];
      $temp = substr($fullDate, 0, 4).","; // Annee
      $temp .= ((string)(((int)substr($fullDate, 5, 2))-1)).","; // Mois
      $temp .= substr($fullDate, 8, 2).","; // Jour
      $temp .= substr($fullDate, 11, 2).","; // Heure
      $temp .= substr($fullDate, 14, 2).","; // Minute
      $temp .= substr($fullDate, 17, 2); // Second

	  echo "<sample".$nb.">";
	  echo "<date>".$temp."</date>";
      for($i=0; $i<10; $i++)
      {
        echo "<room".$i.">".$r['room'.sprintf('%02d',$i).'_temp_value']."</room".$i.">";
      	//echo $r['room'.sprintf('%02d',$i).'_temp_value'].",";
      }
      echo "<safety_ups>".$r['safety_ups_temp']."</safety_ups>";
      //echo $r['safety_ups_temp'].",";
      echo "<safety_rack>".$r['safety_rack_temp']."</safety_rack>";
      //echo $r['safety_rack_temp']."]";
      if($r['start'] == "1") { echo "<start>yes</start>"; }
  	  echo "</sample".$nb.">";
	  $nb++;
    }
  echo "</Lost>";
?>
