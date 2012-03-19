document.write("\
<head>\
  <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\
  <meta http-equiv=\"content-script-type\" content=\"text/javascript\" />\
  <meta http-equiv=\"content-style-type\" content=\"text/css\" />\
  <meta http-equiv=\"content-language\" content=\"fr\" />\
  <title>FreeCommande</title>\
  <style type=\"text/css\" media=\"screen\">@import \"http://lebomb.free.fr/LOST/media/freebox/css/reset.css\";</style>\
  <style type=\"text/css\" media=\"screen\">@import \"http://lebomb.free.fr/LOST/media/freebox/css/freecommande-v2.css\";</style>\
  <script src=\"http://lebomb.free.fr/LOST/media/freebox/js/jquery-1.4.2.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>\
  <script src=\"http://lebomb.free.fr/LOST/media/freebox/js/jquery.cookies.2.2.0.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>\
  <script src=\"http://lebomb.free.fr/LOST/media/freebox/js/jquery.timers.js\" type=\"text/javascript\" charset=\"utf-8\"></script>\
  <script src=\"http://lebomb.free.fr/LOST/media/freebox/js/freecommande.js\" type=\"text/javascript\" charset=\"utf-8\"></script>\
  <link rel=\"apple-touch-icon-precomposed\" href=\"http://lebomb.free.fr/MM/media/freebox/images/icon-freecommande.png\" />\
  <link rel=\"apple-touch-startup-image\" href=\"http://lebomb.free.fr/MM/media/freebox/images/startup-freecommande.png\" />\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0;\" />\
  <meta name=\"apple-mobile-web-app-capable\" content=\"yes\" />\
  <meta name=\"apple-mobile-web-app-status-bar-style\" content=\"black\" />\
  <meta name=\"dc.language\" content=\"fr\" scheme=\"DCTERMS.RFC1766\" />\
  <meta name=\"dc.publisher\" content=\"grafactory.net\" />\
  <meta name=\"dc.creator\" content=\"Yves Tannier [grafactory.net]\" />\
  <meta name=\"dc.rights\" content=\"Licence LGPL 2010\" />\
  <meta name=\"dc.format\" content=\"text/html; charset=UTF-8\" />\
  <meta name=\"dc.type\" content=\"Text\" scheme=\"DCTERMS.DCMIType\" />\
  <link rel=\"schema.DC\" href=\"http://purl.org/dc/elements/1.1/\" />\
  <link rel=\"schema.DCTERMS\" href=\"http://purl.org/dc/terms/\" />\
  <script type=\"text/javascript\">\
    var _gaq = _gaq || [];\
    _gaq.push(['_setAccount', 'UA-2873345-2']);\
    _gaq.push(['_trackPageview']);\
    (function() {\
      var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;\
      ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';\
      var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);\
    })();\
  </script>\
</head>\
<body>\
    <ul id=\"telecommande\">\
        <li id=\"red\"><a href=\"red\"><span>red</span></a></li>\
        <li id=\"green\"><a href=\"green\"><span>green</span></a></li>\
        <li id=\"blue\"><a href=\"blue\"><span>blue</span></a></li>\
        <li id=\"yellow\"><a href=\"yellow\"><span>yellow</span></a></li>\
        <li id=\"power\"><a href=\"power\"><span>power</span></a></li>\
        <li id=\"tv\"><a href=\"tv\"><span>tv</span></a></li>\
        <li id=\"id1\"><a href=\"1\"><span>1</span></a></li>\
        <li id=\"id2\"><a href=\"2\"><span>2</span></a></li>\
        <li id=\"id3\"><a href=\"3\"><span>3</span></a></li>\
        <li id=\"id4\"><a href=\"4\"><span>4</span></a></li>\
        <li id=\"id5\"><a href=\"5\"><span>5</span></a></li>\
        <li id=\"id6\"><a href=\"6\"><span>6</span></a></li>\
        <li id=\"id7\"><a href=\"7\"><span>7</span></a></li>\
        <li id=\"id8\"><a href=\"8\"><span>8</span></a></li>\
        <li id=\"id9\"><a href=\"9\"><span>9</span></a></li>\
        <li id=\"id0\"><a href=\"0\"><span>0</span></a></li>\
        <li id=\"back\"><a href=\"back\"><span>back</span></a></li>\
        <li id=\"swap\"><a href=\"swap\"><span>swap</span></a></li>\
        <li id=\"info\"><a href=\"info\"><span>info</span></a></li>\
        <li id=\"mail\"><a href=\"mail\"><span>mail</span></a></li>\
        <li id=\"pip\"><a href=\"pip\"><span>pip</span></a></li>\
        <li id=\"epg\"><a href=\"epg\"><span>epg</span></a></li>\
        <li id=\"media\"><a href=\"media\"><span>media</span></a></li>\
        <li id=\"options\"><a href=\"options\"><span>options</span></a></li>\
        <li id=\"help\"><a href=\"help\"><span>help</span></a></li>\
        <li id=\"ok\"><a href=\"ok\"><span>ok</span></a></li>\
        <li id=\"rec\"><a href=\"rec\"><span>rec</span></a></li>\
        <li id=\"play\"><a href=\"play\"><span>play</span></a></li>\
        <li id=\"stop\"><a href=\"stop\"><span>stop</span></a></li>\
        <li id=\"bwd\"><a href=\"bwd\"><span>bwd</span></a></li>\
        <li id=\"fwd\"><a href=\"fwd\"><span>fwd</span></a></li>\
        <li id=\"prev\"><a href=\"prev\"><span>prev</span></a></li>\
        <li id=\"next\"><a href=\"next\"><span>next</span></a></li>\
        <li id=\"vol_inc\"><a href=\"vol_inc\"><span>vol_inc</span></a></li>\
        <li id=\"vol_dec\"><a href=\"vol_dec\"><span>vol_dec</span></a></li>\
        <li id=\"mute\"><a href=\"mute\"><span>mute</span></a></li>\
        <li id=\"prgm_inc\"><a href=\"prgm_inc\"><span>prgm_inc</span></a></li>\
        <li id=\"prgm_dec\"><a href=\"prgm_dec\"><span>prgm_dec</span></a></li>\
        <li id=\"up\"><a href=\"up\"><span>up</span></a></li>\
        <li id=\"right\"><a href=\"right\"><span>right</span></a></li>\
        <li id=\"down\"><a href=\"down\"><span>down</span></a></li>\
        <li id=\"left\"><a href=\"left\"><span>left</span></a></li>\
        <li id=\"home\"><a href=\"home\"><span>home</span></a></li>\
        <li id=\"list\"><a href=\"list\"><span>list</span></a></li>\
        <li id=\"remotekey\"><a href=\"#\"><span>remotekey</span></a></li>\
        <li id=\"linkkey\"><a href=\"linkkey\"><span>linkkey</span></a></li>\
    </ul>\
    <div id=\"channelslist\" class=\"hide\">\
        <div class=\"blackbar\">\
            <div class=\"backbutton\"><a href=\"./\" rel=\"channelslist\"><span>back</span></a></div>\
        </div>\
        <div class=\"conteneur\">\
            <ul class=\"plastic\" id=\"listchannels\"></ul>\
        </div>\
    </div>\
    <div id=\"infosblock\" class=\"hide\">\
        <div class=\"blackbar\">\
            <div class=\"backbutton\"><a href=\"./\" rel=\"infosblock\"><span>back</span></a></div>\
        </div>\
    </div>\
</body>\
");