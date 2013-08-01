<?php
  if(!isset($_GET["tab"]))
  {
    echo "ERROR : Arguments tab not set";
    exit();
  }
  $tab = $_GET["tab"];
  $from_mail = 'alert@lost.fr';
  $header  = 'MIME-Version: 1.0'."\r\n";
  $header .= 'Content-type: text/plain; charset=iso-8859-1'."\r\n";
  $header .= 'Content-transfer-encoding: 8bit'."\r\n";
  $header .= 'Content-Disposition: inline'."\r\n";
  $header .= 'From:  !!! LOST Alert !!! <'.$from_mail.'>'."\r\n";
  $header .= 'Reply-To: noreply@lost.fr'."\r\n";
  $header .= 'X-Priority: 1'."\r\n";
  $header .= 'X-MSMail-Priority: High'."\r\n";
  $header .= 'Importance: High'."\r\n";
  if(isset($_GET['msg']) && !empty($_GET['msg'])) { $msg=$_GET['msg']; } else { $msg="UNKNOWN ALERT"; }
  $sujet = 'LOST Alert '.strtoupper($tab).' : '.$msg;
  $message = $sujet."\r\n".'Sent by '.$from_mail.' at '.date('H:i:s  d.m.Y')."\r\n-- LOST\r\n";

  /* Send email */
  if("mms" == $tab)
  {
    $status_mail1 = mail("cambon.olivier@gmail.com", $sujet, $message, $header);
    $status_mail2 = mail("maximedarde@gmail.com", $sujet, $message, $header);
    $status_mail3 = mail("mariaucam@gmail.com", $sujet, $message, $header);
  }
  else if("bt" == $tab)
  {
    $status_mail1 = mail("cambon.olivier@gmail.com", $sujet, $message, $header);
    $status_mail2 = mail("geni.cambon@free.fr", $sujet, $message, $header);
    $status_mail3 = mail("nicole.cambon@gmail.com", $sujet, $message, $header);
  }
  else if("lb" == $tab)
  {
    $status_mail1 = mail("cambon.olivier@gmail.com", $sujet, $message, $header);
    $status_mail2 = mail("stephanie.minozzo@gmail.com", $sujet, $message, $header);
    $status_mail3 = true;
  }
  else if("fr" == $tab)
  {
    $status_mail1 = mail("cambon.olivier@gmail.com", $sujet, $message, $header);
    $status_mail2 = mail("geni.cambon@free.fr", $sujet, $message, $header);
    $status_mail3 = mail("nicole.cambon@gmail.com", $sujet, $message, $header);
  }
  else
  {
  	$status_mail1 = false;
  	$status_mail2 = false;
  	$status_mail3 = false;
  }

  /* Check results */
  if((true == $status_mail1) && (true == $status_mail2) && (true == $status_mail3))
  { print("LOST Email OK\r\n"); }
  else { print("LOST Email KO\r\n"); }
?>
