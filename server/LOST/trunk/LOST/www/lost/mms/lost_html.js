document.write("\
<div class=\"iLayer\" id=\"waHome\" title=\"Home\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul class=\"iArrow\">\
                <li id=\"Media_bg\"><a href=\"#_Media\"><img class=\"picto\" src=\""+lost_icons_path+"media.jpg\" alt=\"Media\">Media</a></li>\
                <li id=\"Rooms_bg\"><a href=\"#_Rooms\"><img class=\"picto\" src=\""+lost_icons_path+"home.jpg\" alt=\"Home\">Rooms</a></li>\
                <li id=\"Scenes_bg\"><a href=\"#_Scenes\"><img class=\"picto\" src=\""+lost_icons_path+"scenes.jpg\" alt=\"Scenes\">Scenes</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <ul class=\"iArrow\">\
                <li id=\"Safety_bg\"><a href=\"#_Surveillances\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"/>Surveillances</a></li>\
                <li id=\"Alarm_bg\"><a href=\"#_Alarmes\"><img class=\"picto\" src=\""+lost_icons_path+"detector.jpg\"/>Alarmes</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Volets</legend>\
            <ul>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter0_Status\">Unknown</span>Salon Grande Baie</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter1_Status\">Unknown</span>Salon Petite Baie</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter2_Status\">Unknown</span>Salon Simple Biae</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_CUISINE)+"_Shutter0_Status\">Unknown</span>Cuisine</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_BUREAU)+"_Shutter0_Status\">Unknown</span>Bureau</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_TERRASSE)+"_Shutter0_Status\">Unknown</span>Terrasse</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C1)+"_Shutter0_Status\">Unknown</span>Marine</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C2)+"_Shutter0_Status\">Unknown</span>M&M</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C3)+"_Shutter0_Status\">Unknown</span>Amis</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C4)+"_Shutter0_Status\">Unknown</span>Dressing</li>\
                <li><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SDB)+"_Shutter0_Status\">Unknown</span>Salle de Bain</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <ul class=\"iArrow\">\
                <li><a href=\"cgi/monitor.cgi\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"system.jpg\" alt=\"System\">System</a></li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waMedia\" title=\"Media\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li><a href=\"tv.asp\"><img class=\"picto\" src=\""+lost_icons_path+"tv.jpg\" alt=\"TV\">TV</a></li>\
            <li><a href=\"freebox.asp\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"fb.jpg\" alt=\"FB\">Freebox</a></li>\
            <li><a href=\"sat.asp\"><img class=\"picto\" src=\""+lost_icons_path+"sat.jpg\" alt=\"Sat\">Satellite</a></li>\
            <li><a href=\"hifi.asp\"><img class=\"picto\" src=\""+lost_icons_path+"hifi.jpg\" alt=\"Hifi\">Hifi</a></li>\
        </ul>\
    </div>\
</div>\
");
