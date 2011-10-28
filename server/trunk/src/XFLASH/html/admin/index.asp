<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title><%host_name%> - Network Configuration</title>
</head>
<body><div align="center">
<h1><%host_name%></h1>
<h2>Network Configuration</h2>
</div><br>
<div align="center">
<a href="../cgi/mon_showThreads.cgi">ShowThreads</a>
<a href="../cgi/mon_showSockets.cgi">ShowSockets</a>
<a href="../cgi/mon_showPorts.cgi">ShowPorts</a>
</div>
<form enctype="text/plain" action="../cgi/admin_form.cgi" method="GET" name="admin_form"><br>
<TABLE align="center">
<TR><TD>Ethernut OS version</TD><TD><input type="text" maxlength="8" size="8" name="OS_Version" value="<%nut_version%>" readonly disabled></TD></TR>
<TR><TD>Host name</TD><TD><input type="text" maxlength="15" size="15" name="Host_name" value="<%host_name%>"></TD></TR>
<TR><TD>MAC address</TD><TD><input type="text" maxlength="17" size="17" name="MAC_address" value="<%nut_mac_addr%>"></TD></TR>
<TR><TD>IP address</TD><TD><input type="text" maxlength="15" size="15" name="IP_address" value="<%nut_ip_addr%>"></TD></TR>
<TR><TD>Net mask</TD><TD><input type="text" maxlength="15" size="15" name="Net_mask" value="<%nut_ip_mask%>"></TD></TR>
<TR><TD>Gateway</TD><TD><input type="text" maxlength="15" size="15" name="Gateway" value="<%nut_gateway%>"></TD></TR>
<TR><TD>GSM1</TD><TD><input type="text" maxlength="10" size="10" name="admin_gsm1" value="<%admin_gsm1%>"></TD></TR>
<TR><TD>GSM2</TD><TD><input type="text" maxlength="10" size="10" name="admin_gsm2" value="<%admin_gsm2%>"></TD></TR>
</TABLE>
<br><br>
<div align="center">
<input name="button" value="Reset" type="reset">
<input name="button"  value="Send"  type="submit">
<br><br>
<a href="../index.asp">Return to main menu</a>
</div>
</form>
</body></html>
