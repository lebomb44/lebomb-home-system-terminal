<?php
  define("NOM","lebomb");         //monnom = login chez free
  define("PASSE","genesis");     // monpasse=votre mot de passe free
  define("SERVEUR","sql.free.fr");// adresse du serveur free
  define("BASE","lebomb");       //nombase = login chez free


//--Connexion au serveur
$link = mysql_connect(SERVEUR,NOM,PASSE);

if(!$link) {echo"Impossible de se connecter au serveur".mysql_error();exit;}

//--Connexion à la base
mysql_select_db(BASE,$link);


$requete= "SELECT * FROM mms WHERE `DATE` BETWEEN '2012-04-24 12:00:40' AND '2012-04-24 12:13:58'";

$result=mysql_query($requete, $link) or die("Echec de lecture".mysql_error());


while($r=mysql_fetch_array($result, MYSQL_ASSOC))
	{echo"$r<br>DATE: $r[DATE] TEMP0: $r[TEMP0] TEMP1: $r[TEMP1] TEMP2: $r[TEMP2] TEMP3: $r[TEMP3]<br>";
	
	} 

mysql_close($link);

?>
