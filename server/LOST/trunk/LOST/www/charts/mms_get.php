<?php
  header ("Content-Type:text/xml\n");
  echo "<?xml version='1.0' encoding='UTF-8'?>";
  echo "<Lost>";
  if(!isset($_GET["table"]) || !isset($_GET["year"]) || !isset($_GET["month"]) || !isset($_GET["day"]))
  {
    echo "Arguments base, year, month or day not set";
    echo "</Lost>";
    exit();
  }

  define("NOM","lebomb");         //monnom = login chez free
  // define("NOM","root");         //monnom = login chez free
  define("PASSE","genesis");     // monpasse=votre mot de passe free
  // define("PASSE","qwerty");     // monpasse=votre mot de passe free
  define("SERVEUR","sql.free.fr");// adresse du serveur free
  // define("SERVEUR","127.0.0.1");// adresse du serveur free
  define("BASE","lebomb");       //nombase = login chez free

  //--Connexion au serveur
  $link = mysql_connect(SERVEUR,NOM,PASSE);
  if(!$link) { echo "Impossible de se connecter au serveur : ".mysql_error()."</Lost>"; exit(); }
  //--Connexion ? la base
  $result = mysql_select_db(BASE,$link);
  if(!$result) { echo "mysql_select_db bad returned value : ".mysql_error()."</Lost>"; exit(); }

  $year = intval($_GET["year"]); $month = intval($_GET["month"]); $day = intval($_GET["day"]);
  $requete  = "SELECT * FROM ".$_GET["table"]." WHERE `DATE` BETWEEN '".$year."-".sprintf('%02d',$month)."-".sprintf('%02d',$day)." 00:00:00' AND '".$year."-".sprintf('%02d',$month)."-".sprintf('%02d',$day)." 23:59:59' ORDER BY DATE LIMIT 0,100";
  $result = mysql_query($requete, $link);
  if(!$result) { echo "mysql_query bad returned value : ".mysql_error()."</Lost>"; exit(); }
//echo "//".$requete."\n";

  $nb = 0;
  while($r=mysql_fetch_array($result, MYSQL_ASSOC))
    //{echo "DATE: $r[DATE] TEMP0: $r[TEMP0] TEMP1: $r[TEMP1] TEMP2: $r[TEMP2] TEMP3: $r[TEMP3]<br>";}
    {
      echo "<sample".$nb.">";
      echo "<date>".str_replace(" ", "T", $r[DATE])."+00:00</date>";
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

