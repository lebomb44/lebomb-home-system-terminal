# Automatically generated on Thu Sep 13 00:17:26 2012
#
# Do not edit, modify UserConf.mk instead!
#

PLATFORM=ETHERNUT2
HWDEF+=-D$(PLATFORM)
MCU_ATMEGA2560=atmega2560
MCU_ATMEGA2561=atmega2561
MCU_ATMEGA128=atmega128
MCU_ATMEGA103=atmega103
MCU=$(MCU_ATMEGA128)
HWDEF+=-D__HARVARD_ARCH__
NUTMEM_RESERVED=64
CRUROM=crurom


include $(top_blddir)/UserConf.mk
