<?php
  if(!isset($_GET["tab"]))
  {
    echo "ERROR : Arguments tab not set";
    exit();
  }

  define("NOM","lebomb");         //monnom = login chez free
  define("PASSE","genesis");     // monpasse=votre mot de passe free
  define("SERVEUR","sql.free.fr");// adresse du serveur free
  define("BASE","lebomb");       //nombase = login chez free

// Connection to the serveur
$link = mysql_connect(SERVEUR,NOM,PASSE);

// Check the connection
if(!$link) { echo "Impossible to connect to the server".mysql_error(); exit; }

// Select the requiered DB
if(!mysql_select_db(BASE,$link)) { echo "Impossible to select the DB".mysql_error(); exit; }

// Build the SQL request
// Build the header
$request= "INSERT INTO ".$_GET["tab"])." (DATE, ";
// Add the names of the parameters
for($i=0; $i<10; $i++)
{
  $request .= "room".sprintf('%02d',$i)."_temp_value, ";
}
$request .= "safety_ups_temp, ";
$request .= "safety_rack_temp, ";
$request .= "start)";

// Add the values of the parameters
$request .= " VALUES (NOW(), ";
for($i=0; $i<10; $i++)
{
  $request .= "'".sprintf("%.01f",round((((((((floatval($_POST['room'.sprintf('%02d',$i).'_temp_value'])*5*100)/1024)-32)*140)/252)*10)/10),2))."',";
}
$request .= "'".sprintf("%.01f",round((((((((floatval($_POST['safety_ups_temp'])*5*100)/1024)-32)*140)/252)*10)/10),2))."',";
$request .= "'".sprintf("%.01f",round((((((((floatval($_POST['safety_rack_temp'])*5*100)/1024)-32)*140)/252)*10)/10),2))."',";
$request .= "'".sprintf("%d",$_POST['start'])."')";

// Send the request
mysql_query($request, $link) or die("Insertion failed".mysql_error());

// Close the link
mysql_close($link);

// Returned code OK
echo "SQL Insert OK\r\n";
?>
