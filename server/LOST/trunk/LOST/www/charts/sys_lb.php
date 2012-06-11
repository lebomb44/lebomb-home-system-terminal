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
$request= "INSERT INTO lb_sys (DATE, start) VALUES (NOW(), '1') ";

// Send the request
mysql_query($request, $link) or die("Insertion failed".mysql_error());

// Close the link
mysql_close($link);

// Returned code OK
echo "SQL Insert OK\r\n";
?>
