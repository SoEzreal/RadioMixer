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
#include "vumeter.h"

#include <QPaintEvent>
#include <QResizeEvent>
#include <QPixmap>

vuMeter::vuMeter(QWidget *parent)
 : QWidget(parent), level(0.f), canRepaint(FALSE)
{
    bgColor = parent->palette().color( QPalette::Base );
//    buffer = new QPixmap();
    vuTimer = new QTimer(this);

    // sets some usefull minimum sizes for this widget...
    setMinimumWidth( 10 );
    setMinimumHeight( 100 );
}


vuMeter::~vuMeter()
{
}

void vuMeter::paintEvent( QPaintEvent * event)
{
    if(canRepaint == true)
        paint();
}

void vuMeter::setLevel( float level )
{
    if( level == this->level)
        return;

    this->level = level;
    drawLevelMeter( );
    repaint();
}

void vuMeter::drawLevelMeter( )
{
	canRepaint = TRUE;
/*	if(!buffer)
		qWarning("NULL pixmap buffer!");

    for(int i = 0; i < 2 + 2; i++) {
       peak[i] = hold[i] = 1;
       holdTime[i] = 20;
    }
*/
    numLED = height()/8;
    for( int i = 0; i < numLED; i++) {
	if( i < numLED*0.75)
		color[i] = Qt::green;
	else if( i < numLED*0.9)
		color[i] = Qt::yellow;
	else if( i <= numLED)
		color[i] = Qt::red;
	else
		color[i] = Qt::blue;
    }

    //setBackgroundMode(Qt::NoBackground);
    //buffer->fill( bgColor );
}

void vuMeter::paint( )
{
    QPainter painter( this );
    painter.beginNativePainting();
    for(int i = numLED; i > 0; i--) {
	if(level >= 1)
	{
             painter.setBrush(color[i]);
	}
	else
	{
             painter.setBrush(color[i].dark(300));
	}
	painter.drawRect( 1, height()-8*i, width()-2, 6);
        level *= 1.15;
    }
    painter.end();
}

void vuMeter::timeSlot( )
{
int i;
for(i = 0; i < 2 + 2; i++) {
	peak[i] /= 2;
}
}


void vuMeter::resizeEvent( QResizeEvent * event )
{
        drawLevelMeter();
}


void vuMeter::reset( )
{
	level=0.f;
}
