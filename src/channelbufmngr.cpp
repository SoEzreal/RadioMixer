/***************************************************************************
 *   OpenRadio - RadioMixer	                                           *
 *   Copyright (C) 2005-2007 by Jan Boysen                                *
 *   trekkie@media-mission.de                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "channelbufmngr.h"

channelBufMngr::channelBufMngr(mixerChannel_filePlayer* parent)
 : QThread(), runBufferMngr( true )
{
	this->parent = parent;
}


channelBufMngr::~channelBufMngr()
{
}

void channelBufMngr::stop()
{
    runBufferMngr = false;
}

void channelBufMngr::run( )
{
    while( parent->state != mixerChannel_filePlayer::Stopped )
    {
	while(parent->getBuffFill() < 95 && parent->state == mixerChannel_filePlayer::Playing)
                parent->checkBuffer();
        msleep(100);
    }
}
