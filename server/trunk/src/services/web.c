#include <stdio.h>
#include <string.h>

#include <sys/timer.h>
#include <sys/thread.h>
#include <sys/confos.h>
#include <sys/confnet.h>
#include <sys/socket.h>
#include <sys/atom.h>

#include <arpa/inet.h>
#include <net/if_var.h>
#include <net/route.h>

#include <pro/dhcp.h>
#include <pro/httpd.h>

#include "web.h"

int web_ASPCallback (char *pASPFunction, FILE *stream)
{
  time_t tt;
  tm time_now;
  if (strncmp_P(pASPFunction, PSTR("host_name"), sizeof("host_name")) == 0) {
    fprintf_P(stream, PSTR("%s"), confos.hostname);
    return(0);
  }

  else if (strncmp_P(pASPFunction, PSTR("usr_time"), sizeof("usr_time")) == 0) {
    tt = time(NULL);
    localtime_r(&tt, &time_now);
    fprintf_P(stream, PSTR("%d %02d %02d %02d:%02d:%02d %04d"),time_now.tm_wday, time_now.tm_mon+1, time_now.tm_mday, time_now.tm_hour, time_now.tm_min, time_now.tm_sec, time_now.tm_year+1900);
    return(0);
  }

  return (-1);
}

void fprintf_HTML_Head_Begin(FILE* stream)
{
  fputs_P(PSTR("<HTML><HEAD>"), stream);
}

void fprintf_HTML_Head_End(FILE* stream)
{
  fputs_P(PSTR("</HEAD>"), stream);
}

void fprintf_HTML_Title_Begin(FILE* stream)
{
  fputs_P(PSTR("<TITLE>"), stream);
}

void fprintf_HTML_Title_End(FILE* stream)
{
  fputs_P(PSTR("</TITLE>"), stream);
}

void fprintf_HTML_Body_Begin(FILE* stream)
{
  fputs_P(PSTR("<BODY>"), stream);
}

void fprintf_HTML_Body_End(FILE* stream)
{
  fputs_P(PSTR("</BODY></HTML>"), stream);
}

void fprintf_HTML_Redirection(prog_char* url_P, uint8_t delay, FILE* stream)
{
  fputs_P(PSTR("<META http-equiv=Refresh content='"), stream);
  fprintf(stream, "%d", delay);
  fputs_P(PSTR(";URL="), stream);
  fputs_P(url_P, stream);
  fputs_P(PSTR("'>"), stream);
}

void fprintf_HTML_Page(prog_char* head_P, prog_char* title_P, prog_char* body_P, FILE* stream)
{
  fprintf_HTML_Head_Begin(stream);
  fputs_P(head_P, stream);
  fprintf_HTML_Title_Begin(stream);
  fputs_P(title_P, stream);
  fprintf_HTML_Title_End(stream);
  fprintf_HTML_Head_End(stream);
  fprintf_HTML_Body_Begin(stream);
  fputs_P(body_P, stream);
  fprintf_HTML_Body_End(stream);
}

void fprintf_HTML_Page_Redirection(prog_char* url_P, uint8_t delay, prog_char* title_P, prog_char* body_P, FILE* stream)
{
  fprintf_HTML_Head_Begin(stream);
  fprintf_HTML_Redirection(url_P, delay, stream);
  fprintf_HTML_Title_Begin(stream);
  fputs_P(title_P, stream);
  fprintf_HTML_Title_End(stream);
  fprintf_HTML_Head_End(stream);
  fprintf_HTML_Body_Begin(stream);
  fputs_P(body_P, stream);
  fprintf_HTML_Body_End(stream);
}

void fprintf_HTML_Option(unsigned long int nb, unsigned long int comp, FILE *stream)
{
  fprintf_P(stream, PSTR("<option  value='%ld'"), nb);
  if(nb==comp) { fputs_P(PSTR(" selected='selected'"), stream); }
  fprintf_P(stream, PSTR(">%ld</option>"), nb);
}

void fprintf_HTML_Option_and_String(unsigned long int nb, prog_char* str, unsigned long int comp, FILE *stream)
{
  fprintf_P(stream, PSTR("<option  value='%ld'"), nb);
  if(nb==comp) { fputs_P(PSTR(" selected='selected'"), stream); }
  fputs_P(PSTR(">"), stream);
  fputs_P(str, stream);
  fputs_P(PSTR("</option>"), stream);
}

void fprintf_HTML_Option_List(unsigned long int begin, unsigned long int nb, unsigned int comp, FILE *stream)
{
  unsigned long int i=0;
  for(i=begin; i<(begin+nb); i++)
  {
    fprintf_HTML_Option(i, comp, stream);
  }
}

void fprintf_XML_header(FILE *stream)
{
  fprintf(stream, "<?xml version='1.0' encoding='UTF-8'?>");
}

void fprintf_XML_elt_header(char* elt, FILE *stream)
{
  fprintf(stream, "<%s>", elt);
}

void fprintf_XML_elt_trailer(char* elt, FILE *stream)
{
  fprintf(stream, "</%s>", elt);
}

void fprintf_XML_elt_int(char* elt, int data, FILE *stream)
{
  fprintf(stream, "<%s>%d</%s>", elt, data, elt);
}
