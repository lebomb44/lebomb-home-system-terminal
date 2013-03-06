<html>
<head><title>Bourdilot Cameras</title></head>
<body>
<SCRIPT language="javascript">
function openCams(adr, name, top, left, height, width)
{
  var win;
  win=window.open(adr,name,"top="+top+",left="+left+",height="+height+",width="+width+",menubar=no,location=no,toolbar=no,scrollbars=auto,status=no,directories=no,toolbar=no,titlebar=no,fullscreen=yes");
}

function openSalonCam()
{
  openCams("http://bourdilot.no-ip.info:81", "Salon"  , 0,0,(screen.availHeight)/2-50,(screen.availWidth)/2);
}
function openCouloirCam()
{
  openCams("http://bourdilot.no-ip.info:82", "Couloir", 0,(screen.availWidth)/2,(screen.availHeight)/2-50,(screen.availWidth)/2);
}
function openCuisineCam()
{
  openCams("http://bourdilot.no-ip.info:83", "Cuisine", (screen.availHeight)/2,0,(screen.availHeight)/2-50,(screen.availWidth)/2);
}
function openArriereCam()
{
  openCams("http://bourdilot.no-ip.info:84", "Arriere", (screen.availHeight)/2,(screen.availWidth)/2,(screen.availHeight)/2-50,(screen.availWidth)/2);
}
function openFacadeCam()
{
  openCams("http://bourdilot.no-ip.info:85", "Facade", (screen.availHeight)/2,(screen.availWidth)/2,(screen.availHeight)/2-50,(screen.availWidth)/2);
}
function openAllCams()
{
  openSalonCam();
  openCouloirCam();
  openCuisineCam();
  openArriereCam();
  openFacadeCam();
}
</SCRIPT>
<h1>Cameras :</h1>
<A HREF="#" onClick="return openAllCams()">Toutes les cameras</A></br>
<A HREF="#" onClick="return openSalonCam()">Salon</A></br>
<A HREF="#" onClick="return openCouloirCam()">Couloir</A></br>
<A HREF="#" onClick="return openCuisineCam()">Cuisine</A></br>
<A HREF="#" onClick="return openArriereCam()">Arriere</A></br>
<A HREF="#" onClick="return openFacadeCam()">Facade</A></br>
</br>
<h1>Photos enregistrées :</h1>
<?php
$dir_nom = '.'; // dossier listé (pour lister le répertoir courant : $dir_nom = '.'  --> ('point')
$dir = opendir($dir_nom) or die('Erreur de listage : le répertoire n\'existe pas'); // on ouvre le contenu du dossier courant
$fichier= array(); // on déclare le tableau contenant le nom des fichiers
$dossier= array(); // on déclare le tableau contenant le nom des dossiers

while($element = readdir($dir)) {
	if(($element != '.') && ($element != '..') && ($element != '.htaccess')  && ($element != 'index.php')) {
		if (!is_dir($dir_nom.'/'.$element)) {$fichier[] = $element;}
		else {$dossier[] = $element;}
	}
}

closedir($dir);

if(!empty($dossier)) {
	sort($dossier); // pour le tri croissant, rsort() pour le tri décroissant
	echo "Liste des dossiers :\n";
	echo "<ul>\n";
		foreach($dossier as $lien){
			echo "<li><a href=\"$dir_nom/$lien \">$lien</a></li>\n";
		}
	echo "</ul>";
}

if(!empty($fichier)){
	sort($fichier);// pour le tri croissant, rsort() pour le tri décroissant
	echo "Liste des fichiers :\n";
	echo "<ul>\n";
		foreach($fichier as $lien) {
			echo "\t\t\t<li><a href=\"$dir_nom/$lien \">$lien</a></li>\n";
		}
	echo "</ul>";
 }
?>
</body>
</html>
