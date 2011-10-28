/*!
 * Copyright (C) 2001-2003 by egnite Software GmbH. All rights reserved.
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

/*!
 * $Log$
 * Revision 1.6  2009/02/08 01:00:33  thiagocorrea
 * Remove unused variable in sample app
 *
 * Revision 1.5  2008/01/31 09:38:15  haraldkipp
 * Added return statement in main to avoid warnings with latest GCC.
 *
 * Revision 1.4  2005/11/22 09:14:13  haraldkipp
 * Replaced specific device names by generalized macros.
 *
 * Revision 1.3  2004/11/24 16:35:56  haraldkipp
 * Configurable floating point support
 *
 * Revision 1.2  2004/09/10 10:33:28  haraldkipp
 * Temporarly removed non-configurable FP support
 *
 * Revision 1.1  2003/08/05 18:59:52  haraldkipp
 * Release 3.3 update
 *
 * Revision 1.3  2003/02/04 18:19:41  harald
 * Version 3 released
 *
 * Revision 1.2  2003/02/04 16:24:38  harald
 * Adapted to version 3
 *
 * Revision 1.1  2002/08/09 12:44:10  harald
 * Renamed for make rules
 *
 * Revision 1.5  2002/06/12 11:00:10  harald
 * *** empty log message ***
 *
 * Revision 1.4  2002/06/04 19:13:21  harald
 * *** empty log message ***
 *
 * Revision 1.3  2002/05/08 16:02:34  harald
 * First Imagecraft compilation
 *
 * Revision 1.2  2001/08/10 18:20:41  harald
 * GCC version 3 update
 *
 * Revision 1.1  2001/06/28 18:43:13  harald
 * Preview release
 *
 */

/*!
 * \example uart/uart.c
 *
 * This sample demonstrates the usage of the ATmega on-chip UART.
 * Note, that we don't do any error checking, because without this
 * UART we can't tell the user our problem.
 *
 * We use floating points. Make sure to link with nutlibcrtf.
 */

#include <cfg/crt.h>    /* Floating point configuration. */

#include <string.h>
#include <stdio.h>
#include <io.h>

#include <dev/board.h>
#include <sys/timer.h>

static char *banner = "\nNut/OS UART Sample\n";
static prog_char presskey_P[] = "Press any key...";
static prog_char pgm_ptr[] = "\nHello stranger!\n";

static char inbuf[128];

/*
 * UART sample.
 *
 * Some functions do not work with ICCAVR.
 */
int main(void)
{
    int got;
    char *cp;
    u_long baud = 115200;
    FILE *uart;
#ifdef STDIO_FLOATING_POINT
    float dval = 0.0;
#endif

    /*
     * Each device must be registered. We do this by referencing the 
     * device structure of the driver. The advantage is, that only 
     * those device drivers are included in our flash code, which we 
     * really need.
     *
     * The uart0 device is the first one on the ATmega chip. So it 
     * has no configurable base address or interrupt and we set both 
     * parameters to zero.
     */
    NutRegisterDevice(&DEV_UART, 0, 0);

    /*
     * Now, as the device is registered, we can open it. The fopen()
     * function returns a pointer to a FILE structure, which we use 
     * for subsequent reading and writing.
     */
    uart = fopen(DEV_UART_NAME, "r+");

    /*
     * Before doing the first read or write, we set the baudrate.
     * This low level function doesn't know about FILE structures
     * and we use _fileno() to get the low level file descriptor
     * of the stream.
     *
     * The short sleep allows the UART to settle after the baudrate
     * change.
     */
    _ioctl(_fileno(uart), UART_SETSPEED, &baud);

    /*
     * Stream devices can use low level read and write functions. 
     * Writing program space data is supported too.
     */
    _write(_fileno(uart), banner, strlen(banner));
    {
        _write_P(_fileno(uart), presskey_P, sizeof(presskey_P));
    }

    /*
     * Stream devices do buffered I/O. That means, nothing will be 
     * passed to the hardware device until either the output buffer 
     * is full or we do a flush. With stream I/O we typically use
     * fflush(), but low level writing a null pointer will also flush 
     * the output buffer.
     */
    _write(_fileno(uart), 0, 0);

    /*
     * The low level function read() will grab all available bytes 
     * from the input buffer. If the buffer is empty, the call will
     * block until something is available for reading.
     */
    got = _read(_fileno(uart), inbuf, sizeof(inbuf));
    _write(_fileno(uart), inbuf, got);

    /*
     * Nut/OS never expects a thread to return. So we enter an 
     * endless loop here.
     */
    for (;;) {
        /*
         * A bit more advanced input routine is able to read a string 
         * up to and including the first newline character or until a
         * specified maximum number of characters, whichever comes first.
         */
        fputs("\nEnter your name: ", uart);
        fflush(uart);
        fgets(inbuf, sizeof(inbuf), uart);

        /*
         * Chop off trailing linefeed.
         */
        cp = strchr(inbuf, '\n');
        if (cp)
            *cp = 0;

        /*
         * Streams support formatted output as well as printing strings 
         * from program space.
         */
        if (inbuf[0])
            fprintf(uart, "\nHello %s!\n", inbuf);
        else {
            fputs_P(pgm_ptr, uart);
        }

        /*
         * Just to demonstrate formatted floating point output.
         * In order to use this, we need to link the application
         * with nutcrtf instead of nutcrt for pure integer.
         */
#ifdef STDIO_FLOATING_POINT
        dval += 1.0125;
        fprintf(uart, "FP %f\n", dval);
#endif
    }
    return 0;
}
