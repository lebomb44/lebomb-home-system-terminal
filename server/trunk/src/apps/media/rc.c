#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/confnet.h>
#include <sys/confos.h>

#include <arpa/inet.h>
#include <net/if_var.h>
#include <pro/httpd.h>

#include "../../devices/ir.h"
#include "../../services/http.h"
#include "../../services/web.h"
#include "rc.h"

uint8_t rc_init(void)
{
  NutRegisterCgi("rc.cgi", rc_form);

  return 0;
}

int rc_form(FILE * stream, REQUEST * req)
{
  char* type=0;
  char* addr=0;
  char* cmd =0;
  char* nb  =0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBot(stream, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    type = NutHttpGetParameter(req, "type");
    addr = NutHttpGetParameter(req, "addr");
    cmd  = NutHttpGetParameter(req, "cmd" );
    nb   = NutHttpGetParameter(req, "nb"  );
    if(type && addr && cmd && nb)
    {
      ir_send(strtol(type, NULL, 10), strtoul(addr, NULL, 10), strtoul(cmd, NULL, 10), strtoul(nb, NULL, 10));
    }
    fflush(stream);
  }

  return 0;
}

int rc_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("RC", stream);
  fprintf_XML_elt_int("rc0" , 0 , stream);
  fprintf_XML_elt_trailer("RC", stream);
  return 0;
}
