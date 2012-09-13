# Do not edit! Automatically generated on Thu Sep 13 00:17:26 2012

PROJ =	libnutlua

top_srcdir = ../../nut
top_blddir = ../../nutbld_21b

VPATH = $(top_srcdir)/lua

SRCS =	 lapi.c ldo.c ldump.c ldebug.c lfunc.c lgc.c lmem.c lobject.c lopcodes.c \
	 lstate.c lstring.c ltable.c ltm.c lundump.c lvm.c lzio.c lauxlib.c linit.c \
	 loadlib.c lbaselib.c liolib.c loslib.c ldblib.c lmathlib.c ltablib.c lstrlib.c \
	 lcode.c llex.c lparser.c lrotable.c

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
