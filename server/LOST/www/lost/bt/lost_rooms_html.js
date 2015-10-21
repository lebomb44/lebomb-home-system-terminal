document.write("\
<div class=\"iLayer\" id=\"waRooms\" title=\"Rooms\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li><a href=\"#_Cameras\"><img class=\"picto\" src=\""+lost_icons_path+"cam.jpg\">Cameras</a></li>\
        </ul>\
        <ul>\
            <li><a href=\"javascript:lost_room_light_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_light_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumieres</li>\
            <li><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_MAX+3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_MAX+3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</li>\
            <li><a href=\"javascript:lost_room_elec_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_elec_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Eqpts Electriques</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"http://lebomb.free.fr/LOST/charts/chart.php?tab=bt\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\">Courbes de temperature</a></li>\
        </ul>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waCameras\" title=\"Cameras\">\
    <div class=\"iMenu\">\
        <ul>\
            <li><a href=\"http://bourdilot.no-ip.org:81\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V5_5.jpg\">Salle a manger</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:82\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V2_2.jpg\">Couloir</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:83\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V5_5.jpg\">Cuisine</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:84\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V3_3.jpg\">Arriere</a></li>\
            <li><a href=\"http://bourdilot.no-ip.org:85\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden_V3_3.jpg\">Avant</a></li>\
        </ul>\
    </div>\
</div>\
");
