document.write("\
<div class=\"iLayer\" id=\"waRooms\" title=\"Rooms\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li><a href=\""+lost_icons_path+"plan.jpg\"><img class=\"picto\" src=\""+lost_icons_path+"loc.jpg\">Plan</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li id=\"Room"+String(ROOM_SALON)+"_bg\"><a href=\"#_Salon\"><img class=\"picto\" src=\""+lost_icons_path+"canape.jpg\">Salon</a></li>\
            <li id=\"Room"+String(ROOM_CUISINE)+"_bg\"><a href=\"#_Cuisine\"><img class=\"picto\" src=\""+lost_icons_path+"cuisine.jpg\">Cuisine</a></li>\
            <li id=\"Room"+String(ROOM_BUREAU)+"_bg\"><a href=\"#_Bureau\"><img class=\"picto\" src=\""+lost_icons_path+"bureau.jpg\">Bureau</a></li>\
            <li id=\"Room"+String(ROOM_TERRASSE)+"_bg\"><a href=\"#_Terrasse\"><img class=\"picto\" src=\""+lost_icons_path+"terrasse.jpg\">Terrasse</a></li>\
            <li id=\"Room"+String(ROOM_C1)+"_bg\"><a href=\"#_C1\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre Marine</a></li>\
            <li id=\"Room"+String(ROOM_C2)+"_bg\"><a href=\"#_C2\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre M&M</a></li>\
            <li id=\"Room"+String(ROOM_C3)+"_bg\"><a href=\"#_C3\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre Amis</a></li>\
            <li id=\"Room"+String(ROOM_C4)+"_bg\"><a href=\"#_C4\"><img class=\"picto\" src=\""+lost_icons_path+"dressing.jpg\">Dressing</a></li>\
            <li id=\"Room"+String(ROOM_WC)+"_bg\"><a href=\"#_Wc\"><img class=\"picto\" src=\""+lost_icons_path+"wc.jpg\">WC</a></li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_Cameras\"><img class=\"picto\" src=\""+lost_icons_path+"cam.jpg\">Cameras</a></li>\
        </ul>\
        <ul>\
            <li><a href=\"javascript:lost_room_light_all_set(0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_room_light_all_set(1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumieres</li>\
            <li><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_all_set(ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_MAX+3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_MAX+3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</li>\
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
            <legend>LEDs</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light2\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,2);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light2\">Gauche</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light3\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,3);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light3\">Centre</label></li>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_SALON)+"_Light4\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_SALON,4);\"><img class=\"picto\" src=\""+lost_icons_path+"diode.jpg\"><label for=\"Room"+String(ROOM_SALON)+"_Light4\">Droite</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Grande Baie</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,1,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Petite Baie</li>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,2,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,3,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_SALON,3,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Simple</li>\
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
<div class=\"iLayer\" id=\"waBureau\" title=\"Bureau\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_BUREAU)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_BUREAU,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_BUREAU)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_BUREAU,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_BureauInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
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
<div class=\"iLayer\" id=\"waC1\" title=\"Chambre Marine\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C1)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C1,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C1)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C1,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Climatisation</legend>\
            <ul>\
                <li>Temperature\
                <SELECT id=\"Room"+String(ROOM_C1)+"_Clim_Temp\"><script language=\"Javascript\">printSelectOption(\"Room"+String(ROOM_C1)+"_Clim_Temp\",99);</script></SELECT>\
                </li>\
                <li><a href=\"javascript:lost_room_clim_set(ROOM_C1,ROOM_CLIM_ON);\" class=\"iButton iBAction\" style=\"width:60px\">ON</a><a href=\"javascript:lost_room_clim_set(ROOM_C1,ROOM_CLIM_OFF);\" class=\"iButton iBWarn\" style=\"width:60px\">OFF</a><img class=\"picto\" src=\""+lost_icons_path+"clim.jpg\">Commande</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Chambre MarineInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC2\" title=\"Chambre M&M\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C2)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C2,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C2)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C2,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Chambre M&MInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC3\" title=\"Chambre Amis\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C3)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C3,0);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C3)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C3,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Chambre AmisInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
    </div>\
</div>\
");
document.write("\
<div class=\"iLayer\" id=\"waC4\" title=\"Dressing\">\
    <div class=\"iMenu\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Lumieres</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Room"+String(ROOM_C4)+"_Light0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_room_light_set(ROOM_C4,0,this);\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\"><label for=\"Room"+String(ROOM_C4)+"_Light0\">Plafond</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Ouvertures</legend>\
            <ul>\
                <li><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_DOWN);\" class=\"iButton iBWarn\" style=\"width:60px\">FERMER</a><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_STOP);\" class=\"iButton iBAction\" style=\"width:60px\">STOP</a><a href=\"javascript:lost_room_shutter_set(ROOM_C4,0,ROOM_SHUTTER_UP);\" class=\"iButton iBWarn\" style=\"width:60px\">OUVRIR</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Volets</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_DressingInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
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
<div class=\"iLayer\" id=\"waCameras\" title=\"Cameras\">\
    <div class=\"iMenu\">\
        <ul>\
            <li><a href=\"http://bourdilot.no-ip.info:81\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden.jpg\">Salle a manger</a></li>\
            <li><a href=\"http://bourdilot.no-ip.info:82\" target=\"_self\"><img class=\"picto\" src=\""+lost_icons_path+"heden.jpg\">Bureau</a></li>\
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
            <ul>\
                <li id=\"Room"+String(room)+"_Clim_Cmd_bg\"><img class=\"picto\" src=\""+lost_icons_path+"clim.jpg\"><span id=\"Room"+String(room)+"_Clim_Cmd\">Unknown</span>Climatisation</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
}

printRoomInfo(ROOM_SALON   , "Salon"         );
printRoomInfo(ROOM_CUISINE , "Cuisine"       );
printRoomInfo(ROOM_BUREAU  , "Bureau"        );
printRoomInfo(ROOM_TERRASSE, "Terrasse"      );
printRoomInfo(ROOM_C1      , "Chambre Marine");
printRoomInfo(ROOM_C2      , "Chambre M&M"   );
printRoomInfo(ROOM_C3      , "Chambre Amis"  );
printRoomInfo(ROOM_C4      , "Dressing"      );
printRoomInfo(ROOM_WC      , "WC"            );
