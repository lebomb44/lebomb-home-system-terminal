<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN" "http://www.w3.org/TR/html4/frameset.dtd">
<html>

<head>
<title>Bourdilot</title>
</head>
<body>
<SCRIPT language="javascript">
function openCams(adr, name, top, left, height, width)
{
  var win;
  win=window.open(adr,name,"top="+top+",left="+left+",height="+height+",width="+width+",menubar=no,location=no,toolbar=no,scrollbars=auto,status=no,directories=no,toolbar=no,titlebar=no,fullscreen=yes");
}

function openAllCams()
{
  openCams("http://bourdilot.no-ip.org:81", "Salon"  , 0,0,(screen.availHeight)/2-50,(screen.availWidth)/2);
  openCams("http://bourdilot.no-ip.org:82", "Couloir", 0,(screen.availWidth)/2,(screen.availHeight)/2-50,(screen.availWidth)/2);
  openCams("http://bourdilot.no-ip.org:83", "Cuisine", (screen.availHeight)/2,0,(screen.availHeight)/2-50,(screen.availWidth)/2);
  openCams("http://bourdilot.no-ip.org:84", "Arriere", (screen.availHeight)/2,(screen.availWidth)/2,(screen.availHeight)/2-50,(screen.availWidth)/2);
  openCams("http://bourdilot.no-ip.org:85", "Facade"  , 0,0,(screen.availHeight)/2-50,(screen.availWidth)/2);
}

document.onReady=openAllCams();
</SCRIPT>
</body>
</html>

