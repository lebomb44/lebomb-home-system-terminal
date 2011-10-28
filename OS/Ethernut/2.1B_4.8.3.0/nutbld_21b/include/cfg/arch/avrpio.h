#ifndef _INCLUDE_CFG_ARCH_AVRPIO_H_
#define _INCLUDE_CFG_ARCH_AVRPIO_H_

/*
 * Do not edit! Automatically generated on Wed Oct 07 13:59:08 2009
 */

#ifndef LANC111_SIGNAL_IRQ
#define LANC111_SIGNAL_IRQ INT5
#endif

#ifndef RTL_BASE_ADDR
#define RTL_BASE_ADDR 0x8300
#endif

#ifndef RTL_SIGNAL_IRQ
#define RTL_SIGNAL_IRQ INT5
#endif

#ifndef LCD_ROWS
#define LCD_ROWS 2
#endif

#ifndef LCD_COLS
#define LCD_COLS 16
#endif

#ifndef SPI0_CS0_PIO_ID
#define SPI0_CS0_PIO_ID AVRPORTB
#endif

#ifndef SPI0_CS0_PIO_BIT
#define SPI0_CS0_PIO_BIT 4
#endif

#ifndef SPI0_CS1_PIO_BIT
#define SPI0_CS1_PIO_BIT 6
#endif

#ifndef SPI0_CS2_PIO_ID
#define SPI0_CS2_PIO_ID AVRPORTD
#endif

#ifndef SPI0_CS2_PIO_BIT
#define SPI0_CS2_PIO_BIT 7
#endif

#ifndef SPPI0_CS0_AVRPORT
#define SPPI0_CS0_AVRPORT AVRPORTB
#endif

#ifndef SPPI0_CS0_BIT
#define SPPI0_CS0_BIT 4
#endif

#ifndef SPPI0_CS1_AVRPORT
#define SPPI0_CS1_AVRPORT AVRPORTB
#endif

#ifndef SPPI0_CS1_BIT
#define SPPI0_CS1_BIT 0
#endif

#ifndef SPPI0_CS2_AVRPORT
#define SPPI0_CS2_AVRPORT AVRPORTD
#endif

#ifndef SPPI0_CS2_BIT
#define SPPI0_CS2_BIT 7
#endif

#ifndef SPPI0_RST1_AVRPORT
#define SPPI0_RST1_AVRPORT AVRPORTB
#endif

#ifndef SPPI0_RST1_BIT
#define SPPI0_RST1_BIT 6
#endif

#ifndef SPPI0_RST2_AVRPORT
#define SPPI0_RST2_AVRPORT AVRPORTD
#endif

#ifndef SPPI0_RST2_BIT
#define SPPI0_RST2_BIT 4
#endif

#ifndef VSCODEC0_XRESET_PORT
#define VSCODEC0_XRESET_PORT AVRPORTB
#endif

#ifndef VSCODEC0_XRESET_BIT
#define VSCODEC0_XRESET_BIT 6
#endif

#ifndef VSCODEC0_SIGNAL_IRQ
#define VSCODEC0_SIGNAL_IRQ NUTGPIO_EXTINT6
#endif

#ifndef VSCODEC0_DREQ_PORT
#define VSCODEC0_DREQ_PORT AVRPORTE
#endif

#ifndef VSCODEC0_DREQ_BIT
#define VSCODEC0_DREQ_BIT 6
#endif

#ifndef VSCODEC0_XCS_PORT
#define VSCODEC0_XCS_PORT AVRPORTD
#endif

#ifndef VSCODEC0_XCS_BIT
#define VSCODEC0_XCS_BIT 6
#endif

#ifndef VSCODEC0_XDCS_PORT
#define VSCODEC0_XDCS_PORT AVRPORTB
#endif

#ifndef VSCODEC0_XDCS_BIT
#define VSCODEC0_XDCS_BIT 5
#endif

#ifndef VSCODEC0_VSCS_PORT
#define VSCODEC0_VSCS_PORT AVRPORTB
#endif

#ifndef VSCODEC0_VSCS_BIT
#define VSCODEC0_VSCS_BIT 0
#endif

#ifndef LAN91_SIGNAL_IRQ
#define LAN91_SIGNAL_IRQ INT5
#endif

#ifndef VS10XX_SIGNAL_IRQ
#define VS10XX_SIGNAL_IRQ INT0
#endif

#ifndef VS10XX_XCS_PORT
#define VS10XX_XCS_PORT AVRPORTD
#endif

#ifndef VS10XX_XCS_BIT
#define VS10XX_XCS_BIT 6
#endif

#ifndef VS10XX_XDCS_PORT
#define VS10XX_XDCS_PORT AVRPORTB
#endif

#ifndef VS10XX_XDCS_BIT
#define VS10XX_XDCS_BIT 5
#endif


#endif
