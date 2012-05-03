<?php
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
$request= "INSERT INTO mms (DATE, ";
// Add the names of the parameters
for($i=0; $i<10; $i++)
{
  $request .= "room".$i."_temp_value, ";
}
$request .= "safety_ups_temp, ";
$request .= "safety_rack_temp)";

// Add the values of the parameters
$request .= " VALUES (NOW(), ";
for($i=0; $i<10; $i++)
{
  $request .= "'".$_POST['room'.$i.'_temp_value']."',";
}
$request .= "'".$_POST['safety_ups_temp']."',";
$request .= "'".$_POST['safety_rack_temp']."')";

echo var_dump($_POST);
echo "<br>".$request;
// Send the request
mysql_query($request, $link) or die("Insertion failed".mysql_error());

// Close the link
mysql_close($link);
?>
