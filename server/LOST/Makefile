PROJ = main
WEBDIR = flash/$(LOST_CONFIG)
WEBFILE= urom.c

include $(DEVBASE)/OS/Ethernut/$(OS_VERSION)/nutapp_21b/Makedefs
CFLAGS += -DLOST_CONFIG_$(LOST_CONFIG)

SRCS =  $(PROJ).c \
devices/eth.c devices/uart.c devices/adc.c devices/buzzer.c devices/power.c devices/ups.c devices/rack.c devices/volume.c \
devices/lbcomif.c \
services/http.c services/sql.c services/web.c services/monitor.c \
apps/scenes/alarm.c apps/scenes/safety.c apps/scenes/atmosphere.c \
apps/scenes/events.c apps/scenes/events_proc.c apps/scenes/scenes.c \
apps/lbcom/lbcom.c \
apps/lbcom/lbcom_homeeasyTC.c apps/lbcom/lbcom_homeeasyTM.c \
apps/lbcom/lbcom_gsmTC.c apps/lbcom/lbcom_gsmTM.c \
apps/lbcom/lbcom_bourdilot_freezerTC.c apps/lbcom/lbcom_bourdilot_freezerTM.c \
$(WEBFILE)

#apps/media/freebox.c apps/media/remote.c \
#devices/xflash.c services/tftp.c devices/gsm.c \

LIBS =  $(LIBDIR)/nutinit.o -lnutpro -lnutos -lnutarch -lnutdev -lnutgorp -lnutnet -lnutfs -lnutcrt

#LIBS =  $(LIBDIR)/nutinit.o -lnutnet -lnutpro -lnutfs -lnutos -lnutarch -lnutdev -lnutgorp -lnutcrt
#LIBS =  $(LIBDIR)/nutinit.o -lnutcrt -lnutarch -lnutdev -lnutos -lnutdev -lnutarch 
#LIBS =  $(LIBDIR)/nutinit.o -lnutpro -lnutos -lnutarch -lnutdev -lnutarch -lnutnet -lnutfs -lnutcrt

OBJS =  $(SRCS:.c=.o)
TARG =  $(PROJ).hex
LTARG =  $(PROJ).lss

all: $(OBJS) $(TARG) $(ITARG) $(DTARG) $(LTARG) 

dep:
	$(CC) -I$(top_srcdir)/include -M $(PROJ).c

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	avr-objdump -h -S $< > $@

$(WEBFILE): $(WEBDIR)/index.asp
	$(CRUROM) -r -o$(WEBFILE) $(WEBDIR)


include $(DEVBASE)/OS/Ethernut/$(OS_VERSION)/nutapp_21b/Makerules

studio: $(PROJ).obj

clean:
	-rm -f $(OBJS)
	-rm -f $(TARG) $(ITARG) $(DTARG)
	-rm -f $(PROJ).obj
	-rm -f $(PROJ).sym
	-rm -f $(PROJ).map
	-rm -f $(PROJ).lss
	-rm -f $(SRCS:.c=.lst)
	-rm -f $(SRCS:.c=.bak)
	-rm -f $(SRCS:.c=.i)
	-rm -f $(WEBFILE)

