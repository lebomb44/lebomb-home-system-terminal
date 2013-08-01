<?php
header('Content-type: text/html');

if(!isset($_GET["tab"]))
{
  echo "ERROR : Arguments tab not set";
  exit();
}
  
$fp = fopen ($_GET["tab"]."_ip.txt", "w");
if(false === $fp)
{
  print("Impossible to open file\r\n");
  return;
}
if(false === ftruncate($fp,0))
{
  print("Impossible to trunc file\r\n");
  fclose($fp);
  return;
}
if(false === fputs($fp, $_SERVER["REMOTE_ADDR"]))
{
  print("Impossible to write in file\r\n");
  fclose($fp);
  return;
}
if(false === fclose($fp))
{
  print("Impossible to close file\r\n");
  return;
}

print("LOST safety.http_status OK\r\n");
?>

