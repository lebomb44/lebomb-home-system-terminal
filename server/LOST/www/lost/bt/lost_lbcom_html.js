document.write("\
<div class=\"iLayer\" id=\"waCommunications\" title=\"Communications\">\
    <div class=\"iMenu\">\
        <legend>HomeEasy</legend>\
        <ul>\
            <li id=\"LbCom_HomeEasyTM_Manufacturer_bg\"><img class=\"picto\" src=\""+lost_icons_path+"manufacturer.jpg\"><span id=\"LbCom_HomeEasyTM_Manufacturer\">Unknown</span>Manufacturer</li>\
            <li id=\"LbCom_HomeEasyTM_Group_bg\"><img class=\"picto\" src=\""+lost_icons_path+"group.jpg\"><span id=\"LbCom_HomeEasyTM_Group\">Unknown</span>Group</li>\
            <li id=\"LbCom_HomeEasyTM_Device_bg\"><img class=\"picto\" src=\""+lost_icons_path+"device.jpg\"><span id=\"LbCom_HomeEasyTM_Device\">Unknown</span>Device</li>\
            <li id=\"LbCom_HomeEasyTM_Status_bg\"><img class=\"picto\" src=\""+lost_icons_path+"status.jpg\"><span id=\"LbCom_HomeEasyTM_Status\">Unknown</span>Status</li>\
            <li id=\"LbCom_HomeEasyTM_CodeReset_bg\"><a href=\"javascript:lost_lbcom_homeeasytm_codereset();\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"reset.jpg\"><span id=\"LbCom_HomeEasyTM_CodeReset\"></span>CodeReset</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_HomeEasySend\"><img class=\"picto\" src=\""+lost_icons_path+"send.jpg\"/>Send</a></li>\
        </ul>\
        <legend>GSM</legend>\
        <ul>\
            <li id=\"LbCom_GsmTM_Init_bg\"><a href=\"javascript:lost_lbcom_gsmtc_init_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_gsmtm_init_set(0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"init.jpg\"><span id=\"LbCom_GsmTM_Init\">Unknown</span>Init</li>\
            <li id=\"LbCom_GsmTM_CheckPowerUp_bg\"><a href=\"javascript:lost_lbcom_gsmtc_checkpowerup_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_gsmtm_checkpowerup_set(0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"powerup.jpg\"><span id=\"LbCom_GsmTM_CheckPowerUp\">Unknown</span>CheckPowerUp</li>\
            <li id=\"LbCom_GsmTM_SignalStrength_status_bg\"><a href=\"javascript:lost_lbcom_gsmtc_signalstrength_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_gsmtm_signalstrength_set(0, 0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"status.jpg\"><span id=\"LbCom_GsmTM_SignalStrength_status\">Unknown</span>Signal Strength Status</li>\
            <li id=\"LbCom_GsmTM_SignalStrength_value_bg\"><a href=\"javascript:lost_lbcom_gsmtc_signalstrength_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_gsmtm_signalstrength_set(0, 0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"signalstrength.jpg\"><span id=\"LbCom_GsmTM_SignalStrength_value\">Unknown</span>Signal Strength Value</li>\
        </ul>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_GsmSendSMS\"><img class=\"picto\" src=\""+lost_icons_path+"send.jpg\"/>Send</a></li>\
        </ul>\
        <legend>Freezer</legend>\
        <ul>\
            <li id=\"LbCom_Bourdilot_FreezerTM_Network_bg\"><a href=\"javascript:lost_lbcom_bourdilot_freezertc_network_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_bourdilot_freezertm_network_set(0);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\"><span id=\"LbCom_Bourdilot_FreezerTM_Network\">Unknown</span>Network</li>\
            <li id=\"LbCom_Bourdilot_FreezerTM_Temp_bg\"><a href=\"javascript:lost_lbcom_bourdilot_freezertc_temp_get();\" class=\"iButton iBAction\" style=\"width:60px\">Get</a><a href=\"javascript:lost_lbcom_bourdilot_freezertm_temp_set(444);\" class=\"iButton iBWarn\" style=\"width:60px\">Reset</a><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\"><span id=\"LbCom_Bourdilot_FreezerTM_Temp\">Unknown</span>Temperature</li>\
        </ul>\
        <legend>LbCom</legend>\
        <ul class=\"iArrow\">\
            <li><a href=\"#_LbComSend\"><img class=\"picto\" src=\""+lost_icons_path+"send.jpg\"/>Send</a></li>\
        </ul>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waHomeEasySend\" title=\"Home Easy Send\">\
    <div class=\"iMenu\">\
        <legend>HomeEasy Code</legend>\
        <ul>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"manufacturer.jpg\"><label>Manufacturer</label><input type=\"text\" id=\"HomeEasySend_Manufacturer\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"group.jpg\"><label>Group</label><input type=\"text\" id=\"HomeEasySend_Group\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"device.jpg\"><label>Device</label><input type=\"text\" id=\"HomeEasySend_Device\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"status.jpg\"><input type=\"checkbox\" id=\"HomeEasySend_Status\" class=\"iToggle\" title=\"ON|OFF\"><label for=\"HomeEasySend_Status\">Status</label></li>\
        </ul>\
        <input type=\"button\" class=\"iPush iBCancel\" value=\"Send\" style=\"width:100%\" onClick=\"lost_lbcom_homeeasytc_send();\"/>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waGsmSendSMS\" title=\"Send SMS\">\
    <div class=\"iMenu\">\
        <legend>SMS</legend>\
        <ul>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"phone.jpg\"><label>Phone</label><input type=\"text\" id=\"GsmSendSMS_Phone\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"msg.jpg\"><label>Message</label><input type=\"text\" id=\"GsmSendSMS_Msg\"/></li>\
        </ul>\
        <input type=\"button\" class=\"iPush iBCancel\" value=\"Send\" style=\"width:100%\" onClick=\"lost_lbcom_gsmtc_sendsms();\"/>\
    </div>\
</div>\
");

document.write("\
<div class=\"iLayer\" id=\"waLbComSend\" title=\"LbCom Send\">\
    <div class=\"iMenu\">\
        <legend>LbCom Frame</legend>\
        <ul>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"out.jpg\"><label>Source</label><input type=\"text\" id=\"LbCom_Src\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"in.jpg\"><label>Destination</label><input type=\"text\" id=\"LbCom_Dst\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"cmd.jpg\"><label>Command</label><input type=\"text\" id=\"LbCom_Cmd\"/></li>\
            <li><img class=\"picto\" src=\""+lost_icons_path+"data.jpg\"><label>Data</label><input type=\"text\" id=\"LbCom_Data\"/></li>\
        </ul>\
        <input type=\"button\" class=\"iPush iBCancel\" value=\"Send\" style=\"width:100%\" onClick=\"lost_lbcom_send();\"/>\
    </div>\
</div>\
");

