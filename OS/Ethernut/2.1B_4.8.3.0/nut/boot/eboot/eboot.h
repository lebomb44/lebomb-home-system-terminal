#ifndef _EBOOT_H
#define _EBOOT_H

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
 *
 */

/*
 * $Log: eboot.h,v $
 * Revision 1.2  2004/09/10 10:10:17  haraldkipp
 * Removed unused bootp parameters
 *
 * Revision 1.1  2004/04/15 09:34:45  haraldkipp
 * Checked in
 *
 */

#include "ether.h"
#include "ip.h"
#include "udp.h"
#include "dhcp.h"
#include "tftp.h"

/*!
 * \addtogroup xgEBoot
 */
/*@{*/

/*
 * Internal compiler address values.
 */
extern unsigned char __data_start;
extern unsigned char __data_end;
extern unsigned char __data_load_start;

extern unsigned char __bss_start;
extern unsigned char __bss_end;

typedef struct {
    ETHERHDR eth_hdr;
    IPHDR    ip_hdr;
    UDPHDR   udp_hdr;
    union {
        TFTPHDR  tftp;
        BOOTPHDR bootp;
    } u;
} BOOTFRAME;

/*@}*/

/*
 * Outgoing frame.
 */
extern BOOTFRAME sframe;

/*
 * Incoming frame.
 */
extern BOOTFRAME rframe;


extern u_char mac[6];
extern u_long netmask;
//extern u_long broadcast;
//extern u_long gateway;
//extern u_long dns;
extern u_long sid;
extern u_long local_ip;
extern u_long server_ip;
extern u_char bootfile[128];


#endif
