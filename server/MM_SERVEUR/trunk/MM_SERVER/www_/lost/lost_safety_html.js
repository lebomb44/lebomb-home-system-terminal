document.write("\
<div class=\"iLayer\" id=\"waSurveillances\" title=\"Surveillances\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Rooms</legend>\
            <ul>\
                <li id=\"Safety_Rooms_Error_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Error_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_error_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"error.jpg\"><label for=\"Safety_Rooms_Error_Ctrl\">Rooms Error</label></li>\
                <li id=\"Safety_Rooms_Temp_Max_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Temp_Max_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_temp_max_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_Rooms_Temp_Max_Ctrl\">Rooms Temperatures Max</label></li>\
                <li id=\"Safety_Rooms_Temp_Min_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Temp_Min_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_temp_min_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_Rooms_Temp_Min_Ctrl\">Rooms Temperatures Min</label></li>\
                <li id=\"Safety_Rooms_Hum_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Hum_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_hum_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\"><label for=\"Safety_Rooms_Hum_Ctrl\">Rooms Humidites</label></li>\
                <li id=\"Safety_Rooms_Smoke_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_Rooms_Smoke_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rooms_smoke_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"gaz.jpg\"><label for=\"Safety_Rooms_Smoke_Ctrl\">Rooms Fumees</label></li>\
            </ul>\
            <legend>Centrale</legend>\
            <ul>\
                <li id=\"Safety_UPS_Temp_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_UPS_Temp_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_ups_temp_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_UPS_Temp_Ctrl\">UPS Temperature</label></li>\
                <li id=\"Safety_UPS_Power_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_UPS_Power_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_ups_power_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><label for=\"Safety_UPS_Power_Ctrl\">UPS Power</label></li>\
                <li id=\"Safety_HTTP_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_HTTP_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_http_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><label for=\"Safety_HTTP_Ctrl\">Connexion Internet</label></li>\
                <li id=\"Safety_GSM_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_GSM_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_gsm_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"sat.jpg\"><label for=\"Safety_GSM_Ctrl\">Reseau GSM</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Info</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_SafetyInfo\"><img class=\"picto\" src=\""+lost_icons_path+"info.jpg\">Info</a></li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waSafetyInfo\" title=\"Surveillances Info\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul>\
                <li id=\"Safety_Rooms_Error_bg\"><img class=\"picto\" src=\""+lost_icons_path+"error.jpg\"><span id=\"Safety_Rooms_Error\">Unknown</span>Rooms Error</li>\
                <li id=\"Safety_Rooms_Temp_Max_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_Rooms_Temp_Max\">Unknown</span>Rooms Temperature Max</li>\
                <li>Rooms Temperature Max Threshold\
                <SELECT id=\"Safety_Rooms_Temp_Max_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_Rooms_Temp_Max_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_Rooms_Temp_Min_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_Rooms_Temp_Min\">Unknown</span>Rooms Temperature Min</li>\
                <li>Rooms Temperature Min Threshold\
                <SELECT id=\"Safety_Rooms_Temp_Min_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_Rooms_Temp_Min_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_Rooms_Hum_bg\"><img class=\"picto\" src=\""+lost_icons_path+"water.jpg\"><span id=\"Safety_Rooms_Hum\">Unknown</span>Rooms Humidity</li>\
                <li id=\"Safety_Rooms_Smoke_bg\"><img class=\"picto\" src=\""+lost_icons_path+"gaz.jpg\"><span id=\"Safety_Rooms_Smoke\">Unknown</span>Rooms Smoke</li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <ul>\
                <li id=\"Safety_UPS_Temp_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_UPS_Temp\">Unknown</span>UPS Temperature</li>\
                <li>UPS Temperature Threshold\
                <SELECT id=\"Safety_UPS_Temp_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_UPS_Temp_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_UPS_Power_bg\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Safety_UPS_Power\">Unknown</span>UPS Power</li>\
                <li id=\"Safety_HTTP_bg\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Safety_HTTP\">Unknown</span>Connexion Internet</li>\
                <li id=\"Safety_GSM_bg\"><img class=\"picto\" src=\""+lost_icons_path+"sat.jpg\"><span id=\"Safety_GSM\">Unknown</span>Reseau GSM</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
