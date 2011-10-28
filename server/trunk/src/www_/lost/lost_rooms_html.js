document.write("\
<div class=\"iLayer\" id=\"waRooms\" title=\"Rooms\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li><a href=\""+lost_icons_path+"plan.jpg\"><img class=\"picto\" src=\""+lost_icons_path+"loc.jpg\">Plan</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Room"+String(ROOM_SALON)+"_bg\"><a href=\"#_Salon\"><img class=\"picto\" src=\""+lost_icons_path+"canape.jpg\">Salon</a></li>\
            <li id=\"Room"+String(ROOM_CUISINE)+"_bg\"><a href=\"#_Cuisine\"><img class=\"picto\" src=\""+lost_icons_path+"cuisine.jpg\">Cuisine</a></li>\
            <li id=\"Room"+String(ROOM_C1)+"_bg\"><a href=\"#_C1\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre 1</a></li>\
            <li id=\"Room"+String(ROOM_C2)+"_bg\"><a href=\"#_C2\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre 2</a></li>\
            <li id=\"Room"+String(ROOM_SDB)+"_bg\"><a href=\"#_Sdb\"><img class=\"picto\" src=\""+lost_icons_path+"douche.jpg\">Salle de Bain</a></li>\
            <li id=\"Room"+String(ROOM_WC)+"_bg\"><a href=\"#_Wc\"><img class=\"picto\" src=\""+lost_icons_path+"wc.jpg\">WC</a></li>\
            <li id=\"Room"+String(ROOM_TERRASSE)+"_bg\"><a href=\"#_Terrasse\"><img class=\"picto\" src=\""+lost_icons_path+"terrasse.jpg\">Terrasse</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_Cameras\"><img class=\"picto\" src=\""+lost_icons_path+"cam.jpg\">Cameras</a></li>\
        </ul>\
        <ul>\
            <li><a href=\"javascript:lost_room_light_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_light_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumieres</li>\
            <li><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            <li><a href=\"javascript:lost_room_heater_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_heater_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</li>\
            <li><a href=\"javascript:lost_room_elec_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_elec_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Eqpts Electriques</li>\
        </ul>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waSalon\" title=\"Salon\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light0\">Plafond</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light1\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,1);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light1\">Design</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Neons</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light2\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,2);\"><img class=\"picto\" src=\""+lost_icons_path+"neon.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light2\">Bleu</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light3\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,3);\"><img class=\"picto\" src=\""+lost_icons_path+"neon.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light3\">Rouge</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light4\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,4);\"><img class=\"picto\" src=\""+lost_icons_path+"neon.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light4\">Vert</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Diodes</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light5\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,5);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light5\">Gauche</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light6\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,6);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light6\">Droite</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light7\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,7);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light7\">Etagere</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_SalonInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waCuisine\" title=\"Cuisine\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_CUISINE)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_CUISINE,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_CUISINE)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_CUISINE,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_CuisineInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC1\" title=\"Chambre 1\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C1)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C1,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C1)+"_Light0\">Plafond</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C1)+"_Light1\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C1,1);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C1)+"_Light1\">Chevet</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C1,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Chambre 1Info\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC2\" title=\"Chambre 2\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C2)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C2,0,this);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C2)+"_Light0\">Plafond</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C2)+"_Light1\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C2,1,this);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C2)+"_Light1\">Chevet</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C2,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Autres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C2)+"_Elec0\" class=\"iToggle\" title=\"ON|OFF\"><img class=\"picto\" src=\""+lost_icons_path+"pc.jpg\"><label for=\"Room"+String(ROOM_C2)+"_Elec0\">PC</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Chambre 2Info\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waSdb\" title=\"Salle de bain\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SDB)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SDB,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_SDB)+"_Light0\">Plafond</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SDB)+"_Light1\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SDB,1);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_SDB)+"_Light1\">Miroir</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SDB,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Autres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SDB)+"_Elec0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_elec_set(ROOM_SDB,0);\"><img class=\"picto\" src=\""+lost_icons_path+"mal.jpg\"><label for=\"Room"+String(ROOM_SDB)+"_Elec0\">Machine a Laver</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Salle de BainInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waWc\" title=\"WC\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_WC)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_WC,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_WC)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_WC,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_WC,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_WC,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_WC,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_WC,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_WC,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_WCInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waTerrasse\" title=\"Terrasse\">\
		    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_TERRASSE)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_TERRASSE,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_TERRASSE)+"_Light0\">Phare</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_TERRASSE,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_TERRASSE,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_TERRASSE,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_TerrasseInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waCameras\" title=\"Cameras\">\
    <div class=\"iMenu\">\
        <ul>\
            <li><a href=\"http://bourdilot.no-ip.info:81\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden.jpg\">Salle a manger</a></li>\
            <li><a href=\"http://bourdilot.no-ip.info:82\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden.jpg\">Cuisine</a></li>\
            <li><a href=\"http://bourdilot.no-ip.info:83\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"wvc54gca.jpg\">Exterieur</a></li>\
        </ul>\
    </div>\
</div>\
");

