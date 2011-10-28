#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/timer.h>
#include <sys/thread.h>
#include <sys/confnet.h>
#include <sys/confos.h>
#include <sys/socket.h>
#include <sys/atom.h>
#include <sys/version.h>

#include <arpa/inet.h>
#include <net/if_var.h>
#include <pro/httpd.h>
#include <pro/asp.h>

#include "admin.h"
#include "web.h"

char admin_gsm1[11] = "\0";
char admin_gsm2[11] = "\0";

uint8_t admin_init(void)
{
  strncpy(admin_gsm1, "0689350159", 10);
  strncpy(admin_gsm2, "0689350159", 10);

  // TODO NutRegisterAuth("admin", "root:2maktest");
  NutRegisterCgi("admin.cgi", admin_form);

  return 0;
}

int admin_form(FILE * stream, REQUEST * req)
{
  char* arg_s=NULL;
  uint8_t i=0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBot(stream, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    arg_s = NutHttpGetParameter(req, "OS_Version");
    if(arg_s)
    {
      fprintf(stream, "%s", NutVersionString());
    }
    arg_s = NutHttpGetParameter(req, "Host_name");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%s", confos.hostname); }
      else { strncpy(confos.hostname, arg_s, MAX_HOSTNAME_LEN); }
    }
    arg_s = NutHttpGetParameter(req, "MAC_address");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%02X:%02X:%02X:%02X:%02X:%02X", confnet.cdn_mac[0], confnet.cdn_mac[1], confnet.cdn_mac[2], confnet.cdn_mac[3], confnet.cdn_mac[4], confnet.cdn_mac[5]); }
      else
      {
        if(strnlen(arg_s, 17)==17)
        {
          for(i=0; i<6; i++) { arg_s[(i*3)+2]= '\0'; confnet.cdn_mac[i] = (uint8_t) strtoul(&arg_s[i*3], NULL, 16); }
        }
      }
    }
    arg_s = NutHttpGetParameter(req, "IP_address");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%s", inet_ntoa(confnet.cdn_ip_addr)); }
      else { confnet.cdn_ip_addr = inet_addr(arg_s); }
    }
    arg_s = NutHttpGetParameter(req, "Net_mask");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%s", inet_ntoa(confnet.cdn_ip_mask)); }
      else { confnet.cdn_ip_mask = inet_addr(arg_s); }
    }
    arg_s = NutHttpGetParameter(req, "Gateway");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%s", inet_ntoa(confnet.cdn_gateway)); }
      else
      {
        confnet.cdn_gateway = inet_addr(arg_s);
      }
    }
    arg_s = NutHttpGetParameter(req, "admin_gsm1");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%s", admin_gsm1); }
      else
      {
        strncpy(admin_gsm1, arg_s, 10);
      }
    }
    arg_s = NutHttpGetParameter(req, "admin_gsm2");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%s", admin_gsm2); }
      else
      {
        strncpy(admin_gsm2, arg_s, 10);
      }
    }
    arg_s = NutHttpGetParameter(req, "button");
    if(arg_s)
    {
      if(strncmp(arg_s, "Send", 4) == 0)
      {
        NutSaveConfig(); NutNetSaveConfig();
        fprintf_HTML_Head_Begin(stream); fprintf_P(stream, PSTR("<META http-equiv=Refresh content='3;URL=/admin/index.asp'>"), inet_ntoa(confnet.cdn_ip_addr)); fprintf_HTML_Head_End(stream);
        fprintf_HTML_Body_Begin(stream); fprintf_P(stream, PSTR("You should now reboot to take the modification into account")); fprintf_HTML_Body_End(stream);
      }
    }

    fflush(stream);
  }
    return 0;
}
