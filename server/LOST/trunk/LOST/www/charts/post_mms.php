<!DOCTYPE html>
<html>
<head>
</head>
<body>
<FORM method=post action="http://lebomb.free.fr/LOST/charts/insert_mms.php">
MnM Insert POST Form
<TABLE>
<?php
for($i=0; $i<10; $i++)
{
  echo "<TR><TD>room".$i."_temp_value</TD><TD><INPUT type=text name='room".$i."_temp_value' value='".$i."'></TD></TR>";
}
?>
<TR><TD>safety_ups_temp</TD><TD><INPUT type=text name="safety_ups_temp" value="123"></TD></TR>
<TR><TD>safety_rack_temp</TD><TD><INPUT type=text name="safety_rack_temp" value="231"></TD></TR>
<TR><TD><INPUT type="submit" value="Send"></TD></TR>
</TABLE>
</FORM>
</body>
</html>
