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
 * Revision 1.2  2008/01/31 09:38:15  haraldkipp
 * Added return statement in main to avoid warnings with latest GCC.
 *
 * Revision 1.1  2003/08/05 18:59:05  haraldkipp
 * Release 3.3 update
 *
 * Revision 1.4  2003/02/04 18:19:39  harald
 * Version 3 released
 *
 * Revision 1.3  2003/02/04 16:24:35  harald
 * Adapted to version 3
 *
 * Revision 1.2  2002/06/26 17:29:04  harald
 * First pre-release with 2.4 stack
 *
 * Revision 1.1  2001/06/28 18:39:59  harald
 * Preview release
 *
 */

/*!
 * \example simple/simple.c
 *
 * This sample is the most simple application that could be build
 * with Nut/OS. It doesn't do anything but running in a loop.
 *
 * Only a minimal Nut/OS kernel with thread, timer and memory
 * management is loaded, occupying less than 4 kBytes of code
 * space and about 50 bytes of RAM.
 */

#include <compiler.h>

/*!
 * \brief Main application routine. 
 *
 */
int main(void)
{
    for (;;);
    return 0;
}
