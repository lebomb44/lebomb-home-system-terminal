document.write("\
<div class=\"iLayer\" id=\"waEvenements\" title=\"Evenements\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Power</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_POWER_0+"\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Wifi</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_1+"\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Ethernet</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_2+"\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Power 2</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_3+"\"><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Alarm</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_ALARM_PERIMETER_CHECK+"\"><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm check</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_PERIMETER+"\"><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm perimeter</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_VOLUME+"\"><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm volume</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_ALL+"\"><img class=\"picto\" src=\""+lost_icons_path+"alarm.jpg\">Alarm all</a></li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");

function printEventInfo(event, name)
{
document.write("\
<div class=\"iLayer\" id=\"waEvent"+event+"\" title=\""+name+"\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_St\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_status_set("+String(event)+");\"><label for=\"Event"+String(event)+"_St\">Status</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Recurrences</legend>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec1\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 1, Number(checked));\"><label for=\"Event"+String(event)+"_rec1\">Lundi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec2\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 2, Number(checked));\"><label for=\"Event"+String(event)+"_rec2\">Mardi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec3\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 3, Number(checked));\"><label for=\"Event"+String(event)+"_rec3\">Mercredi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec4\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 4, Number(checked));\"><label for=\"Event"+String(event)+"_rec4\">Jeudi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec5\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 5, Number(checked));\"><label for=\"Event"+String(event)+"_rec5\">Vendredi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec6\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 6, Number(checked));\"><label for=\"Event"+String(event)+"_rec6\">Samedi</label></li>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_rec0\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_rec_set("+String(event)+", 0, Number(checked));\"><label for=\"Event"+String(event)+"_rec0\">Dimanche</label></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Horloges</legend>\
            <ul>\
                <li>Depart : Heure / Minute\
                <SELECT id=\"Event"+String(event)+"_HStart\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_HStart\",24);</script></SELECT>\
                <SELECT id=\"Event"+String(event)+"_MStart\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_MStart\",60);</script></SELECT>\
                </li>\
            </ul>\
            <ul>\
                <li>Fin : Heure / Minute\
                <SELECT id=\"Event"+String(event)+"_HEnd\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_HEnd\",24);</script></SELECT>\
                <SELECT id=\"Event"+String(event)+"_MEnd\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_MEnd\",60);</script></SELECT>\
                </li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
}

printEventInfo(EVENT_POWER_0       , "Wifi"                   );
printEventInfo(EVENT_POWER_1       , "Ethernet"               );
printEventInfo(EVENT_POWER_2       , "Power 2"                );
printEventInfo(EVENT_POWER_3       , "Chauffage"              );
printEventInfo(EVENT_ALARM_PERIMETER_CHECK, "Alarm check"     );
printEventInfo(EVENT_ALARM_PERIMETER      , "Alarm perimeter" );
printEventInfo(EVENT_ALARM_VOLUME         , "Alarm volume"    );
printEventInfo(EVENT_ALARM_ALL            , "Alarm all"       );

