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
#include "mixerchannel_jackin.h"
#include "mixerchannelmanager.h"

QString const mixerChannel_jackIn::Type = QString("JACKIN");

mixerChannel_jackIn::mixerChannel_jackIn( QString name, QUuid uuid )
 : mixerChannel( name, uuid ), levelMeterLeft(0), levelMeterRight(0)
{
    type = Type;
	smplRate = Jack::getSmplRate();

	// shrink the buffer size for lower latency...
        soundBuffers[0].setBufSize(3072);
        soundBuffers[1].setBufSize(3072);

//	connect( jackPlayer, SIGNAL( onConnect() ), this, SLOT( connectPort()) );
//	connect( jackPlayer, SIGNAL( onDisconnect() ), this, SLOT( disconnectPort()) );
	connectPort();
        registerChannel();
}


mixerChannel_jackIn::~mixerChannel_jackIn( )
{
    // unregister myself in the channel manager
    mixerChannelManager::unregisterChannel( this );
    disconnectPort();
}

void mixerChannel_jackIn::process( jack_nframes_t frames  )
{
    if(!jack_port[0]||!jack_port[1])
        return;
    jack_default_audio_sample_t*    sourceL = ( jack_default_audio_sample_t* ) jack_port_get_buffer (jack_port[0], frames);
    jack_default_audio_sample_t*    sourceR = ( jack_default_audio_sample_t* ) jack_port_get_buffer (jack_port[1], frames);

    // copy Jacks buffer to our own...
    if( soundBuffers[0].canWrite( frames ) )
	soundBuffers[0].write( sourceL, frames);
    if( soundBuffers[1].canWrite( frames ) )
	soundBuffers[1].write( sourceR, frames);
}

void mixerChannel_jackIn::mute( )
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

void mixerChannel_jackIn::unMute( )
{
//	connect( jackIn[0], SIGNAL( processData( jack_nframes_t ) ), this, SLOT( processJackLeft( jack_nframes_t ) ) );
//	connect( jackIn[1], SIGNAL( processData( jack_nframes_t ) ), this, SLOT( processJackRight( jack_nframes_t ) ) );
}

void mixerChannel_jackIn::connectPort( )
{
    jack_port[0] = Jack::newPort( getName().left(16)+QString("_L"), JackPortIsInput);
    jack_port[1] = Jack::newPort( getName().left(16)+QString("_R"), JackPortIsInput);
    unMute();
}

void mixerChannel_jackIn::disconnectPort( )
{
    if(jack_port[0])
        Jack::unregisterPort( jack_port[0] );
    if(jack_port[1])
        Jack::unregisterPort( jack_port[1] );
}

void mixerChannel_jackIn::setName( QString newName )
{
    if(!jack_port[0]||!jack_port[1])
        return;
    mixerChannel::setName( newName );
    jack_port_set_name(jack_port[0], settings["name"].toString()+QString("_L") );
    jack_port_set_name(jack_port[1], settings["name"].toString()+QString("_R") );
}

void mixerChannel_jackIn::updateSettings( settingsType settings )
{
    if(!jack_port[0]||!jack_port[1])
        return;
    jack_port_set_name(jack_port[0], settings["name"].toString()+QString("_L") );
    jack_port_set_name(jack_port[1], settings["name"].toString()+QString("_R") );
    mixerChannel::updateSettings( settings );
}
