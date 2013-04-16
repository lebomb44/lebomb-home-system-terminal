<?php
header('Content-type: text/html');

$fp = fopen ("bt_ip.txt", "w");
if($fp === false)
{
  print("Impossible to open file\r\n");
  return;
}
if(ftruncate($fp,0) === false)
{
  print("Impossible to trunc file\r\n");
  fclose($fp);
  return;
}
if(fputs($fp, $_SERVER["REMOTE_ADDR"]) === false)
{
  print("Impossible to write in file\r\n");
  fclose($fp);
  return;
}
if(fclose($fp) === false)
{
  print("Impossible to close file\r\n");
  return;
}

print("LOST safety.http_status OK\r\n");
?>

