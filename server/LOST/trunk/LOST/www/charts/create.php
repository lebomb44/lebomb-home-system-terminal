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
$requete = "CREATE TABLE `".$_GET["tab"]."` (";
// Add the names of the parameters
$requete .= "`DATE` DATETIME DEFAULT '0000-00-00 00:00:00' NOT NULL,";
for($i=0; $i<10; $i++)
{
  $requete .= "`room".sprintf('%02d',$i)."_temp_value` DECIMAL(4,1) NOT NULL,";
}
$requete .= "`safety_ups_temp` DECIMAL(4,1) NOT NULL,";
$requete .= "`safety_rack_temp` DECIMAL(4,1) NOT NULL,";
$requete .= "`start` BOOL NULL DEFAULT '0',";
$requete .= "PRIMARY KEY (`DATE`));";

// Send the request
mysql_query($requete,$link);

// Close the link
mysql_close($link);
?>
