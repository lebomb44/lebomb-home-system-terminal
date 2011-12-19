# Do not edit! Automatically generated on Tue Dec 13 17:58:51 2011

PROJ =	libnutcrt

top_srcdir = ../../nut
top_blddir = ../../nutbld_21b

VPATH = $(top_srcdir)/crt

SRCS =	 close.c clrerr.c ioctl.c open.c getf.c read.c putf.c write.c write_p.c \
	 fclose.c fcloseall.c fdopen.c feof.c ferror.c fflush.c filelength.c fileno.c \
	 flushall.c fmode.c fopen.c fpurge.c freopen.c fseek.c ftell.c seek.c tell.c fgetc.c \
	 fgets.c fread.c fscanf.c getc.c getchar.c gets.c kbhit.c scanf.c ungetc.c \
	 vfscanf.c fscanf_p.c scanf_p.c vfscanf_p.c fprintf.c fputc.c fputs.c fwrite.c \
	 printf.c putc.c putchar.c puts.c vfprintf.c fprintf_p.c fputs_p.c fwrite_p.c \
	 printf_p.c puts_p.c vfprintf_p.c sprintf.c sscanf.c vsprintf.c vsscanf.c \
	 sprintf_p.c sscanf_p.c vsprintf_p.c vsscanf_p.c gmtime.c localtim.c mktime.c \
	 time.c tzset.c errno.c calloc.c calloc_dbg.c malloc.c malloc_dbg.c realloc.c \
	 realloc_dbg.c strdup.c strdup_dbg.c getenv.c putenv.c setenv.c environ.c

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
