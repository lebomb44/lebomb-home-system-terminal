document.write("\
<div class=\"iLayer\" id=\"waScenes\" title=\"Scenes\">\
    <div class=\"iMenu\">\
        <legend>Power</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_0, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Wifi</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_1, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Ethernet</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_2, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">POWER 2</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_POWER_3, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">POWER 3</li>\
        </ul>\
        <legend>Alarm</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER_CHECK, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER_CHECK, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm check</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_PERIMETER, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm perimeter</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_ALARM_VOLUME, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_VOLUME, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm volume</li>\
            <li><a href=\"javascript:lost_scene_set(EVENT_ALARM_ALL, 0);\" class=\"iButton iBAction\" style=\"width:60px\">OFF</a><a href=\"javascript:lost_scene_set(EVENT_ALARM_ALL, 1);\" class=\"iButton iBWarn\" style=\"width:60px\">ON</a><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm all</li>\
        </ul>\
    </div>\
</div>\
");
