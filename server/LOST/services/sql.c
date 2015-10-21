#include <stdio.h>
#include <string.h>

#include <sys/timer.h>
#include <sys/thread.h>
#include <sys/socket.h>

#include "../apps/rooms/rooms.h"
#include "../apps/scenes/safety.h"
#include "../config.h"
#include "http.h"
#include "sql.h"

uint8_t sql_init(void)
{
  /* Start the push thread */
  NutThreadCreate("SqlD" , SqlD , 0, 512);

  return 0;
}

THREAD(SqlD, arg)
{
  arg = arg;
  NutThreadSetPriority(149);

  /* Wait 1 minute */
  NutSleep(60000);
  /* Insert datas with start flag */
  sql_send(1);

  while(1)
  {
    /* Wait 15 minutes */
    NutSleep(900000);
    /* Insert datas without start flag */
    sql_send(0);
  }
}

uint8_t sql_send_once(uint8_t start)
{
  TCPSOCKET *sock = NULL;
  FILE *stream = NULL;
  uint8_t i = 0;
  char* buff = NULL;
  char* out = NULL;
  uint8_t ret = 0;

  /* Connect and send the HTTP header */
  ret = http_request_header_start("212.27.63.116", 80, METHOD_POST, &sock, &stream);
  if(0 != ret) { return (ret+10); }

  /* Send the URL */
  fputs(LOST_INSERT, stream);
  /* Send the host target */
  http_request_header_end("lebomb.free.fr", ((sizeof("roomXX.temp_value=XXX")-1)*ROOM_MAX)+ROOM_MAX-1+sizeof("&safety.ups_temp=XXXXX")-1+sizeof("&safety.rack_temp=XXXXX")-1+sizeof("&start=XXX")-1, stream);
  /* Build the POST request */
  for(i=0; i<ROOM_MAX; i++)
  {
    if(0<i) { fputs("&", stream); }
    fprintf(stream, "room%02d_temp_value=%03d", i, room_temp_value_get(i));
  }
  fprintf(stream, "&safety_ups_temp=%05d", safety_ups_temp_value_get());
  fprintf(stream, "&safety_rack_temp=%05d", safety_rack_temp_value_get());
  fprintf(stream, "&start=%03d", start);
  fflush(stream);

  /* Catch the answer */
  buff = malloc(400);
  if(NULL == buff) { http_request_close(&sock, &stream); return 1; }
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

  /* Close the connection : raw socket and the corresponding stream */
  http_request_close(&sock, &stream);

  /* Build the return status */
  if(out) { return 0; }

  /* The expected keyword was not found, so return error */
  return 2;
}

void sql_send(uint8_t start)
{
  uint8_t i = 0;

  /* Retry if error */
  for(i=0; i<10; i++)
  {
    /* If OK break the retry loop */
    if(0 == sql_send_once(start)) { break; }
    /* Wait before retry */
    NutSleep(10000);
  }
}
