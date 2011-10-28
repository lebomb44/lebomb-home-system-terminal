# Do not edit! Automatically generated on Wed Oct 07 13:59:08 2009

PROJ =	libnutdev

top_srcdir = ../../nut
top_blddir = ../../nutbld_21b

VPATH = $(top_srcdir)/dev

SRCS =	 ihndlr.c usart.c chat.c term.c netbuf.c can_dev.c nvmem.c reset.c \
	 watchdog.c sbbif0.c spibus_gpio.c spibus0gpio.c twbbif.c null.c spi_mlcd.c \
	 spi_vscodec.c spi_vscodec0.c lan91.c blockdev.c spi_at45d.c spi_at45d0.c \
	 spi_at45d1.c spi_at45d2.c spi_at45d3.c mmcard.c rtc.c ds1307rtc.c spibus.c vs10xx.c \
	 avrtarget.c nvmem_at45d.c at49bv.c sbi0mmc0.c sbi0mmc1.c sbi1mmc0.c sbi1mmc1.c \
	 ppp.c

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
