/***************************************************************************
 *   OpenRadio - RadioMixer                                                *
 *   Copyright (C) 2005-2010 by Jan Boysen                                 *
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
#ifndef mixerChannel_filePlayer_H
#define mixerChannel_filePlayer_H

#include "mixerchannel.h"
#include "channelbufmngr.h"
#include "filedecoder.h"
#include "playlist.h"

#include <stdio.h>
#include <qregexp.h>

// forward declaration
class channelBufMngr;

/**
@author Jan Boysen
*/
class mixerChannel_filePlayer : public mixerChannel
{
  Q_OBJECT

public:
    explicit mixerChannel_filePlayer( QString name = QString(), QUuid uuid = QUuid() );
    virtual ~mixerChannel_filePlayer();

    static QString const Type;

    // redefined as we have automation support
    virtual bool hasAutomationSupport();

	// Public Member for the BufferMngr Thread
	virtual void checkBuffer();
	virtual const bool isFileOpen();
	virtual const bool isLooping();
	
    // Specialisations
    virtual AudioDataType getAudioDataType() { return mixerChannel::AudioDataIn; }
    virtual QString getType() { return Type; }
    virtual void setName( QString newName );

    // States of the Player
    enum playerState
    {
        Stopped,
        Playing,
        Paused,
        Cued
    } state;
    void setState( playerState );

    // Stream Infos
    const int getRTime();
    const int getTime();
    const float getPosition_Samples();
    const float getTotal_Samples();

    virtual const float getPrerollFrames();
    virtual const float getTotalFrames();
    virtual const float getPlayedFrames();
    virtual const float getRemainFrames();

protected:
	QString fileName;
	FILE* fHandle;
	bool fileOpen;
	bool loopMode;
        playList* playlist;

	fileDecoder* decoder;
	void decode();
        void endOfTrack();

	// Buffer Manager
	channelBufMngr* bufferThread;

        int position_change_counter;

public slots:
        virtual void open( playListItem* track );
        virtual void attachToPlaylist( playList* playlist ); // giving NULL pointer will detach from playlists too
        virtual void detachPlaylist( );
        virtual void close();
	virtual void stop( );
	virtual void play();
	virtual void pause();
        virtual void cue();
	virtual void toggleLoop();

signals:
	void stopped();
	void paused();
	void playing();
        void cued( playListItem* );
	void trackEnded();
        void loopChanged( bool );
	// temporary signal
	void positionChanged( QTime );
};

#endif
