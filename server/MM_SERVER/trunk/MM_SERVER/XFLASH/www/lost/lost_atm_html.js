document.write("\
<div class=\"iLayer\" id=\"waScenes\" title=\"Scenes\">\
    <div class=\"iMenu\">\
        <ul class=\"iArrow\">\
            <li class=\"iRadio\"><img class=\"picto\" src=\""+lost_icons_path+"ambiance.jpg\"/>Ambiances\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_CINEMA);\">Cinema</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ROMANTIQUE);\">Romantique</label>\
                <label><input type=\"radio\" name=\"radioAmbiances\" onClick=\"lost_atm_set(ATM_ECO);\">Economie d\"energie</label>\
            </li>\
            <li><a href=\"#_Evenements\"><img class=\"picto\" src=\""+lost_icons_path+"wakeup.jpg\"/>Evenements</a></li>\
        </ul>\
        <ul>\
            <li><a href=\"javascript:lost_scene_set(EVENT_REVEIL, EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_REVEIL, EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"sunrise.jpg\">Reveil</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_COUCHE, EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_COUCHE, EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Couche</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_MAX+0 , 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_MAX+0 , 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">WIFI</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_MAX+1 , 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_MAX+1 , 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Ethernet</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_MAX+2 , 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_MAX+2 , 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">POWER2</li>\
        </ul>\
    </div>\
</div>\
");
