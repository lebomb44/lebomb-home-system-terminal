<?php
  $from_mail = 'alert@lost.fr';
  $header   = 'From: "LOST Alert"<'.$from_mail.'>'."\n";
  $header .= 'Reply-To: noreply@lost.fr'."\n";
  $header  .= 'X-Priority: 1'."\n";
  $header .= 'Content-Type: text/plain; charset="iso-8859-1"'."\n";
  $header .= 'Content-Transfer-Encoding: 8bit';
  if(isset($_GET['msg']) && !empty($_GET['msg'])) { $msg=$_GET['msg']; } else { $msg="UNKNOWN ALERT"; }
  $sujet = 'LOST Alert : '.$msg;
  $message = $sujet."\n".'Sent by '.$from_mail.' at '.date('h:i:s d.m.Y');

  /* TODO set the email adresses */
  $status_mail1 = mail("cambon.olivier@gmail.com", $sujet, $message, $header);
  $status_mail2 = mail("0689350159@orange.fr"    , $sujet, $message, $header);

  if((status_mail1 == true) && (status_mail2 == true)) { print('OK'); } else { print('KO'); }
?>

