document.write("\
<div class=\"iLayer\" id=\"waScenes\" title=\"Scenes\">\
    <div class=\"iMenu\">\
        <legend></legend>\
        <ul class=\"iArrow\">\
            <li class=\"iRadio\"><img class=\"picto\" src=\""+lost_icons_path+"ambiance.jpg\"/>Ambiances\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_CINEMA);\">Cinema</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ROMANTIQUE);\">Romantique</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ECO);\">Economie d\"energie</label>\
            </li>\
            <li><a href=\"#_Evenements\"><img class=\"picto\" src=\""+lost_icons_path+"wakeup.jpg\"/>Evenements</a></li>\
        </ul>\
        <legend>Rooms</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"javascript:lost_scene_set(EVENT_REVEIL        , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_REVEIL        , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"sunrise.jpg\">Reveil</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_COUCHE        , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_COUCHE        , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Couche</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_CHAUFFAGE_SDB , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_CHAUFFAGE_SDB , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\">Chauffage SdB</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_CHAUFFAGE_CAFE, EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_CHAUFFAGE_CAFE, EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"coffee.jpg\">Chauffage Cafe</li>\
        </ul>\
        <legend>Modes</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"javascript:lost_scene_set(EVENT_LUMIERE_AUTO  , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_LUMIERE_AUTO  , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumiere automatique</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_MUSIQUE_AUTO  , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_MUSIQUE_AUTO  , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"hifi.jpg\">Musique automatique</li>\
        </ul>\
        <legend>Power</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Wifi</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Ethernet</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">POWER 2</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">POWER 3</li>\
        </ul>\
    </div>\
</div>\
");
