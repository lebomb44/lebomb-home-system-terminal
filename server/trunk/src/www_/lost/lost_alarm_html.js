document.write("\
<div class=\"iLayer\" id=\"waAlarmes\" title=\"Alarmes\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Alarmes</legend>\
            <ul class=\"iArrow\">\
                <li id=\"Alarm_Perimeter_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Perimeter_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_perimeter_set();\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><label for=\"Alarm_Perimeter_Ctrl\">Perimetrique</label></li>\
                <li id=\"Alarm_Volume_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Volume_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_volume_set();\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><label for=\"Alarm_Volume_Ctrl\">Volumetrique</label></li>\
                <li id=\"Alarm_Simulation_Ctrl_bg\"><input type=\"checkbox\" id=\"Alarm_Simulation_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_alarm_simulation_set();\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><label for=\"Alarm_Simulation_Ctrl\">Simulation de presence</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_AlarmesInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waAlarmesInfo\" title=\"Alarmes Info\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul>\
                <li id=\"Alarm_Perimeter_bg\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\"><span id=\"Alarm_Perimeter\">Unknown</span>Perimetrique</li>\
                <li id=\"Alarm_Volume_bg\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\"><span id=\"Alarm_Volume\">Unknown</span>Volumetrique</li>\
                <li id=\"Alarm_Simulation_bg\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\"><span id=\"Alarm_Simulation\">Unknown</span>Simulation de presence</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
