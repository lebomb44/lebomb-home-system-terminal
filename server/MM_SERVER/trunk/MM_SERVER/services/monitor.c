#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/atom.h>
#include <sys/thread.h>
#include <sys/timer.h>
#include <sys/socket.h>
#include <sys/heap.h>

#include <arpa/inet.h>
#include <pro/httpd.h>

#include "monitor.h"

uint8_t mon_init(void)
{
  NutRegisterCgi("monitor.cgi", mon_show);

  NutThreadCreate("Monitord", Mond, 0, 128);

  return 0;
}

THREAD(Mond, arg)
{
  NutThreadSetPriority(250);
  while(1)
  {
    NutSleep(5000);
  }
}

static char *states[] = { "TRM",
    "<FONT COLOR=#CC0000>RUN</FONT>",
    "<FONT COLOR=#339966>RDY</FONT>",
    "SLP"
};


prog_char tbot1_P[] = "</TABLE>";
prog_char tbot2_P[] = "</TABLE></BODY></HTML>";
/*
 * Thread list CGI.
 */
int mon_show(FILE * stream, REQUEST * req)
{
    extern TCPSOCKET *tcpSocketList;
    TCPSOCKET *ts;
    NUTTHREADINFO *tdp = nutThreadList;
    static prog_char head1_P[] = "<HTML><HEAD><TITLE>Nut/OS</TITLE>" "</HEAD><BODY><h1>Nut/OS Threads</h1>\r\n";
    static prog_char ttop_P[] = "<TABLE BORDER><TR><TH>Handle</TH>"
        "<TH>Name</TH><TH>Priority</TH>"
        "<TH>Status</TH><TH>Event<BR>Queue</TH>" "<TH>Timer</TH><TH>Stack-<BR>pointer</TH>" "<TH>Free<BR>Stack</TH></TR>\r\n";
    static prog_char tfmt_P[] = "<TR><TD>%04X</TD><TD>%s</TD><TD>%u</TD>"
        "<TD>%s</TD><TD>%04X</TD><TD>%04X</TD>" "<TD>%04X</TD><TD>%u</TD><TD>%s</TD></TR>\r\n";

    static prog_char head2_P[] = "<h1>Nut/OS Sockets</h1><TABLE BORDER><TR>" "<TH>Handle</TH><TH>Type</TH><TH>Local</TH>" "<TH>Remote</TH><TH>Status</TH></TR>\r\n";

    static prog_char fmt1_P[] = "<TR><TD>%04X</TD><TD>TCP</TD><TD>%s:%u</TD>";
    static prog_char fmt2_P[] = "<TD>%s:%u</TD><TD>";
    static prog_char estb_P[] = "<FONT COLOR=#CC0000>ESTABL</FONT>";

    NutHttpSendHeaderTop(stream, req, 200, "Ok");
    NutHttpSendHeaderBot(stream, "text/html", -1);

    fputs_P(head1_P, stream);
	fprintf_P(stream, PSTR("Available Heap : %d bytes\r\n"), (int) NutHeapAvailable());
    fputs_P(ttop_P, stream);
    while (tdp) {
        fprintf_P(stream, tfmt_P, (u_int)tdp, tdp->td_name, tdp->td_priority,
                  states[tdp->td_state], (u_int)tdp->td_queue, (u_int)tdp->td_timer,
                  (u_int)tdp->td_sp,
                  (u_int) tdp->td_sp - (u_int) tdp->td_memory, *((u_long *) tdp->td_memory) != DEADBEEF ? "Corr" : "OK");
        tdp = tdp->td_next;
    }
    fputs_P(tbot1_P, stream);

    fputs_P(head2_P, stream);
    NutEnterCritical();
    for (ts = tcpSocketList; ts; ts = ts->so_next) {
        fprintf_P(stream, fmt1_P, (u_int)ts, inet_ntoa(ts->so_local_addr), ntohs(ts->so_local_port));
        fprintf_P(stream, fmt2_P, inet_ntoa(ts->so_remote_addr), ntohs(ts->so_remote_port));
        switch (ts->so_state) {
        case TCPS_LISTEN:
            fputs_P(PSTR("LISTEN"), stream);
            break;
        case TCPS_SYN_SENT:
            fputs_P(PSTR("SYNSENT"), stream);
            break;
        case TCPS_SYN_RECEIVED:
            fputs_P(PSTR("SYNRCVD"), stream);
            break;
        case TCPS_ESTABLISHED:
            fputs_P(estb_P, stream);
            break;
        case TCPS_FIN_WAIT_1:
            fputs_P(PSTR("FINWAIT1"), stream);
            break;
        case TCPS_FIN_WAIT_2:
            fputs_P(PSTR("FINWAIT2"), stream);
            break;
        case TCPS_CLOSE_WAIT:
            fputs_P(PSTR("CLOSEWAIT"), stream);
            break;
        case TCPS_CLOSING:
            fputs_P(PSTR("CLOSING"), stream);
            break;
        case TCPS_LAST_ACK:
            fputs_P(PSTR("LASTACK"), stream);
            break;
        case TCPS_TIME_WAIT:
            fputs_P(PSTR("TIMEWAIT"), stream);
            break;
        case TCPS_CLOSED:
            fputs_P(PSTR("CLOSED"), stream);
            break;
        default:
            fputs_P(PSTR("?UNK?"), stream);
            break;
        }
        fputs_P(PSTR("</TD></TR>\r\n"), stream);
    }
    NutExitCritical();
    fputs_P(tbot2_P, stream);
    fflush(stream);

    return 0;
}
