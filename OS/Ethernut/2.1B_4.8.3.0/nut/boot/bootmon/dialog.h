#ifndef _DIALOG_H
#define _DIALOG_H

/*
 * Copyright (C) 2005-2007 by egnite Software GmbH. All rights reserved.
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
 * $Log$
 * Revision 1.2  2009/02/28 15:28:46  olereinhardt
 * Fixed compiler warnings (signedness)
 *
 * Revision 1.1  2007/08/17 13:16:32  haraldkipp
 * Checked in.
 *
 */

extern void PutString(char *cp);
extern void PutHex(unsigned char val);
extern void PutShortHex(unsigned short val);
extern void PutLongHex(unsigned long val);
extern int GetLine(char *line, int size);
extern char *GetIP(char *prompt, char *value);
extern void GetMac(unsigned char *mac);

#ifdef NUTDEBUG

#define DEBUG(s)        PutString(s)
#define DEBUGUCHAR(v)   PutHex(v)
#define DEBUGUSHORT(v)  PutShortHex(v)
#define DEBUGULONG(v)   PutLongHex(v)

#else

#define DEBUG(s)
#define DEBUGUCHAR(v)
#define DEBUGUSHORT(v)
#define DEBUGULONG(v)

#endif

#endif
