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

$requete="CREATE TABLE `mms` (
`DATE` DATETIME DEFAULT '0000-00-00 00:00:00' NOT NULL,
`TEMP0` INT( 8 ) NOT NULL,
`TEMP1` INT( 8 ) NOT NULL,
`TEMP2` INT( 8 ) NOT NULL,
`TEMP3` INT( 8 ) NOT NULL,
PRIMARY KEY (`DATE`) 
);";

mysql_query($requete,$link);
?>