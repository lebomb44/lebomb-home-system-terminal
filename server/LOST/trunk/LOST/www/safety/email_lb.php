<?php
  $from_mail = 'lb@lost.fr';
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
  $sujet = 'LOST Alert LB : '.$msg;
  $message = $sujet."\r\n".'Sent by '.$from_mail.' at '.date('H:i:s  d.m.Y')."\r\n-- LOST\r\n";

  /* Set the email adresses */
  $status_mail1 = mail("cambon.olivier@gmail.com", $sujet, $message, $header);

  if($status_mail1 == true) { print("LOST Email OK\r\n"); } else { print("LOST Email KO\r\n"); }
?>
