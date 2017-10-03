var url_lbcom="cgi/lbcom.cgi?";

function lost_lbcom_xml_get(xml)
{
  lost_innerHTML_update(xml, "LbCom_HomeEasyTM", "Manufacturer");
  lost_innerHTML_update(xml, "LbCom_HomeEasyTM", "Group");
  lost_innerHTML_update(xml, "LbCom_HomeEasyTM", "Device");
  lost_innerHTML_update(xml, "LbCom_HomeEasyTM", "Status");
  lost_innerHTML_update(xml, "LbCom_GsmTM", "Init");
  lost_innerHTML_update(xml, "LbCom_GsmTM", "CheckPowerUp");
  lost_innerHTML_update(xml, "LbCom_GsmTM", "SignalStrength_status");
  lost_innerHTML_update(xml, "LbCom_GsmTM", "SignalStrength_value");
  lost_innerHTML_update(xml, "LbCom_Bourdilot_FreezerTM", "Network");
  lost_innerHTML_update(xml, "LbCom_Bourdilot_FreezerTM", "Temp");
}
