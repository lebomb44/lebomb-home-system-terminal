<?php
  define("NOM","lebomb");         //monnom = login chez free
  define("PASSE","genesis");     // monpasse=votre mot de passe free
  define("SERVEUR","sql.free.fr");// adresse du serveur free
  define("BASE","lebomb");       //nombase = login chez free

 //--Connexion au serveur
$link = mysql_connect(SERVEUR,NOM,PASSE);

if(!$link) {echo"Impossible de se connecter au serveur".mysql_error();exit;}
else {echo"connection au serveur réussie !";}

//--Connexion à la base
mysql_select_db(BASE,$link);

$temp0=$_GET['temp0'];
$temp1=$_GET['temp1'];
$temp2=$_GET['temp2'];
$temp3=$_GET['temp3'];

$requete= "INSERT INTO mms (DATE, TEMP0, TEMP1, TEMP2, TEMP3) VALUES (NOW(), '".$temp0."','".$temp1."','".$temp2."','".$temp3."')";

mysql_query($requete, $link) or die("Echec d'insertion".mysql_error());

mysql_close($link);
?>
