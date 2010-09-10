/* $Id$ */
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
#ifndef MIXERGUIPLAYER_H
#define MIXERGUIPLAYER_H

#include <mixergui.h>
#include "widgets/playlist.h"
#include "soundplayer.h"
#include "glowbutton.h"
#include "blinkbutton.h"
#include "timedisplay.h"
#include "playlistitemsongdb.h"

#include <QDropEvent>
#include <QDragEnterEvent>

/**
@author Jan Boysen
*/
class mixerGuiPlayer : public mixerGUI
{
  Q_OBJECT

public:
    mixerGuiPlayer( QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );
    ~mixerGuiPlayer();

	virtual void languageChange();
	virtual QString getType();
        virtual void associateToChannel( mixerChannel* channel );

protected:
        QGridLayout* meterLayout;
	timeDisplay* tDisplay;
        glowButton* playButton;
	glowButton* stopButton;
	blinkButton* pauseButton;
	blinkButton* cueButton;
	blinkButton* openButton;
	glowButton* loopButton;
	vuMeter* levelMeterLeft;
	vuMeter* levelMeterRight;

	// DnD
	virtual void dragEnterEvent( QDragEnterEvent* evt );
	virtual void dropEvent( QDropEvent* evt );

protected slots:
	virtual void fileOpen();
	virtual void setMeta( metaTag );
        virtual void cued( playListItem* );
        virtual void setState( int newState );

public slots:
	virtual void cueTrack( unsigned int playerId, playListItem* song );
	virtual void cueNewTrack();

signals:
	void getNextTrack( unsigned int );
	void sixSecondsLeft();
        void openFile( playListItem* );
	void onCue( metaTag, QString );

};

#endif
