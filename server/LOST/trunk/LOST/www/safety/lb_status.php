<?php
header('Content-type: text/html');

$fp = fopen ("lb_ip.txt", "w");
if($fp === false)
{
  echo "Impossible to open file";
  return;
}
if(ftruncate($fp,0) === false)
{
  echo "Impossible to trunc file";
  fclose($fp);
  return;
}
if(fputs($fp, $_SERVER["REMOTE_ADDR"]) === false)
{
  echo "Impossible to write in file";
  fclose($fp);
  return;
}
if(fclose($fp) === false)
{
  echo "Impossible to close file";
  return;
}

echo "LOST safety.http_status OK";
?>

