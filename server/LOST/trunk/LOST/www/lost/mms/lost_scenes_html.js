document.write("\
<div class=\"iLayer\" id=\"waScenes\" title=\"Scenes\">\
    <div class=\"iMenu\">\
        <legend>Volets</legend>\
        <ul class=\"iArrow\">\
            <li id=\"Scene"+String(EVENT_SHUTTERS_ALL)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_ALL               , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_ALL        , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_ALL)+"_Status\">Unknown</span>Tous</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_UPSTAIRS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_UPSTAIRS     , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_UPSTAIRS   , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_UPSTAIRS)+"_Status\">Unknown</span>Etage</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_DOWNSTAIRS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DOWNSTAIRS , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DOWNSTAIRS , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"canape.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_DOWNSTAIRS)+"_Status\">Unknown</span>Rez de Chaussé</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_MARINE)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_MARINE         , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_MARINE     , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_MARINE)+"_Status\">Unknown</span>Marine</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_MM)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_MM                 , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_MM         , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_MM)+"_Status\">Unknown</span>M&M</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_FRIENDS)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_FRIENDS       , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_FRIENDS    , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_FRIENDS)+"_Status\">Unknown</span>Amis</li>\
            <li id=\"Scene"+String(EVENT_SHUTTERS_DRESSING)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DRESSING     , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SHUTTERS_DRESSING   , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"dressing.jpg\"><span id=\"Scene"+String(EVENT_SHUTTERS_DRESSING)+"_Status\">Unknown</span>Dressing</li>\
        </ul>\
        <legend>Alarme</legend>\
        <ul class=\"iArrow\">\
            <li id=\"Scene"+String(EVENT_ALARM_ALL)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_ALARM_ALL             , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_ALL       , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Scene"+String(EVENT_ALARM_ALL)+"_Status\">Unknown</span>Toutes</li>\
            <li id=\"Scene"+String(EVENT_ALARM_PERIMETER)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Scene"+String(EVENT_ALARM_PERIMETER)+"_Status\">Unknown</span>Périmétrique</li>\
            <li id=\"Scene"+String(EVENT_ALARM_VOLUME)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_ALARM_VOLUME       , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_VOLUME    , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Scene"+String(EVENT_ALARM_VOLUME)+"_Status\">Unknown</span>Volumétrique</li>\
            <li id=\"Scene"+String(EVENT_SIMU)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_SIMU                       , EVENT_STATUS_OFF);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_SIMU            , EVENT_STATUS_ON);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><span id=\"Scene"+String(EVENT_SIMU)+"_Status\">Unknown</span>Simulation Présence</li>\
        </ul>\
        <legend>Power</legend>\
        <ul class=\"iArrow\">\
            <li id=\"Scene"+String(EVENT_POWER_0)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Scene"+String(EVENT_POWER_0)+"_Status\">Unknown</span>Wifi</li>\
            <li id=\"Scene"+String(EVENT_POWER_1)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Scene"+String(EVENT_POWER_1)+"_Status\">Unknown</span>Reseau</li>\
            <li id=\"Scene"+String(EVENT_POWER_2)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Scene"+String(EVENT_POWER_2)+"_Status\">Unknown</span>POWER 2</li>\
            <li id=\"Scene"+String(EVENT_POWER_3)+"_Status_bg\"><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Scene"+String(EVENT_POWER_3)+"_Status\">Unknown</span>POWER 3</li>\
        </ul>\
    </div>\
</div>\
");