function printRoomInfo(room, name)
{
document.write("\
<div class=\"iLayer\" id=\"wa"+name+"Info\" title=\""+name+"\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul>\
                <li id=\"Room"+String(room)+"_Error_bg\"><span id=\"Room"+String(room)+"_Error_Trig\">Unknown</span>Error</li>\
            </ul>\
            <ul>\
                <li><span id=\"Room"+String(room)+"_Type\">Unknown</span>Type</li>\
                <li><span id=\"Room"+String(room)+"_Version\">Unknown</span>Version</li>\
                <li><span id=\"Room"+String(room)+"_Adress\">Unknown</span>Adresse</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Temp_Max_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Max\">Unknown</span>Temperature Max</li>\
                <li id=\"Room"+String(room)+"_Temp_Max_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Max_Ctrl\">Unknown</span>Temperature Max Control</li>\
                <li id=\"Room"+String(room)+"_Temp_Max_Th_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Max_Th\">Unknown</span>Temperature Max Threshold</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Temp_Min_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Min\">Unknown</span>Temperature Min</li>\
                <li id=\"Room"+String(room)+"_Temp_Min_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Min_Ctrl\">Unknown</span>Temperature Min Control</li>\
                <li id=\"Room"+String(room)+"_Temp_Min_Th_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Room"+String(room)+"_Temp_Min_Th\">Unknown</span>Temperature Min Threshold</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Hum_bg\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\"><span id=\"Room"+String(room)+"_Hum\">Unknown</span>Humidite</li>\
                <li id=\"Room"+String(room)+"_Hum_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\"><span id=\"Room"+String(room)+"_Hum_Ctrl\">Unknown</span>Humidite Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Smoke_bg\"><img class=\"picto\" src=\""+lost_icons_path+"gaz.jpg\"><span id=\"Room"+String(room)+"_Smoke\">Unknown</span>Smoke</li>\
                <li id=\"Room"+String(room)+"_Smoke_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"gaz.jpg\"><span id=\"Room"+String(room)+"_Smoke_Ctrl\">Unknown</span>Smoke Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Perimeter_bg\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Room"+String(room)+"_Perimeter\">Unknown</span>Perimeter</li>\
                <li id=\"Room"+String(room)+"_Perimeter_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Room"+String(room)+"_Perimeter_Ctrl\">Unknown</span>Perimeter Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Volume_bg\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Room"+String(room)+"_Volume\">Unknown</span>Volume</li>\
                <li id=\"Room"+String(room)+"_Volume_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Room"+String(room)+"_Volume_Ctrl\">Unknown</span>Volume Control</li>\
            </ul>\
            <ul>\
                <li id=\"Room"+String(room)+"_Simulation_bg\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><span id=\"Room"+String(room)+"_Simulation\">Unknown</span>Simulation</li>\
                <li id=\"Room"+String(room)+"_Simulation_Ctrl_bg\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><span id=\"Room"+String(room)+"_Simulation_Ctrl\">Unknown</span>Simulation Control</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
}

printRoomInfo(ROOM_SALON   , "Salon"        );
printRoomInfo(ROOM_CUISINE , "Cuisine"      );
printRoomInfo(ROOM_C1      , "Chambre 1"    );
printRoomInfo(ROOM_C2      , "Chambre 2"    );
printRoomInfo(ROOM_SDB     , "Salle de Bain");
printRoomInfo(ROOM_WC      , "WC"           );
printRoomInfo(ROOM_TERRASSE, "Terrasse"     );
