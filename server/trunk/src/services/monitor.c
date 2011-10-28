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
  NutRegisterCgi("mon_showThreads.cgi", mon_showThreads);
  NutRegisterCgi("mon_showSockets.cgi", mon_showSockets);
  NutRegisterCgi("mon_showPorts.cgi", mon_showPorts);

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


prog_char tbot_P[] = "</TABLE></BODY></HTML>";
/*
 * Thread list CGI.
 */
int mon_showThreads(FILE * stream, REQUEST * req)
{
    NUTTHREADINFO *tdp = nutThreadList;
    static prog_char head_P[] = "<HTML><HEAD><TITLE>Nut/OS Threads</TITLE>" "</HEAD><BODY><h1>Nut/OS Threads</h1>\r\n";
    static prog_char ttop_P[] = "<TABLE BORDER><TR><TH>Handle</TH>"
        "<TH>Name</TH><TH>Priority</TH>"
        "<TH>Status</TH><TH>Event<BR>Queue</TH>" "<TH>Timer</TH><TH>Stack-<BR>pointer</TH>" "<TH>Free<BR>Stack</TH></TR>\r\n";
    static prog_char tfmt_P[] = "<TR><TD>%04X</TD><TD>%s</TD><TD>%u</TD>"
        "<TD>%s</TD><TD>%04X</TD><TD>%04X</TD>" "<TD>%04X</TD><TD>%u</TD><TD>%s</TD></TR>\r\n";

    NutHttpSendHeaderTop(stream, req, 200, "Ok");
    NutHttpSendHeaderBot(stream, "text/html", -1);

    fputs_P(head_P, stream);
	fprintf_P(stream, PSTR("Available Heap : %d bytes\r\n"), (int) NutHeapAvailable());
    fputs_P(ttop_P, stream);
    while (tdp) {
        fprintf_P(stream, tfmt_P, (u_int)tdp, tdp->td_name, tdp->td_priority,
                  states[tdp->td_state], (u_int)tdp->td_queue, (u_int)tdp->td_timer,
                  (u_int)tdp->td_sp,
                  (u_int) tdp->td_sp - (u_int) tdp->td_memory, *((u_long *) tdp->td_memory) != DEADBEEF ? "Corr" : "OK");
        tdp = tdp->td_next;
    }
    fputs_P(tbot_P, stream);
    fflush(stream);

    return 0;
}



/*
 * Socket list CGI.
 */
int mon_showSockets(FILE * stream, REQUEST * req)
{
    extern TCPSOCKET *tcpSocketList;
    TCPSOCKET *ts;
    static prog_char head_P[] = "<HTML><HEAD><TITLE>Show Threads</TITLE>"
        "</HEAD><BODY><TABLE BORDER><TR>" "<TH>Handle</TH><TH>Type</TH><TH>Local</TH>" "<TH>Remote</TH><TH>Status</TH></TR>\r\n";
    static prog_char fmt1_P[] = "<TR><TD>%04X</TD><TD>TCP</TD><TD>%s:%u</TD>";
    static prog_char fmt2_P[] = "<TD>%s:%u</TD><TD>";
    static prog_char estb_P[] = "<FONT COLOR=#CC0000>ESTABL</FONT>";

    NutHttpSendHeaderTop(stream, req, 200, "Ok");
    NutHttpSendHeaderBot(stream, "text/html", -1);

    fputs_P(head_P, stream);

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
    fputs_P(tbot_P, stream);
    fflush(stream);

    return 0;
}


void DoCheckboxes(FILE * stream, char * name, u_char val)
{
    u_char i;
    static prog_char ttop_P[] = "<tr><td>%s</td>";
    static prog_char tfmt_P[] = "<td><input type=\"checkbox\"" " name=\"%s\" value=\"%u\" ";
    static prog_char tchk_P[] = " checked=\"checked\"";

    fprintf_P(stream, ttop_P, name);
    for (i = 8; i-- > 0;) {
        fprintf_P(stream, tfmt_P, name, i);
        if (val & _BV(i))
            fputs_P(tchk_P, stream);
        fputs_P(PSTR("></td>\r\n"), stream);
    }
    fputs_P(PSTR("</tr>\r\n"), stream);
}


/*
 * Socket list CGI.
 */
int mon_showPorts(FILE * stream, REQUEST * req)
{
    static prog_char ttop_P[] = "<HTML><HEAD><TITLE>Show Ports</TITLE>"
        "</HEAD><BODY>"
        "<form action=\"cgi-bin/setports.cgi\" "
        "enctype=\"text/plain\"> <TABLE BORDER>"
        "<tr><td>Bit</td><td>7</td><td>6</td>" "<td>5</td><td>4</td><td>3</td><td>2</td>" "<td>1</td><td>0</td></tr>\r\n";
#if defined (__AVR__)
    static prog_char trow_P[] = "<tr></tr>";
#endif

    NutHttpSendHeaderTop(stream, req, 200, "Ok");
    NutHttpSendHeaderBot(stream, "text/html", -1);

    fputs_P(ttop_P, stream);

#if defined (__AVR__)
    DoCheckboxes(stream, "DDRA", inb(DDRA));
    DoCheckboxes(stream, "PINA", inb(PINA));
    DoCheckboxes(stream, "PORTA", inb(PORTA));

    fputs_P(trow_P, stream);
    DoCheckboxes(stream, "DDRB", inb(DDRB));
    DoCheckboxes(stream, "PINB", inb(PINB));
    DoCheckboxes(stream, "PORTB", inb(PORTB));

    fputs_P(trow_P, stream);
    DoCheckboxes(stream, "PORTC", inb(PORTC));

    fputs_P(trow_P, stream);
    DoCheckboxes(stream, "DDRD", inb(DDRD));
    DoCheckboxes(stream, "PIND", inb(PIND));
    DoCheckboxes(stream, "PORTD", inb(PORTD));

    fputs_P(trow_P, stream);
    DoCheckboxes(stream, "DDRE", inb(DDRE));
    DoCheckboxes(stream, "PINE", inb(PINE));
    DoCheckboxes(stream, "PORTE", inb(PORTE));

    fputs_P(trow_P, stream);
    DoCheckboxes(stream, "PINF", inb(PINF));
#endif

    fputs_P(tbot_P, stream);
    fflush(stream);

    return 0;
}

