# Do not edit! Automatically generated on Wed Oct 07 13:59:08 2009

PROJ =	libnutpro

top_srcdir = ../../nut
top_blddir = ../../nutbld_21b

VPATH = $(top_srcdir)/pro

SRCS =	 discover.c dhcpc.c resolv.c ftpd.c auth.c cgi.c dencode.c discover.c \
	 httpd.c httpd_p.c httpopt.c asp.c ssi.c rfctime.c snmp.c snmp_agent.c \
	 snmp_api.c snmp_auth.c snmp_config.c snmp_mib.c asn1.c sntp.c syslog.c wins.c \
	 uxmlparse.c uxmlstream.c uxmltree.c

OBJS = $(SRCS:.c=.o)
include $(top_blddir)/NutConf.mk

include $(top_srcdir)/Makedefs.avr-gcc

INCFIRST=$(INCPRE)$(top_blddir)/include 

all: $(PROJ).a $(OBJS)

install: $(PROJ).a
	$(CP) $(PROJ).a ../../nutbld_21b/lib/$(PROJ).a

include $(top_srcdir)/Makerules.avr-gcc

.PHONY: clean
clean: cleancc cleanedit
	-rm -f $(PROJ).a
