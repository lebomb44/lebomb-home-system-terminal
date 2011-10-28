/*
 * Copyright (C) 2002-2004 by egnite Software GmbH. All rights reserved.
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

/*
 * $Log: util.c,v $
 * Revision 1.2  2007/07/30 09:47:55  olereinhardt
 * ATMega2561 port. Makedefs need to be modifies by hand (uncomment LDFLAGS
 * line and comment out LDFLAGS for mega128
 *
 * Revision 1.1  2004/04/15 09:34:45  haraldkipp
 * Checked in
 *
 */

#include <avr/io.h>
#include "util.h"

/*!
 * \addtogroup xgEBoot
 */
/*@{*/

/*
 * Delay by executing a given number of NOPs.
 */
void Delay(long ms)
{
    long i;

    ms <<= 11;
    for (i = 0; i < ms; i++)
        asm volatile ("nop\n\t"::);
}

#if 0
void Debug(char *cp)
{
    while(*cp) {
#if defined(__AVR_ATmega2561__)    
        while((UCSR0A & (1<<UDRE0)) == 0);
#else
        while((UCSR0A & (1<<UDRE)) == 0);
#endif
        UDR0 = *cp;
        cp++;
    }
}
#endif

/*@}*/
