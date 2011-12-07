var ATM_UNKNOWN    = 0;
var ATM_CINEMA     = 1;
var ATM_ROMANTIQUE = 2;
var ATM_ECO        = 3;
var url_atm="cgi/atm.cgi?atm=";
var url_scene="cgi/scenes.cgi?scene=";

function lost_atm_set(atm)
{
  lost_set(url_atm+String(atm));
}

function lost_scene_set(scene, status)
{
  lost_set(url_scene+String(scene)+"&status="+String(status));
}
