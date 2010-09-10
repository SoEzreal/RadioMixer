/* $Id$ */
/***************************************************************************
 *   OpenRadio - RadioMixer                                                *
 *   Copyright (C) 2009-2010 by Jan Boysen                                 *
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
#ifndef MIXERCHANNEL_JACKOUT_H
#define MIXERCHANNEL_JACKOUT_H

#include <mixerchannel.h>
#include "jack.h"

/**
@author Jan Boysen
*/
class mixerChannel_jackOut : public mixerChannel
{
Q_OBJECT
public:
    explicit mixerChannel_jackOut( const char *name = 0, QUuid uuid = QUuid() );
    virtual ~mixerChannel_jackOut();

    static QString const Type;

    virtual AudioDataType getAudioDataType() { return mixerChannel::AudioDataOut; }
    virtual QString getType() { return Type; }
    virtual void process( jack_nframes_t );

protected:
	jack_port_t*	jack_port[2];
	jack_nframes_t	frames;

private:
	float levelMeterLeft;
	float levelMeterRight;

public slots:
	virtual void mute();
	virtual void unMute();
	virtual void connectPort();
	virtual void disconnectPort();
};

#endif //MIXERCHANNEL_JACKOUT
