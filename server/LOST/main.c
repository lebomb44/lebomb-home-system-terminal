#define __PROG_TYPES_COMPAT__ 1
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dev/watchdog.h>
#include <dev/gpio.h>
#include <sys/thread.h>
#include <sys/timer.h>
#include <arpa/inet.h>
#include <pro/sntp.h>
#include <time.h>

#include "devices/uart.h"
#include "devices/eth.h"
#include "devices/adc.h"
#include "devices/buzzer.h"
#include "devices/power.h"
#include "devices/ups.h"
#include "devices/rack.h"
#include "devices/volume.h"
#include "devices/lbcomif.h"

#include "services/http.h"
#include "services/monitor.h"
#include "services/sql.h"
#include "services/web.h"

#include "apps/scenes/alarm.h"
#include "apps/scenes/atmosphere.h"
#include "apps/scenes/safety.h"
#include "apps/scenes/events.h"
#include "apps/scenes/scenes.h"
#include "apps/scenes/homeeasy.h"
#include "apps/scenes/lbcom.h"

#include "config.h"

int xml_get_form(FILE * stream, REQUEST * req)
{
  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "application/xml", -1);

  if(METHOD_GET == req->req_method)
  {
    fprintf_XML_header(stream);
    fprintf_XML_elt_header("Lost", stream);
    mon_xml_get(stream);
    events_xml_get(stream);
    alarm_xml_get(stream);
    safety_xml_get(stream);
    fprintf_XML_elt_trailer("Lost", stream);
  }
  fflush(stream);

  return 0;
}

int main(void)
{
  uart_init();
  eth_init();
  adc_init();
  buzzer_init();
  power_init();
  ups_init();
  rack_init();
  volume_init();
  lbcomif_init();

  http_init();
  mon_init();
  sql_init();

  alarm_init();
  atmosphere_init();
  safety_init();
  events_init();
  scenes_init();
  homeeasy_init();
  lbcom_init();

  /* Set the time zone to Paris */
  _timezone = -1L * 60L * 60L;
  /* Start the NTP client and connect to ntp.laas.fr */
  NutSNTPStartThread(inet_addr("195.83.132.135"), 60000);

  /* Register the XML global status form */
  NutRegisterCgi("get.xml", xml_get_form);

  printf("Starting LOST\n");
  http_email_send("Starting_LOST");

  NutThreadSetPriority(148);
  NutWatchDogStart(60000, 0);
  while(1) { NutSleep(1000); printf("."); NutWatchDogRestart(); }

  return 0;
}

ISR(BADISR_vect, ISR_NOBLOCK)
{
// user code here
}

