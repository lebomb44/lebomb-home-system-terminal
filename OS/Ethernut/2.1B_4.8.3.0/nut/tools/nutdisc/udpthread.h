#ifndef _UDPTHREAD_H_
#define _UDPTHREAD_H_

/* ----------------------------------------------------------------------------
 * Copyright (C) 2005-2006 by egnite Software GmbH
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * ----------------------------------------------------------------------------
 */

/*
 * $Log$
 * Revision 1.2  2008/01/31 15:33:33  haraldkipp
 * Linux fixes.
 *
 * Revision 1.1  2006/09/07 08:58:27  haraldkipp
 * First check-in
 *
 */

#include "mainframe.h"

#define UDP_EVENT    200

class CUdpThread : public wxThread
{
public:
    CUdpThread(CMainFrame *frame);

    virtual void *Entry();
    virtual void OnExit();
//new
    bool Broadcast(DISCOVERY_TELE *dist = NULL);
//new

public:
    CMainFrame *m_frame;
};

#endif