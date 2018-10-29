document.write("\
<div class=\"iLayer\" id=\"waSurveillances\" title=\"Surveillances\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Centrale</legend>\
            <ul>\
                <li id=\"Safety_UPS_Temp_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_UPS_Temp_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_ups_temp_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_UPS_Temp_Ctrl\">UPS Temperature</label></li>\
                <li id=\"Safety_UPS_Power_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_UPS_Power_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_ups_power_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><label for=\"Safety_UPS_Power_Ctrl\">UPS Power</label></li>\
                <li id=\"Safety_RACK_Temp_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_RACK_Temp_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rack_temp_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_RACK_Temp_Ctrl\">RACK Temperature</label></li>\
                <li id=\"Safety_RACK_Alarm_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_RACK_Alarm_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_rack_alarm_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><label for=\"Safety_RACK_Alarm_Ctrl\">RACK Alarm</label></li>\
                <li id=\"Safety_HTTP_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_HTTP_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_http_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><label for=\"Safety_HTTP_Ctrl\">Connexion Internet</label></li>\
                <li id=\"Safety_BtFz_Temp_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_BtFz_Temp_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_btfz_temp_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><label for=\"Safety_BtFz_Temp_Ctrl\">Freezer Temperature</label></li>\
                <li id=\"Safety_BtFz_Net_Ctrl_bg\"><input type=\"checkbox\" id=\"Safety_BtFz_Net_Ctrl\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_safety_btfz_network_status_set();\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><label for=\"Safety_BtFz_Net_Ctrl\">Freezer Network</label></li>\
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
                <li id=\"Safety_UPS_Temp_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_UPS_Temp\">Unknown</span>UPS Temperature</li>\
                <li>UPS Temperature Threshold\
                <SELECT id=\"Safety_UPS_Temp_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_UPS_Temp_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_UPS_Power_bg\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Safety_UPS_Power\">Unknown</span>UPS Power</li>\
                <li id=\"Safety_RACK_Temp_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_RACK_Temp\">Unknown</span>RACK Temperature</li>\
                <li>RACK Temperature Threshold\
                <SELECT id=\"Safety_RACK_Temp_Th\"><script language=\"Javascript\">printSelectOption(\"Safety_RACK_Temp_Th\",99);</script></SELECT>\
                </li>\
                <li id=\"Safety_RACK_Alarm_bg\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Safety_RACK_Alarm\">Unknown</span>RACK Alarm</li>\
                <li id=\"Safety_HTTP_bg\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"Safety_HTTP\">Unknown</span>Connexion Internet</li>\
                <li id=\"Safety_BtFz_Temp_bg\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"Safety_BtFz_Temp\">Unknown</span>Freezer Temperature</li>\
                <li>Freezer Temperature Threshold\
                <SELECT id=\"Safety_BtFz_Temp_Th\"><script language=\"Javascript\">printSelectOptionMinMax(\"Safety_BtFz_Temp_Th\",0,20);</script></SELECT>\
                </li>\
                <li id=\"Safety_BtFz_Net_bg\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\"><span id=\"Safety_BtFz_Net\">Unknown</span>Freezer Network</li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
