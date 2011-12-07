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
#include "devices/ups.h"
#include "devices/rack.h"
#include "devices/gsm.h"
#include "devices/i2c.h"
#include "devices/xflash.h"

#include "services/http.h"
#include "services/monitor.h"
#include "services/web.h"
#include "services/tftp.h"

#include "apps/media/freebox.h"

#include "apps/rooms/rooms.h"
#include "apps/rooms/ext.h"

#include "apps/scenes/alarm.h"
#include "apps/scenes/atmosphere.h"
#include "apps/scenes/safety.h"
#include "apps/scenes/scenes.h"

int xml_get_form(FILE * stream, REQUEST * req);

int main(void)
{
  uart_init();
  eth_init();
  adc_init();
  ups_init();
  rack_init();
  gsm_init();
  i2c_init();

  http_init();

  mon_init();

  freebox_init();

  rooms_init();
  ext_init();

  alarm_init();
  atmosphere_init();
  safety_init();
  scenes_init();

  /* Set the time zone to Paris */
  _timezone = -1L * 60L * 60L; 
  /* Start the NTP client and connect to ntp.laas.fr */
  NutSNTPStartThread(inet_addr("195.83.132.135"), 60000);

  /* Register the XML global status form */
  NutRegisterCgi("get.xml", xml_get_form);

  // TODO NutTFTPStart();
  printf("Starting LOST\n");
  http_email_send("Starting_LOST");

  NutThreadSetPriority(149);
  NutWatchDogStart(10000, 0);
  while(1) { NutSleep(1000); printf("."); NutWatchDogRestart(); }

  return 0;
}

int xml_get_form(FILE * stream, REQUEST * req)
{
  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBot(stream, "application/xml", -1);

  if (req->req_method == METHOD_GET)
  {
    fprintf_XML_header(stream);
    fprintf_XML_elt_header("Lost", stream);
    rooms_xml_get(stream);
    scenes_xml_get(stream);
    alarm_xml_get(stream);
    safety_xml_get(stream);
    ext_xml_get(stream);
    fprintf_XML_elt_trailer("Lost", stream);
  }
  fflush(stream);

  return 0;
}

ISR(BADISR_vect, ISR_NOBLOCK)
{
// user code here
}
