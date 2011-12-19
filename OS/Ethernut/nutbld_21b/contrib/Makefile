# Do not edit! Automatically generated on Tue Dec 13 17:58:51 2011

PROJ =	libnutcontrib

top_srcdir = ../../nut
top_blddir = ../../nutbld_21b

VPATH = $(top_srcdir)/contrib

SRCS =	

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
