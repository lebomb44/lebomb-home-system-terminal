<?
$fp = fopen ("lb_ip.txt", "w");
if($fp === false)
{
  echo "Impossible to open file";
  return;
}  
if(fputs($fp, $_SERVER["REMOTE_ADDR"]."        ") === false)
{
  echo "Impossible to write in file";
  return;
}
if(fclose ($fp) === false)
{
  echo "Impossible to close file";
  return;
}

echo "LOST safety.http_status OK";
?>

