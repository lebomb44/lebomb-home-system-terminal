document.write("\
<div class=\"iLayer\" id=\"waEvenements\" title=\"Evenements\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Volets</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_ALL+"\"><img class=\"picto\" src=\""+lost_icons_path+"volet.jpg\">Tous</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_C1+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre 1</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_C2+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre 2</a></li>\
                <li><a href=\"#_Event"+EVENT_SHUTTERS_C3+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Chambre 3</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Alarme</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_ALARM_ALL+"\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\">Toutes</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_PERIMETER+"\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\">Périmétrique</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_PERIMETER_CHECK+"\"><img class=\"picto\" src=\""+lost_icons_path+"perimetre.jpg\">Périmétrique Auto</a></li>\
                <li><a href=\"#_Event"+EVENT_ALARM_VOLUME+"\"><img class=\"picto\" src=\""+lost_icons_path+"volume.jpg\">Volumétrique</a></li>\
                <li><a href=\"#_Event"+EVENT_SIMU+"\"><img class=\"picto\" src=\""+lost_icons_path+"man.jpg\">Simulation Presence</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Power</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+EVENT_POWER_0+"\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Wifi</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_1+"\"><img class=\"picto\" src=\""+lost_icons_path+"net.jpg\">Ethernet</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_2+"\"><img class=\"picto\" src=\""+lost_icons_path+"elec.jpg\">Power 2</a></li>\
                <li><a href=\"#_Event"+EVENT_POWER_3+"\"><img class=\"picto\" src=\""+lost_icons_path+"radiateur.jpg\">Chauffage</a></li>\
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
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_StStart\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_date_status_update("+String(event)+");\"><label for=\"Event"+String(event)+"_StStart\">Depart : Heure / Minute</label></li>\
                <li>\
                <SELECT id=\"Event"+String(event)+"_HStart\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_HStart\",24);</script></SELECT>\
                <SELECT id=\"Event"+String(event)+"_MStart\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_MStart\",60);</script></SELECT>\
                </li>\
            </ul>\
            <ul>\
                <li><input type=\"checkbox\" id=\"Event"+String(event)+"_StEnd\" class=\"iToggle\" title=\"ON|OFF\" onClick=\"lost_ev_date_status_update("+String(event)+");\"><label for=\"Event"+String(event)+"_StEnd\">Fin : Heure / Minute</label></li>\
                <li>\
                <SELECT id=\"Event"+String(event)+"_HEnd\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_HEnd\",24);</script></SELECT>\
                <SELECT id=\"Event"+String(event)+"_MEnd\"><script language=\"Javascript\">printSelectOption(\"Event"+String(event)+"_MEnd\",60);</script></SELECT>\
                </li>\
            </ul>\
        </fieldset>\
    </div>\
</div>\
");
}

printEventInfo(EVENT_SHUTTERS_ALL         , "Tous"               );
printEventInfo(EVENT_SHUTTERS_UPSTAIRS    , "Etage"              );
printEventInfo(EVENT_SHUTTERS_DOWNSTAIRS  , "Rez de Chaussé"     );
printEventInfo(EVENT_SHUTTERS_C1          , "Chambre 1"          );
printEventInfo(EVENT_SHUTTERS_C2          , "Chambre 2"          );
printEventInfo(EVENT_SHUTTERS_C3          , "Chambre 3"          );
printEventInfo(EVENT_SHUTTERS_C4          , "Chambre 4"          );
printEventInfo(EVENT_ALARM_ALL            , "Toutes"             );
printEventInfo(EVENT_ALARM_PERIMETER_CHECK, "Perimetrique"       );
printEventInfo(EVENT_ALARM_PERIMETER      , "Perimetrique Auto"  );
printEventInfo(EVENT_ALARM_VOLUME         , "Volumetrique"       );
printEventInfo(EVENT_SIMU                 , "Simulation Presence");
printEventInfo(EVENT_POWER_0              , "Wifi"               );
printEventInfo(EVENT_POWER_1              , "Ethernet"           );
printEventInfo(EVENT_POWER_2              , "Power 2"            );
printEventInfo(EVENT_POWER_3              , "Chauffage"          );
