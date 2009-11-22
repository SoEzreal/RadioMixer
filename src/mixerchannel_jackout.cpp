/* $Id$ */
/***************************************************************************
 *   OpenRadio - RadioMixer                                                *
 *   Copyright (C) 2009 by Jan Boysen                                      *
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
#include "mixerchannel_jackout.h"

mixerChannel_jackOut::mixerChannel_jackOut( QString chName, const char *name )
 : mixerChannel( name ), levelMeterLeft(0), levelMeterRight(0)
{
	this->name = chName;

	// shrink the buffer size for lower latency...
	soundBuffers[0].setBufSize(8192);
	soundBuffers[1].setBufSize(8192);

#warning TODO.......
//	connect( jackPlayer, SIGNAL( onConnect() ), this, SLOT( connectPort()) );
//	connect( jackPlayer, SIGNAL( onDisconnect() ), this, SLOT( disconnectPort()) );
	connectPort();
        registerChannel();
}


mixerChannel_jackOut::~mixerChannel_jackOut( )
{
//	if( player->isConnected() )
//		disconnectPort();
}

void mixerChannel_jackOut::process( jack_nframes_t frames  )
{
	jack_default_audio_sample_t*	destL = ( jack_default_audio_sample_t* ) jack_port_get_buffer (jack_port[0], frames);
	jack_default_audio_sample_t*	destR = ( jack_default_audio_sample_t* ) jack_port_get_buffer (jack_port[1], frames);

	if( canGetData(frames) )
	{
	    getDataLeft( destL, frames );
	    getDataRight( destR, frames );
	}
	else
	    for(int i;i<=frames;i++)
	    {
		destL[i] = 0;
		destR[i] = 0;
	    }
}

void mixerChannel_jackOut::setVolume( int volume )
{
	this->volume = float(100.f-volume)/100.f;
}

void mixerChannel_jackOut::mute( )
{
//	disconnect( jackIn[0], SIGNAL( processData( jack_nframes_t ) ), this, SLOT( processJackLeft( jack_nframes_t ) ) );
//	disconnect( jackIn[1], SIGNAL( processData( jack_nframes_t ) ), this, SLOT( processJackRight( jack_nframes_t ) ) );

//	jack_default_audio_sample_t*	mixedL = ( jack_default_audio_sample_t* ) jack_port_get_buffer (jackOut[0]->jackport, frames);
//	jack_default_audio_sample_t*	mixedR = ( jack_default_audio_sample_t* ) jack_port_get_buffer (jackOut[1]->jackport, frames);
//	unsigned int sample_off = 0;
//	while( sample_off < frames )
//	{
//		mixedL[sample_off] = 0.f;
//		mixedR[sample_off] = 0.f;
//		sample_off++;
//	}
}

void mixerChannel_jackOut::unMute( )
{
//	connect( jackIn[0], SIGNAL( processData( jack_nframes_t ) ), this, SLOT( processJackLeft( jack_nframes_t ) ) );
//	connect( jackIn[1], SIGNAL( processData( jack_nframes_t ) ), this, SLOT( processJackRight( jack_nframes_t ) ) );
}

void mixerChannel_jackOut::connectPort( )
{
    jack_port[0] = Jack::newPort( getName()+QString("_L"), JackPortIsOutput);
    jack_port[1] = Jack::newPort( getName()+QString("_R"), JackPortIsOutput);
    unMute();
}

void mixerChannel_jackOut::disconnectPort( )
{
	mute();
//	player->unregisterJackPort( jackIn[0] );
//	player->unregisterJackPort( jackOut[0] );
//	player->unregisterJackPort( jackIn[1] );
//	player->unregisterJackPort( jackOut[1] );
}

