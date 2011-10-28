#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/confnet.h>
#include <sys/confos.h>

#include <arpa/inet.h>
#include <net/if_var.h>
#include <pro/httpd.h>

#include "../../devices/i2c.h"
#include "../../services/http.h"
#include "../../services/web.h"
#include "ext.h"

uint8_t ext_init(void)
{
  NutRegisterCgi("ext.cgi", ext_form);

  return 0;
}

int ext_form(FILE * stream, REQUEST * req)
{
  char* sla=0;
  char* addr=0;
  char* data=0;
  uint8_t value=0;
  uint8_t ret=0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBot(stream, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    sla = NutHttpGetParameter(req, "sla");
    addr = NutHttpGetParameter(req, "addr");
    data = NutHttpGetParameter(req, "data");
    if(sla && addr && data)
    {
      if(data[0] == '?')
      {
        ret=i2c_get(strtoul(sla, NULL, 10), strtoul(addr, NULL, 10), 1, (uint8_t*) &value);
        fprintf(stream, "I2C GET (%ld,%ld)(%d) : %d\n", strtoul(sla, NULL, 10), strtoul(addr, NULL, 10), ret, value);
      }
      else
      {
        value = strtoul(data, NULL, 10);
        ret=i2c_set(strtoul(sla, NULL, 10), strtoul(addr, NULL, 10), 1, (uint8_t*) &value);
        fprintf(stream, "I2C SET (%ld,%ld)(%d) : %d\n", strtoul(sla, NULL, 10), strtoul(addr, NULL, 10), ret, value);
      }
    }
    fflush(stream);
  }

  return 0;
}

int ext_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("Ext", stream);
  fprintf_XML_elt_int("ext0" , 0 , stream);
  fprintf_XML_elt_trailer("Ext", stream);
  return 0;
}
