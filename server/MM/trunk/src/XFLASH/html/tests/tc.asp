<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
         "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>TC Raw</title>

<script type="text/javascript" src="../lost/lost.js"></script>
<script type="text/javascript">
var ip1;
var ip2;
var port;

var adr;
var cmd;

var tc_input;
var tc_output;

  function lost_send()
  {
    ip1 = document.getElementById("ip1_id");
    ip2 = document.getElementById("ip2_id");
    port = document.getElementById("port_id");

    adr = document.getElementById("adr_id");
    cmd = document.getElementById("cmd_id");

    tc_input = document.getElementById("tc_in");
    tc_output = document.getElementById("tc_out");
    lost_tc(ip1.value + ip2.value + port.value, adr.value, cmd.value, tc_input.value, tc_output);
  }

</script>
</head>
<body>

TC
<input id="ip1_id" type="text" name="ip1" value="010_" maxlength="4" size="4">
<input id="ip2_id" type="text" name="ip2" value="002_" maxlength="4" size="4">
<input id="port_id" type="text" name="port" value="123_" maxlength="4" size="4">

<input id="adr_id" type="text" name="adr" value="1" maxlength="3" size="3">
<input id="cmd_id" type="text" name="cmd" value="2" maxlength="3" size="3">

<input id="tc_in" type="text" name="tc_in" value="001_002_003_">
<input type="button" onclick="lost_send();" value="Send">
<input id="tc_out" type="text" name="tc_out" value="waiting for response...">

</body>
</html>

