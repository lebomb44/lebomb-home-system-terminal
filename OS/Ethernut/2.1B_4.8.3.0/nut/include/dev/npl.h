#ifndef _DEV_NPL_H_
#define _DEV_NPL_H_

/*
 * Copyright (C) 2005 by egnite Software GmbH. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY EGNITE SOFTWARE GMBH AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL EGNITE
 * SOFTWARE GMBH OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * For additional information see http://www.ethernut.de/
 */

#include <dev/irqreg.h>

/*!
 * \file dev/npl.h
 * \brief Nut Programmable Logic Header File
 *
 * \verbatim
 *
 * $Log$
 * Revision 1.2  2006/05/25 09:38:40  haraldkipp
 * Use the AVR way of defining memory mapped I/O.
 *
 * Revision 1.1  2006/01/05 16:32:16  haraldkipp
 * First check-in.
 *
 *
 * \endverbatim
 */

/*!
 * \addtogroup xgNpl
 */
/*@{*/

/*!
 * \brief CPLD register base address.
 *
 * On Ethernut 3 the CPLD is selected via NCS2 (GPIO 27), which
 * is configured to 0x21000000 - 0x210FFFFF in the CRT initialization
 * startup file.
 */
#ifndef NPL_BASE
#if defined(ETHERNUT3)
#define NPL_BASE        0x21000000
#else
#define NPL_BASE        0xFF00
#endif
#endif

/*! \brief RS232 command register.
 */
#define NPL_RSCR        _SFR_MEM8(NPL_BASE + 0x00)

#define NPL_RSFON       0x0001  /*!< \brief Force on. */
#define NPL_RSFOFF      0x0002  /*!< \brief Force off. */
#define NPL_RSDTR       0x0004  /*!< \brief DTR handshake. */
#define NPL_RSRTS       0x0008  /*!< \brief RTS handshake. */
#define NPL_RSUS0E      0x0020  /*!< \brief USART0 select. */
#define NPL_RSUS1E      0x0040  /*!< \brief USART1 select. */
#define NPL_RSUS1P      0x0080  /*!< \brief USART1 primary. */

/*! \brief Interrupt mask register.
 */
#define NPL_IMR         _SFR_MEM16(NPL_BASE + 0x04)

/*! \brief Signal latch register.
 */
#define NPL_SLR         _SFR_MEM16(NPL_BASE + 0x0C)

/*! \brief Signal clear register.
 */
#define NPL_SCR         _SFR_MEM16(NPL_BASE + 0x10)

#define NPL_RSCTS       0x0001  /*!< \brief RS232 CTS interrupt. */
#define NPL_RSDSR       0x0002  /*!< \brief RS232 DSR interrupt. */
#define NPL_RSDCD       0x0004  /*!< \brief RS232 DCD interrupt. */
#define NPL_RSRI        0x0008  /*!< \brief RS232 RI interrupt. */
#define NPL_RTCALARM    0x0010  /*!< \brief RTC alarm interrupt. */
#define NPL_LANWAKEUP   0x0020  /*!< \brief NIC wakeup interrupt. */
#define NPL_FMBUSY      0x0040  /*!< \brief FLASH ready interrupt. */
#define NPL_MMCREADY    0x0080  /*!< \brief MMC shift register ready. */
#define NPL_RSINVAL     0x0100  /*!< \brief RS232 invalid interrupt. */
#define NPL_NRSINVAL    0x0200  /*!< \brief RS232 valid interrupt. */
#define NPL_MMCD        0x0400  /*!< \brief MMC insert interrupt. */
#define NPL_NMMCD       0x0800  /*!< \brief MMC remove interrupt. */

/*! \brief MMC data register.
 */
#define NPL_MMCDR       _SFR_MEM8(NPL_BASE + 0x14)

/*! \brief External enable register.
 */
#define NPL_XER         _SFR_MEM8(NPL_BASE + 0x18)

#define NPL_MMCS        0x0001  /*!< \brief MMC select. */
#define NPL_PANCS       0x0002  /*!< \brief Panel select. */
#define NPL_USRLED      0x0004  /*!< \brief User LED. */
#define NPL_NPCS0       0x0008  /*!< \brief DataFlash CS. */

/*! \brief Version identifier register.
 */
#define NPL_VIDR        _SFR_MEM8(NPL_BASE + 0x1C)

extern IRQ_HANDLER sig_RSCTS;
extern IRQ_HANDLER sig_RSDSR;
extern IRQ_HANDLER sig_RSDCD;
extern IRQ_HANDLER sig_RSRI;
extern IRQ_HANDLER sig_RTCALARM;
extern IRQ_HANDLER sig_LANWAKEUP;
extern IRQ_HANDLER sig_FMBUSY;
extern IRQ_HANDLER sig_RSINVAL;
extern IRQ_HANDLER sig_NRSINVAL;
extern IRQ_HANDLER sig_MMCD;
extern IRQ_HANDLER sig_NMMCD;

__BEGIN_DECLS
/* Function prototypes. */
extern int NplRegisterIrqHandler(IRQ_HANDLER * irq, void (*handler) (void *), void *arg);
extern int NplIrqEnable(IRQ_HANDLER * irq);
extern int NplIrqDisable(IRQ_HANDLER * irq);
__END_DECLS
/* */
/*@}*/
#endif
