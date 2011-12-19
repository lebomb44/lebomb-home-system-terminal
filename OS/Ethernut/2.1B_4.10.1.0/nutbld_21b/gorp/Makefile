# Do not edit! Automatically generated on Tue Dec 13 17:58:51 2011

PROJ =	libnutgorp

top_srcdir = ../../nut
top_blddir = ../../nutbld_21b

VPATH = $(top_srcdir)/gorp

SRCS =	 buffer/perci.c edit/edline.c edit/history.c edit/vt100.c \
	 codec/base64_decode.c codec/base64_encode.c hashes/md5.c list/lili.c list/lpushpop.c \
	 list/lstrcmp.c list/lstrcopy.c list/lutil.c crypt/xtea.c

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
