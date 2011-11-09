document.write("\
<div class=\"iLayer\" id=\"waEvenements\" title=\"Evenements\">\
    <div class=\"iPanel\">\
        <fieldset>\
            <legend>Rooms</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+SCENE_REVEIL+"\"><img class=\"picto\" src=\""+lost_icons_path+"sunrise.jpg\">Reveil</a></li>\
                <li><a href=\"#_Event"+SCENE_COUCHE+"\"><img class=\"picto\" src=\""+lost_icons_path+"lit.jpg\">Couche</a></li>\
                <li><a href=\"#_Event"+SCENE_CHAUFFAGE_SDB+"\"><img class=\"picto\" src=\""+lost_icons_path+"temperature.jpg\">Chauffage Salle de bain</a></li>\
                <li><a href=\"#_Event"+SCENE_CHAUFFAGE_CAFE+"\"><img class=\"picto\" src=\""+lost_icons_path+"coffee.jpg\">Chauffage Cafe</a></li>\
            </ul>\
        </fieldset>\
        <fieldset>\
            <legend>Modes</legend>\
            <ul class=\"iArrow\">\
                <li><a href=\"#_Event"+SCENE_LUMIERE_AUTO+"\"><img class=\"picto\" src=\""+lost_icons_path+"lamp.jpg\">Lumiere automatique</a></li>\
                <li><a href=\"#_Event"+SCENE_MUSIQUE_AUTO+"\"><img class=\"picto\" src=\""+lost_icons_path+"hifi.jpg\">Musique automatique</a></li>\
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

printEventInfo(SCENE_REVEIL        , "Reveil"                 );
printEventInfo(SCENE_COUCHE        , "Couche"                 );
printEventInfo(SCENE_CHAUFFAGE_SDB , "Chauffage Salle de Bain");
printEventInfo(SCENE_CHAUFFAGE_CAFE, "Chauffage Cafe"         );
printEventInfo(SCENE_LUMIERE_AUTO  , "Lumiere automatique"    );
printEventInfo(SCENE_MUSIQUE_AUTO  , "Musique automatique"    );
