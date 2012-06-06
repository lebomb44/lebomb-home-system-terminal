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
#include "devices/gsm.h"
#include "devices/i2c.h"

#include "services/http.h"
#include "services/monitor.h"
#include "services/web.h"

#include "apps/media/freebox.h"
#include "apps/media/remote.h"

#include "apps/rooms/rooms.h"
#include "apps/rooms/ext.h"

#include "apps/scenes/alarm.h"
#include "apps/scenes/atmosphere.h"
#include "apps/scenes/safety.h"
#include "apps/scenes/events.h"
#include "apps/scenes/scenes.h"

#include "config.h"

int xml_get_form(FILE * stream, REQUEST * req)
{
  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "application/xml", -1);

  if (req->req_method == METHOD_GET)
  {
    fprintf_XML_header(stream);
    fprintf_XML_elt_header("Lost", stream);
    mon_xml_get(stream);
    rooms_xml_get(stream);
    events_xml_get(stream);
    alarm_xml_get(stream);
    safety_xml_get(stream);
    ext_xml_get(stream);
    fprintf_XML_elt_trailer("Lost", stream);
  }
  fflush(stream);

  return 0;
}

uint8_t sql_send_once(void)
{
  TCPSOCKET *sock = NULL;
  FILE *stream = NULL;
  uint8_t i = 0;
  char* buff = NULL;
  char* out = NULL;

  /* Connect and send the HTTP header */
  if(http_request_header_start("212.27.63.157", 80, METHOD_POST, &sock, &stream) == 0)
  {
    /* Send the URL */
    fputs(LOST_INSERT, stream);
    /* Send the host target */
    http_request_header_end("lebomb.free.fr", ((sizeof("roomXX.temp_value=XXX")-1)*ROOM_MAX)+ROOM_MAX-1+sizeof("&safety.ups_temp=XXXXX")-1+sizeof("&safety.rack_temp=XXXXX")-1, stream);
    /* Build the POST request */
    for(i=0; i<ROOM_MAX; i++)
    {
      if(i>0) { fputs("&", stream); }
      fprintf(stream, "room%02d_temp_value=%03d", i, room_temp_value_get(i));
    }
    fprintf(stream, "&safety_ups_temp=%05d", safety_ups_temp_value_get());
    fprintf(stream, "&safety_rack_temp=%05d", safety_rack_temp_value_get());
    fflush(stream);
    /* Catch the answer */
    buff = malloc(400);
    if(buff != NULL)
    {
      while(fgets(buff, 400, stream))
      {
        /* Force the end of the string */
        buff[399] = '\0';
        /* On each string search the good answer */
        out = strstr(buff, "SQL Insert OK");
        /* If the good answer is found, we can break the loop */
        if(out) { break; }
      }
      /* The analyze is finished, so free the answer buffer */
      free(buff);
    }
    http_request_close(&sock, &stream);
  }
  /* Build the return status */
  if(out) { return 0; }

  return 1;
}

THREAD(SQLPostD, arg)
{
  uint8_t i = 0;

  arg = arg;
  NutThreadSetPriority(149);

  /* Wait 5 minutes */
  NutSleep(300000);

  while(1)
  {
    /* Retry if error */
    for(i=0; i<10; i++)
    {
      /* If OK break the retry loop */
      if(sql_send_once() == 0) { break; }
      /* Wait before retry */
      NutSleep(10000);
    }
    /* Wait 15 minutes */
    NutSleep(900000);
  }
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
  gsm_init();
  i2c_init();

  http_init();

  mon_init();

  freebox_init();
  remote_init();

  rooms_init();
  ext_init();

  alarm_init();
  atmosphere_init();
  safety_init();
  events_init();
  scenes_init();

  /* Set the time zone to Paris */
  _timezone = -1L * 60L * 60L;
  /* Start the NTP client and connect to ntp.laas.fr */
  NutSNTPStartThread(inet_addr("195.83.132.135"), 60000);

  /* Register the XML global status form */
  NutRegisterCgi("get.xml", xml_get_form);

  /* Start the push thread */
  NutThreadCreate("SQLPostD" , SQLPostD , 0, 512);

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
