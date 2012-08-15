document.write("\
<div class=\"iLayer\" id=\"waHome\" title=\"Home\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li id=\"Event"+String(EVENT_POWER_1)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Event"+String(EVENT_POWER_1)+"_Status\">Unknown</span>Reseau</li>\
            <li id=\"Alarm_bg\"><a href=\"#_Alarmes\"><img class=\"picto\" src=\""+lost_icons_path+"detector.jpg\"/>Alarmes</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Event"+String(EVENT_SHUTTERS_ALL)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_ALL        , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_ALL        , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\"><span id=\"Event"+String(EVENT_SHUTTERS_ALL)+"_Status\">Unknown</span>Tous les Volets</li>\
            <li id=\"Event"+String(EVENT_SHUTTERS_UPSTAIRS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_UPSTAIRS   , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_UPSTAIRS   , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Event"+String(EVENT_SHUTTERS_UPSTAIRS)+"_Status\">Unknown</span>Volets Etage</li>\
            <li id=\"Event"+String(EVENT_SHUTTERS_DOWNSTAIRS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DOWNSTAIRS , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DOWNSTAIRS , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"canape.jpg\"><span id=\"Event"+String(EVENT_SHUTTERS_DOWNSTAIRS)+"_Status\">Unknown</span>Volets Rez de Chaussé</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Room"+String(ROOM_SALON)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter0_Status\">Unknown</span>Salon Grande Baie</li>\
            <li id=\"Room"+String(ROOM_SALON)+"_Shutter1_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter1_Status\">Unknown</span>Salon Petite Baie</li>\
            <li id=\"Room"+String(ROOM_SALON)+"_Shutter2_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_SALON)+"_Shutter2_Status\">Unknown</span>Salon Simple Baie</li>\
            <li id=\"Room"+String(ROOM_CUISINE)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_CUISINE)+"_Shutter0_Status\">Unknown</span>Cuisine</li>\
            <li id=\"Room"+String(ROOM_BUREAU)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_BUREAU)+"_Shutter0_Status\">Unknown</span>Bureau</li>\
            <li id=\"Room"+String(ROOM_C1)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C1)+"_Shutter0_Status\">Unknown</span>Marine</li>\
            <li id=\"Room"+String(ROOM_C2)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C2)+"_Shutter0_Status\">Unknown</span>M&M</li>\
            <li id=\"Room"+String(ROOM_C3)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C3)+"_Shutter0_Status\">Unknown</span>Amis</li>\
            <li id=\"Room"+String(ROOM_C4)+"_Shutter0_Status_bg\"><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\" alt=\"Volet\"><span id=\"Room"+String(ROOM_C4)+"_Shutter0_Status\">Unknown</span>Dressing</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Scenes_bg\"><a href=\"#_Scenes\"><img class=\"picto\" src=\""+lost_icons_path+"scenes.jpg\" alt=\"Scenes\">Scenes</a></li>\
            <li><a href=\"#_Evenements\"><img class=\"picto\" src=\""+lost_icons_path+"wakeup.jpg\"/>Evenements</a></li>\
            <li id=\"Rooms_bg\"><a href=\"#_Rooms\"><img class=\"picto\" src=\""+lost_icons_path+"home.jpg\" alt=\"Home\">Rooms</a></li>\
            <li id=\"Media_bg\"><a href=\"#_Media\"><img class=\"picto\" src=\""+lost_icons_path+"media.jpg\" alt=\"Media\">Media</a></li>\
            <li class=\"iRadio\"><img class=\"picto\" src=\""+lost_icons_path+"ambiance.jpg\"/>Ambiances\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_CINEMA);\">Cinema</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ROMANTIQUE);\">Romantique</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ECO);\">Economie d\"energie</label>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Safety_bg\"><a href=\"#_Surveillances\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"/>Surveillances</a></li>\
            <li><a href=\"cgi/monitor.cgi\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"system.jpg\" alt=\"System\">System</a></li>\
        </ul>\
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
