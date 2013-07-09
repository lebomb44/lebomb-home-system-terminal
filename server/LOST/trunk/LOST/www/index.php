<?php
function get_ip($src)
{
  return file_get_contents("safety/".$src."_ip.txt");
}
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head><title>LOST Main page</title></head>
<body>
<a href="http://mmms.no-ip.org">LOST MM's</a><br>
<?php
echo "<a href=\"http://".get_ip("mms")."\">LOST MM's by IP</a><br>\n";
?>
<a href="charts/mms_index.php">LOST MM's Chart</a><br>
<br>
<a href="http://bourdilot.no-ip.org">LOST Bourdilot</a><br>
<?php
echo "<a href=\"http://".get_ip("bt")."\">LOST Bourdilot by IP</a><br>\n";
?>
<a href="charts/bt_index.php">LOST Bourdilot Chart</a><br>
<a href="cams/bt.php">Bourdilot cameras</a><br>
<br>
<a href="http://lebomb.no-ip.org">LOST LeBomb</a><br>
<?php
echo "<a href=\"http://".get_ip("lb")."\">LOST LeBomb by IP</a><br>\n";
?>
<a href="charts/lb_index.php">LOST Frenes Chart</a><br>
<br>
<a href="http://cambon.no-ip.org">LOST Frenes</a><br>
<?php
echo "<a href=\"http://".get_ip("fr")."\">LOST Frenes by IP</a><br>\n";
?>
<a href="charts/fr_index.php">LOST Frenes Chart</a><br>
<a href="http://82.66.83.150">Frenes cameras</a><br>
<br>

</body>
</html>
