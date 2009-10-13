/* $Id$ */
/***************************************************************************
 *   OpenRadio - RadioMixer                                                *
 *   Copyright (C) 2005-2009 by Jan Boysen                                *
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

#include "mixerchannel.h"
#include "mixerchannelmanager.h"

mixerChannel::mixerChannel( const char *name )
 : QObject(0, name), provides_audiodata( false ), volume(1), sendVuMeterChanged_left(0), sendVuMeterChanged_right(0)
{
    // initiate my thread and move my eventloop into it...
    thread = new QThread();
    this->moveToThread( thread );
    thread->start();

	// allocate Stereo Sound Ringbuffer.,...
	soundBuffers = new soundRingBuffer[2];
	soundBuffers[0].setName(name+QString("_left"));
	soundBuffers[1].setName(name+QString("_right"));
	soundBuffers[0].setBufSize(16384);
	soundBuffers[1].setBufSize(16384);

	state = 0;
	volume_left = 1;
	volume_right = 1;

        // register myself in the channel manager
        mixerChannelManager::registerChannel( this );
}


mixerChannel::~mixerChannel()
{
}

void mixerChannel::setVolume( int newValue )
{
        float newVolume = (float)newValue/100.f;
        if( newVolume != volume )
        {
            volume = newVolume;
            emit( volumeChanged(newValue) );
        }
}

void mixerChannel::play( )
{
    setState( 1 );
}

void mixerChannel::stop( )
{
    soundBuffers[0].flush();
    soundBuffers[1].flush();
    setState( 0 );
}

void mixerChannel::pause( )
{
    setState( 2 );
}

void mixerChannel::cue( )
{
    setState( 3 );
}

const bool mixerChannel::isPlaying( )
{
	if( state == 1)
		return TRUE;
	else
		return FALSE;
}

const bool mixerChannel::isStopped( )
{
	if( state == 0)
		return TRUE;
	else
		return FALSE;
}

const bool mixerChannel::isPaused( )
{
	if( state == 2)
		return TRUE;
	else
		return FALSE;
}

const bool mixerChannel::isCued( )
{
	if( state == 3)
		return TRUE;
	else
		return FALSE;
}

QString mixerChannel::getName( )
{
	return name;
}

void mixerChannel::setName( QString newName )
{
	name = newName;
	emit( nameChanged( name ) );
}

int mixerChannel::getLevelLeft( )
{
	return int(volume_left*100);
}

int mixerChannel::getLevelRight( )
{
	return int(volume_right*100);
}

/**
 * signal Wrapper only that emits the refresh signal to outside connected stuff.
 */
void mixerChannel::refresh( )
{
	emit( refreshed() );
}

const unsigned int mixerChannel::getSmplRate( )
{
//	return smplRate;
    return 48000;
}

void mixerChannel::connectPort( )
{
}

void mixerChannel::disconnectPort( )
{
}

void mixerChannel::setTreble( int level )
{
    if(level > 0)
    {
        volume_left = (100-level)/100.f;
        volume_right = 1.f;
    }
    else if(level < 0)
    {
        volume_left = 1.f;
        volume_right = (100+level)/100.f;
    }
    else
    {
        volume_left = 1.f;
        volume_right = 1.f;
    }
    emit(trebleChanged(level));
}

bool mixerChannel::canGetData( unsigned int size )
{
	return ( soundBuffers[0].canRead( size ) && soundBuffers[1].canRead( size ) );
}

void mixerChannel::getDataLeft( float * dataOut, unsigned int size )
{
    if(sendVuMeterChanged_left >= 2)
    {
	sendVuMeterChanged_left = 0;
	emit(vuMeterChanged_left(soundBuffers[0].getLastReadAverage()));
    }
    else
	sendVuMeterChanged_left++;

	if(soundBuffers[0].canRead( size ))
		soundBuffers[0].read( dataOut, size );
	else qWarning("oupsi this should never happen........");

}

void mixerChannel::getDataRight( float * dataOut, unsigned int size )
{
    if(sendVuMeterChanged_right >= 2)
    {
	sendVuMeterChanged_right = 0;
	emit(vuMeterChanged_right(soundBuffers[1].getLastReadAverage()));
    }
    else
	sendVuMeterChanged_right++;

        if(soundBuffers[1].canRead( size ))
		soundBuffers[1].read( dataOut, size );
	else qWarning("oupsi this should never happen........");
}

void mixerChannel::checkBuffer( )
{
}

unsigned int mixerChannel::getBuffFill( )
{
	return soundBuffers[0].getFill();
}

bool mixerChannel::providesAudioData()
{
    return provides_audiodata;
}

void mixerChannel::setState(int newState )
{
    this->state = newState;
    emit(stateChanged(state));
}
