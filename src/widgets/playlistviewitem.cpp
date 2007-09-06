/* $Id$ */
/***************************************************************************
 *   OpenRadio - RadioMixer                                                *
 *   Copyright (C) 2006 by Jan Boysen                                *
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
#include "playlistviewitem.h"

static const unsigned char novote_image[] = {
	0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
	0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x10,
	0x08, 0x06, 0x00, 0x00, 0x00, 0x88, 0xa2, 0x58, 0xbb, 0x00, 0x00, 0x00,
	0xe6, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xed, 0x97, 0x4d, 0x0e, 0x84,
	0x20, 0x0c, 0x85, 0xdf, 0x33, 0x92, 0x39, 0x89, 0xf7, 0x3f, 0xd0, 0xec,
	0xbc, 0xc5, 0xa8, 0xc9, 0x9b, 0x85, 0xa9, 0x3f, 0x28, 0xc8, 0x30, 0x4b,
	0xfa, 0x56, 0x44, 0xda, 0x8f, 0xa6, 0x85, 0x0a, 0x94, 0x84, 0x94, 0x48,
	0x0a, 0x00, 0x24, 0x31, 0x69, 0xf4, 0xa0, 0xd6, 0x18, 0x5d, 0xce, 0x59,
	0x12, 0xe7, 0x0f, 0x68, 0xa0, 0x9a, 0x00, 0x5a, 0x63, 0xdc, 0x26, 0xd4,
	0x9c, 0x97, 0x69, 0x2d, 0x44, 0x4d, 0x20, 0xad, 0x32, 0x92, 0x3b, 0xd4,
	0x55, 0x27, 0x4a, 0x42, 0x9c, 0xed, 0x63, 0x35, 0x8e, 0x0a, 0x2f, 0x5c,
	0xec, 0x36, 0x90, 0x33, 0x20, 0x89, 0xbd, 0x6d, 0x67, 0xfb, 0xb8, 0x4c,
	0xc4, 0x9d, 0x33, 0xb0, 0x6e, 0x75, 0x00, 0xc0, 0xb8, 0x2f, 0x2c, 0x89,
	0xce, 0xd8, 0x19, 0xfd, 0xd1, 0xb1, 0x48, 0x63, 0x7a, 0xca, 0x19, 0x40,
	0x67, 0x55, 0xf9, 0xd5, 0x39, 0x0c, 0xd8, 0x2a, 0xe9, 0x8c, 0x9d, 0xd1,
	0x19, 0x24, 0xee, 0x07, 0xa5, 0x01, 0x98, 0x9c, 0xb1, 0x32, 0xb6, 0xbf,
	0x7c, 0x16, 0xf2, 0x10, 0x80, 0x33, 0x76, 0xc6, 0xf5, 0xda, 0x34, 0x46,
	0xe3, 0x4c, 0x9f, 0x49, 0xaa, 0x61, 0x06, 0xed, 0xe9, 0x49, 0x52, 0xf3,
	0x1b, 0x45, 0x9d, 0x38, 0x55, 0x59, 0x67, 0x3c, 0x5c, 0xec, 0xc3, 0x00,
	0x85, 0xe1, 0xa1, 0x97, 0x14, 0x2c, 0xd6, 0x12, 0x23, 0x99, 0x50, 0xcb,
	0xba, 0x24, 0xd6, 0x06, 0xd2, 0x22, 0x63, 0x3b, 0xf2, 0xc0, 0xf9, 0x85,
	0x10, 0x1f, 0x83, 0xdc, 0x5c, 0xa9, 0x5d, 0x0b, 0x8c, 0x53, 0x42, 0x5d,
	0xff, 0xeb, 0x0b, 0x01, 0x39, 0x0e, 0xff, 0x87, 0x42, 0x43, 0xf2, 0x00,
	0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char voted6_image[] = {
	0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
	0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x10,
	0x08, 0x06, 0x00, 0x00, 0x00, 0x88, 0xa2, 0x58, 0xbb, 0x00, 0x00, 0x00,
	0xe0, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xed, 0x97, 0xcd, 0x11, 0x85,
	0x20, 0x0c, 0x84, 0x37, 0x8e, 0x95, 0xd8, 0x49, 0x2a, 0xb7, 0x13, 0x1d,
	0x2a, 0xd9, 0x77, 0x40, 0x10, 0x51, 0x10, 0x79, 0x47, 0xb2, 0x17, 0x0f,
	0x66, 0x3f, 0x33, 0x89, 0xe1, 0x47, 0x48, 0xa2, 0x24, 0x11, 0x21, 0x00,
	0x90, 0x94, 0x62, 0xd0, 0x8b, 0x46, 0x63, 0x4c, 0x35, 0x33, 0x49, 0x6c,
	0xdb, 0x16, 0x41, 0x3d, 0x09, 0x8c, 0xc6, 0x78, 0x2c, 0x68, 0x30, 0xef,
	0xfb, 0x0e, 0x00, 0x5d, 0x89, 0x8c, 0xca, 0x28, 0xfe, 0xa1, 0xa6, 0x3e,
	0x09, 0xc9, 0x5b, 0xb5, 0xd3, 0x6e, 0xa4, 0x5a, 0x96, 0x05, 0x59, 0x5c,
	0x5c, 0x4b, 0x8c, 0xe1, 0x19, 0xe2, 0x9f, 0xa7, 0xff, 0xc9, 0x98, 0xcb,
	0x39, 0x07, 0x00, 0x50, 0x55, 0x0f, 0x39, 0x46, 0xc2, 0x18, 0x8a, 0xf9,
	0x8b, 0x31, 0x35, 0x3f, 0xc9, 0x18, 0xc0, 0x74, 0x74, 0xe5, 0xb3, 0x39,
	0x74, 0x14, 0x00, 0x8c, 0x71, 0x32, 0xa6, 0x00, 0xc9, 0xd7, 0x83, 0xd6,
	0x04, 0x82, 0x8c, 0xe1, 0x19, 0x71, 0x97, 0xaf, 0x41, 0xde, 0x12, 0x30,
	0xc6, 0xc9, 0xb8, 0x1d, 0x9b, 0xd2, 0x60, 0xe7, 0x5c, 0x75, 0x9d, 0x29,
	0x69, 0x64, 0x86, 0x84, 0x1d, 0x4d, 0x44, 0xb8, 0xae, 0x6b, 0xd3, 0x47,
	0x4a, 0x9d, 0x35, 0xc6, 0xcb, 0xc1, 0x5e, 0x55, 0xa1, 0xaa, 0x4d, 0x50,
	0x63, 0x78, 0x15, 0x0b, 0x1a, 0xaa, 0x4e, 0x52, 0x7a, 0x13, 0x19, 0x91,
	0x11, 0x47, 0x1e, 0xb8, 0xde, 0x10, 0xf2, 0x31, 0xa8, 0xbd, 0x6b, 0x8d,
	0x1b, 0x81, 0x71, 0x29, 0xa8, 0xe9, 0x7f, 0xfd, 0x00, 0x3b, 0x83, 0x37,
	0x08, 0xbf, 0x06, 0x12, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e,
	0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char voted5_image[] = {
	0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
	0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x10,
	0x08, 0x06, 0x00, 0x00, 0x00, 0x88, 0xa2, 0x58, 0xbb, 0x00, 0x00, 0x01,
	0x36, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xed, 0x97, 0x6b, 0x8e, 0x84,
	0x20, 0x10, 0x84, 0xab, 0xcd, 0x9a, 0xbd, 0x87, 0xc9, 0x1c, 0x84, 0x93,
	0x7b, 0x90, 0x4d, 0x34, 0xcc, 0x2d, 0xe6, 0x91, 0xd4, 0xfe, 0xd0, 0x76,
	0x10, 0x01, 0x19, 0xe6, 0x97, 0x38, 0x95, 0x18, 0x7c, 0xf1, 0x01, 0x45,
	0xd3, 0xa2, 0x90, 0x44, 0x4c, 0x22, 0x42, 0x00, 0x20, 0x29, 0xd1, 0x97,
	0x76, 0x74, 0x36, 0x46, 0x93, 0xaa, 0x4c, 0x12, 0x8f, 0xdb, 0x0b, 0x54,
	0xd2, 0x01, 0x92, 0x18, 0x86, 0xe1, 0x34, 0x8c, 0xa0, 0xa1, 0x5a, 0xf9,
	0x79, 0x9f, 0x26, 0xa2, 0xc4, 0x54, 0x65, 0x8c, 0xe3, 0x08, 0x00, 0x45,
	0x83, 0x39, 0x22, 0x23, 0x1a, 0xa1, 0x5f, 0x95, 0x49, 0x48, 0x6e, 0xdc,
	0x76, 0xa3, 0xd3, 0x55, 0xfb, 0xbb, 0xbe, 0x76, 0x73, 0x49, 0x88, 0xa1,
	0x33, 0xea, 0xaa, 0xeb, 0xba, 0xaa, 0x19, 0x32, 0x95, 0xaf, 0xfa, 0x21,
	0x23, 0x37, 0xba, 0x4e, 0x45, 0x7b, 0x99, 0x21, 0xf3, 0x92, 0x50, 0x85,
	0x1a, 0xf7, 0x65, 0xad, 0x05, 0x00, 0x18, 0x63, 0xaa, 0x62, 0xfc, 0xe8,
	0xcd, 0x2c, 0x23, 0x81, 0xc5, 0xcc, 0x90, 0x72, 0x1a, 0x77, 0x3b, 0x50,
	0x23, 0xa3, 0x99, 0x67, 0x25, 0xab, 0xb2, 0x6b, 0xa6, 0x46, 0x27, 0xb0,
	0x44, 0xe9, 0xdb, 0x1d, 0xd0, 0xa8, 0xa8, 0x89, 0xd1, 0x28, 0xc4, 0xcf,
	0x8f, 0x1b, 0x45, 0xcc, 0x54, 0x91, 0x14, 0x3f, 0xa7, 0xe4, 0x0e, 0xa2,
	0x26, 0xc6, 0xf2, 0x95, 0x4f, 0x9a, 0xba, 0x63, 0x66, 0x4e, 0x47, 0xf6,
	0x06, 0x51, 0x0b, 0x63, 0xbb, 0x6d, 0xba, 0x7a, 0xe7, 0x89, 0x9c, 0x19,
	0x93, 0xdb, 0xa0, 0xb5, 0x36, 0x99, 0xab, 0x6a, 0x63, 0x88, 0x7e, 0xd1,
	0x44, 0x84, 0x8f, 0xbf, 0xbc, 0x46, 0x62, 0x51, 0x2a, 0x22, 0xec, 0xfb,
	0x3e, 0x8b, 0x11, 0x8b, 0x8e, 0xa3, 0x33, 0x92, 0x1b, 0xfb, 0xf6, 0x32,
	0x1d, 0x9f, 0xc8, 0x18, 0x03, 0x63, 0xcc, 0x69, 0x18, 0x51, 0x43, 0x35,
	0x0a, 0x49, 0x4a, 0xa9, 0xa9, 0x3a, 0x73, 0x24, 0xa5, 0x74, 0x30, 0x47,
	0x63, 0x2c, 0x4b, 0x1e, 0x58, 0xff, 0x21, 0xf8, 0xcb, 0x20, 0xf5, 0x2c,
	0xf7, 0xbd, 0x33, 0x30, 0x56, 0x86, 0x7e, 0xf5, 0xb9, 0xfe, 0x01, 0xd6,
	0x6b, 0x1e, 0x46, 0x94, 0xfe, 0x42, 0x95, 0x00, 0x00, 0x00, 0x00, 0x49,
	0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char voted4_image[] = {
	0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
	0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x10,
	0x08, 0x06, 0x00, 0x00, 0x00, 0x88, 0xa2, 0x58, 0xbb, 0x00, 0x00, 0x01,
	0x48, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xed, 0x97, 0x61, 0x8e, 0x82,
	0x30, 0x10, 0x85, 0xdf, 0x90, 0x25, 0xde, 0x83, 0xc4, 0x83, 0xf4, 0xe4,
	0x1c, 0xc4, 0x04, 0x52, 0x6f, 0xa1, 0x6e, 0x32, 0xfb, 0x03, 0x06, 0x4a,
	0xa1, 0xa5, 0xa9, 0x23, 0x5b, 0xa3, 0x2f, 0x21, 0x80, 0xd2, 0x4f, 0xe6,
	0xf5, 0x75, 0x40, 0x62, 0x66, 0x84, 0x44, 0x44, 0x0c, 0x00, 0xcc, 0x4c,
	0xc1, 0x8b, 0x76, 0xf4, 0x69, 0x8c, 0x2a, 0x36, 0x98, 0x99, 0xf1, 0xb8,
	0xcd, 0xa0, 0x9c, 0x1b, 0xd0, 0x62, 0x74, 0x5d, 0xf7, 0x16, 0x8c, 0x4d,
	0x43, 0x65, 0xf0, 0xef, 0x7d, 0x98, 0x88, 0x1c, 0x43, 0x34, 0x19, 0x7d,
	0xdf, 0x03, 0x40, 0x96, 0x21, 0x47, 0x33, 0x82, 0x09, 0xfd, 0x2a, 0x4f,
	0xc4, 0xcc, 0x2b, 0xb7, 0xdd, 0x64, 0xb9, 0xaa, 0x4f, 0xcb, 0x73, 0xb7,
	0x97, 0xbc, 0x8a, 0x21, 0xa9, 0x70, 0xd5, 0x34, 0x4d, 0xb1, 0x0c, 0x1a,
	0xf6, 0xf3, 0xf8, 0x2d, 0x13, 0x56, 0xba, 0x0e, 0xbb, 0xfa, 0x3c, 0x42,
	0xc6, 0x25, 0xa1, 0xc9, 0xd8, 0x2a, 0xc0, 0x97, 0xb5, 0x16, 0x00, 0x60,
	0x8c, 0x29, 0x86, 0xf1, 0x23, 0x1f, 0x26, 0x99, 0x00, 0x4c, 0x46, 0x6c,
	0x49, 0x83, 0x91, 0x52, 0x00, 0x30, 0x17, 0x51, 0x1a, 0xa3, 0x1a, 0x67,
	0x25, 0x69, 0xb0, 0x6b, 0x84, 0x24, 0x0b, 0x98, 0x12, 0x76, 0x18, 0xc3,
	0x2d, 0x42, 0x92, 0x55, 0x0a, 0xa3, 0x12, 0x88, 0xdf, 0xdb, 0x56, 0x0a,
	0x18, 0x21, 0xd2, 0x62, 0xf8, 0x7d, 0xc9, 0x57, 0xc8, 0x88, 0x52, 0x18,
	0xd3, 0x53, 0x3e, 0x6a, 0xc8, 0x8e, 0x11, 0xda, 0x8c, 0x50, 0x31, 0x7b,
	0x46, 0x94, 0xc0, 0x58, 0xbf, 0x36, 0x5d, 0xbd, 0xe3, 0x48, 0xbf, 0x0b,
	0x4a, 0x81, 0xe1, 0xde, 0xb4, 0xb5, 0x36, 0xda, 0xef, 0x4a, 0x62, 0x90,
	0x3c, 0xd1, 0x88, 0x88, 0x1f, 0x97, 0xb4, 0x1f, 0x09, 0x25, 0x4c, 0x8b,
	0xd1, 0xb6, 0x6d, 0x12, 0x23, 0x94, 0xb0, 0xff, 0x64, 0x44, 0x5f, 0xec,
	0xeb, 0xf3, 0xb0, 0x3d, 0x23, 0x0d, 0x86, 0x31, 0x06, 0xc6, 0x98, 0xb7,
	0x60, 0x04, 0x0d, 0x95, 0x04, 0x31, 0x33, 0xe5, 0x1a, 0xa2, 0xc1, 0x90,
	0xd9, 0x67, 0x66, 0xca, 0x35, 0xe4, 0x48, 0xc6, 0xb4, 0xe4, 0x81, 0xe5,
	0x3f, 0x04, 0x7f, 0x19, 0xc4, 0xbe, 0x4b, 0xbd, 0xee, 0x13, 0x18, 0x0b,
	0x43, 0xbf, 0x7a, 0x5e, 0x7f, 0x05, 0x53, 0x05, 0x84, 0xa2, 0x37, 0x1e,
	0xdb, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
	0x82
};

static const unsigned char voted3_image[] = {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x88, 0xa2, 0x58, 0xbb, 0x00, 0x00, 0x01,
    0x47, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xed, 0x97, 0x7d, 0x8a, 0x83,
    0x30, 0x10, 0xc5, 0xdf, 0x48, 0x65, 0xef, 0x51, 0xe8, 0x41, 0x72, 0x72,
    0x0f, 0xb2, 0x60, 0x88, 0xb7, 0xe8, 0x07, 0xbc, 0xfd, 0xc3, 0x4d, 0x8d,
    0xa9, 0x89, 0xd9, 0xa8, 0x30, 0x4b, 0xfb, 0xa0, 0xd0, 0xa2, 0xf9, 0xd9,
    0xf7, 0x32, 0x33, 0xaa, 0x90, 0x44, 0x4a, 0x22, 0x42, 0x00, 0x20, 0x29,
    0xc9, 0x93, 0x56, 0xf4, 0x6e, 0x8c, 0x26, 0xb7, 0x98, 0x24, 0xee, 0xd7,
    0x09, 0x54, 0xf3, 0x07, 0x34, 0x31, 0xfa, 0xbe, 0x3f, 0x9c, 0xb1, 0x18,
    0xa8, 0x5f, 0xfc, 0xb8, 0x8d, 0x1b, 0x51, 0x63, 0x46, 0x1b, 0xc3, 0x5a,
    0x0b, 0x00, 0x55, 0xa1, 0xfe, 0x85, 0x91, 0xac, 0xd0, 0x8f, 0xea, 0x24,
    0x24, 0x5f, 0xd2, 0x0e, 0xab, 0x22, 0x54, 0xfb, 0x35, 0xff, 0x1d, 0xce,
    0x12, 0xcd, 0x0c, 0x5f, 0x59, 0xa1, 0xce, 0xe7, 0xf3, 0x21, 0x8c, 0x93,
    0x2f, 0x67, 0xaf, 0xc7, 0x4d, 0x16, 0x4d, 0x00, 0x63, 0xcb, 0x01, 0x00,
    0x86, 0xe9, 0xc2, 0x24, 0x45, 0x2b, 0xc3, 0x5a, 0xbb, 0x18, 0x04, 0x30,
    0xb6, 0x2d, 0x00, 0x38, 0xe7, 0x76, 0x65, 0x9c, 0x42, 0x03, 0x45, 0x1a,
    0xd2, 0x87, 0xb4, 0x30, 0x52, 0x01, 0xc4, 0xf2, 0x41, 0xec, 0xc9, 0x68,
    0x7e, 0x77, 0xa5, 0x68, 0x71, 0x68, 0xa2, 0xbd, 0x4c, 0x6d, 0xf2, 0x1f,
    0x19, 0x61, 0x10, 0xc6, 0x98, 0xdd, 0x18, 0x8d, 0x87, 0xc4, 0x73, 0xa9,
    0xd4, 0x84, 0x97, 0x26, 0x46, 0x3c, 0xdb, 0x62, 0xa5, 0xc2, 0xdc, 0x83,
    0xf1, 0xbc, 0xcb, 0x67, 0xcd, 0xac, 0x98, 0xd0, 0xc8, 0x48, 0x05, 0xb2,
    0x16, 0xe6, 0x56, 0xc6, 0xeb, 0x63, 0xd3, 0x10, 0x7d, 0xcf, 0xcc, 0xaa,
    0xa4, 0x94, 0x30, 0x42, 0xe3, 0xce, 0xb9, 0xec, 0xcc, 0xdc, 0x8b, 0x21,
    0xfe, 0x8e, 0x26, 0x22, 0xbc, 0x7f, 0x97, 0x5d, 0x24, 0x55, 0x1d, 0x9a,
    0x18, 0x5d, 0xd7, 0x15, 0x31, 0x52, 0x55, 0x5a, 0xcb, 0xc8, 0x3e, 0xd8,
    0xb7, 0x97, 0xf1, 0xb3, 0x45, 0x5a, 0x18, 0xc6, 0x18, 0x18, 0x63, 0x0e,
    0x67, 0x24, 0x03, 0xf5, 0xbb, 0x4f, 0x52, 0x6a, 0xcd, 0x68, 0x61, 0xf8,
    0x0a, 0x22, 0x29, 0xb5, 0xa1, 0x96, 0x32, 0x9e, 0x2d, 0x0f, 0xcc, 0xdf,
    0x10, 0xe2, 0x36, 0xc8, 0x1d, 0x2b, 0x3d, 0xef, 0x1d, 0x18, 0xb3, 0x40,
    0x3f, 0xda, 0xae, 0x1f, 0x91, 0xd8, 0x05, 0xfd, 0x0d, 0x16, 0x16, 0x29,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char voted2_image[] = {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x88, 0xa2, 0x58, 0xbb, 0x00, 0x00, 0x01,
    0x34, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xed, 0x97, 0x5d, 0x6e, 0x83,
    0x30, 0x10, 0x84, 0x67, 0x51, 0x50, 0xef, 0x81, 0x94, 0x83, 0xf8, 0xe4,
    0x1c, 0xa4, 0x12, 0x96, 0xb9, 0x45, 0x7e, 0xa4, 0xe9, 0x03, 0xdd, 0x60,
    0x8c, 0xd7, 0x71, 0xe9, 0x9b, 0xc9, 0x3c, 0x81, 0x30, 0x9f, 0x47, 0xb3,
    0xde, 0x25, 0x11, 0x92, 0xb0, 0x24, 0x22, 0x04, 0x00, 0x92, 0x62, 0x2e,
    0x7a, 0xa3, 0xb3, 0x31, 0xba, 0xd2, 0xcb, 0x24, 0xf1, 0xb8, 0xad, 0xa0,
    0x23, 0x06, 0x5a, 0x63, 0x4c, 0xd3, 0x54, 0x64, 0x64, 0x03, 0xd5, 0x97,
    0x9f, 0xf7, 0xa5, 0x10, 0x47, 0x8c, 0xb4, 0xc8, 0xf0, 0xde, 0x03, 0x40,
    0x31, 0x54, 0xf3, 0x84, 0x7e, 0x74, 0x4c, 0x42, 0x72, 0x97, 0x76, 0x5c,
    0xd1, 0x58, 0xfd, 0xd7, 0xf6, 0x3e, 0x9e, 0x25, 0xad, 0x33, 0xf4, 0x74,
    0xc6, 0x1a, 0x86, 0x61, 0xc7, 0xb8, 0xe8, 0x71, 0x56, 0x3d, 0xef, 0x92,
    0x35, 0x00, 0x2c, 0xed, 0x02, 0x00, 0x98, 0xd7, 0x8d, 0x49, 0x4a, 0xcb,
    0x0c, 0xef, 0x7d, 0x36, 0x4c, 0x60, 0x69, 0x7d, 0x00, 0x08, 0x21, 0xbc,
    0x18, 0x97, 0x78, 0xf3, 0x2a, 0xcd, 0xf6, 0xa3, 0x96, 0x18, 0x56, 0x88,
    0xa9, 0x34, 0x4c, 0x55, 0xf7, 0x5b, 0x95, 0x3f, 0x1b, 0xe8, 0xaf, 0x6b,
    0x9b, 0x9c, 0x95, 0x11, 0x87, 0xe9, 0x9c, 0x03, 0x49, 0xe9, 0x14, 0x92,
    0xce, 0x94, 0x5a, 0x03, 0xaa, 0xd6, 0x18, 0xe9, 0x7c, 0x4c, 0x95, 0x0b,
    0x13, 0x88, 0xbe, 0xf2, 0x45, 0x23, 0x6f, 0x0c, 0xb4, 0xca, 0xb0, 0x42,
    0xb5, 0xc2, 0x04, 0x72, 0x3f, 0x9b, 0xe6, 0xe4, 0xba, 0x30, 0x67, 0x4c,
    0x35, 0xc4, 0x88, 0xc3, 0x0b, 0x21, 0xec, 0x66, 0x66, 0x2a, 0xd1, 0x2f,
    0x9a, 0x88, 0xf0, 0xf1, 0x5d, 0xb7, 0x89, 0x55, 0xd9, 0xd6, 0x18, 0xe3,
    0x38, 0x56, 0x31, 0xb2, 0x2d, 0x6f, 0x6d, 0xd6, 0x5f, 0xeb, 0x8c, 0x9d,
    0x81, 0xe1, 0x9c, 0x83, 0x73, 0xae, 0xb8, 0xc6, 0x0c, 0x54, 0x2b, 0x47,
    0x52, 0x8e, 0x1a, 0x69, 0x89, 0xa1, 0xa7, 0x90, 0xa4, 0x94, 0x42, 0x7d,
    0xb5, 0x3c, 0xb0, 0xfd, 0x87, 0x90, 0xb6, 0x41, 0xe9, 0x59, 0xed, 0xba,
    0x33, 0x30, 0x36, 0x81, 0x7e, 0xf4, 0x7f, 0xfd, 0x00, 0x5f, 0x9b, 0xec,
    0x79, 0x3e, 0xff, 0xa5, 0xc9, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e,
    0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char voted1_image[] = {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x88, 0xa2, 0x58, 0xbb, 0x00, 0x00, 0x00,
    0xe0, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xed, 0x97, 0x4d, 0x0e, 0x84,
    0x20, 0x0c, 0x85, 0x5f, 0x8d, 0x66, 0x4e, 0xe2, 0xfd, 0x0f, 0x34, 0x3b,
    0x6f, 0x31, 0x6a, 0xf2, 0x66, 0xc1, 0x54, 0xf0, 0x07, 0x64, 0x70, 0xd9,
    0xbe, 0xc4, 0x44, 0x03, 0xfd, 0x68, 0xda, 0x52, 0x50, 0x48, 0x22, 0x27,
    0x11, 0x21, 0x00, 0x90, 0x94, 0xec, 0xa4, 0x1b, 0x59, 0x63, 0x74, 0x25,
    0x63, 0x92, 0x58, 0x3e, 0x11, 0xd4, 0xe2, 0x80, 0x35, 0xc6, 0x65, 0x40,
    0xd5, 0x78, 0x9d, 0x43, 0x22, 0x5a, 0x1c, 0xb1, 0xca, 0xc8, 0x56, 0xa8,
    0xab, 0x4d, 0x42, 0xf2, 0x14, 0xed, 0x34, 0x1b, 0xa9, 0x86, 0xd7, 0xfe,
    0x3b, 0xed, 0x25, 0xce, 0x08, 0x8c, 0x5e, 0xcb, 0x59, 0xb5, 0xce, 0x72,
    0x69, 0x0c, 0x84, 0x52, 0x07, 0x00, 0x4c, 0x71, 0x61, 0x92, 0xe2, 0x8c,
    0xc8, 0xe8, 0x53, 0xc3, 0x2a, 0x4d, 0xf9, 0x21, 0x67, 0x00, 0xdd, 0x2f,
    0x2b, 0x7f, 0x1b, 0x0f, 0x63, 0xdc, 0x26, 0xce, 0x88, 0x8c, 0x4e, 0x21,
    0xc7, 0x7e, 0x50, 0xeb, 0x80, 0xca, 0x19, 0x81, 0xb1, 0x9d, 0xf2, 0x45,
    0xc8, 0x8d, 0x03, 0xce, 0x88, 0x8c, 0xf3, 0xb5, 0x69, 0x3a, 0xbc, 0x17,
    0xfa, 0x4c, 0x56, 0x86, 0x19, 0xa2, 0x27, 0x9a, 0x88, 0x70, 0x79, 0xd7,
    0xad, 0x91, 0xcb, 0xac, 0x33, 0x6e, 0x2e, 0xf6, 0xc3, 0x18, 0x9e, 0x27,
    0xb2, 0xc6, 0xc8, 0x06, 0x54, 0xa3, 0x4e, 0x52, 0x5a, 0x1d, 0xb1, 0xc8,
    0xd8, 0xb6, 0x3c, 0xb0, 0xff, 0x43, 0x38, 0x6e, 0x83, 0xd2, 0x58, 0xed,
    0x3c, 0x0b, 0x8c, 0x5d, 0x40, 0x5d, 0xcf, 0xf5, 0x05, 0xf0, 0xcc, 0xd3,
    0x04, 0x38, 0xa1, 0x7e, 0x64, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e,
    0x44, 0xae, 0x42, 0x60, 0x82
};

playListViewItem::playListViewItem( QListView * parent )
 : QListViewItem( parent )
{
	setDragEnabled(TRUE);
	setDropEnabled(TRUE);
}

playListViewItem::playListViewItem( QListView * parent, playListItem * item, QListViewItem * after )
 : QListViewItem( parent, after ), playListEntry( item )
{
	setDragEnabled(TRUE);
	setDropEnabled(TRUE);

	setText( 0, item->getSong() );
	setText( 1, item->getGenre() );
	setText( 2, item->getLength().toString()+( item->getPreLength() > QTime()?" ("+item->getPreLength().toString()+")":"" ) );
	setVote( item->getVote() );
}

playListViewItem::playListViewItem( QListViewItem * parent, QString newSong, QListViewItem * after )
 : QListViewItem( parent, after )
{
	playListEntry = new playListItem( newSong );
	setDragEnabled(TRUE);
	setDropEnabled(TRUE);

	setText( 0, playListEntry->getSong() );
	setText( 1, playListEntry->getGenre() );
	setText( 2, playListEntry->getLength().toString()+( playListEntry->getPreLength() > QTime()?" ("+playListEntry->getPreLength().toString()+")":"" ) );
	setVote( playListEntry->getVote() );
}

playListViewItem::playListViewItem( playListViewItem * parent )
 : QListViewItem( parent )
{
	setDragEnabled(TRUE);
	setDropEnabled(TRUE);
}

playListViewItem::playListViewItem(QListViewItem * parent, QDomDocument domdoc )
: QListViewItem( parent )
{
	setDragEnabled(TRUE);
	setDropEnabled(TRUE);

	QDomElement item = domdoc.documentElement();
	if( item.tagName() == "playListEntry" )
		qWarning("playListEntry");
	else if( item.tagName() == "songdbEntry" )
		playListEntry = new playListItemSongDB( item.attribute("id").toInt() );

	connect( playListEntry, SIGNAL( refreshed()), this, SLOT(refresh()));

	playListEntry->refreshMeta();
	setText( 0, tr("retriving data from songDB...") );
}

playListViewItem::~playListViewItem()
{
	delete playListEntry;
}

void playListViewItem::paintCell( QPainter * p, const QColorGroup & cg, int column, int width, int alignment )
{
	QColor itemBGColor = cg.base();
	QColor itemFGColor = cg.text();

	if( isSelected() )
	{
		itemBGColor = cg.highlight();
		itemFGColor = cg.highlightedText();
	}else
		if( playListEntry->hasCostumBackgroundColor() )
			itemBGColor = playListEntry->getBackgroundColor();
		else
			if( (itemPos()/height())%2 == 1)
				itemBGColor = cg.highlight().light( 175 );

	QColorGroup _cg( cg );
	_cg.setColor( QColorGroup::Base, itemBGColor );
	_cg.setColor( QColorGroup::Text, itemFGColor );
	QListViewItem::paintCell( p, _cg, column, width, alignment );
}

void playListViewItem::setVote(int vote)
{
	switch( vote )
	{
		case 1:
			voteImage.loadFromData( voted1_image, sizeof( voted1_image ), "PNG");
			break;
		case 2:
			voteImage.loadFromData( voted2_image, sizeof( voted2_image ), "PNG");
			break;
		case 3:
			voteImage.loadFromData( voted3_image, sizeof( voted3_image ), "PNG");
			break;
		case 4:
			voteImage.loadFromData( voted4_image, sizeof( voted4_image ), "PNG");
			break;
		case 5:
			voteImage.loadFromData( voted5_image, sizeof( voted5_image ), "PNG");
			break;
		case 6:
			voteImage.loadFromData( voted6_image, sizeof( voted6_image ), "PNG");
			break;
		default:
			voteImage.loadFromData( novote_image, sizeof( novote_image ), "PNG");
	};
	setPixmap(3, voteImage);
}

QString playListViewItem::key(int column, bool ascending) const
{
	if(!playListEntry)
		return("0");

	switch( column )
	{
		case 1:
			return( playListEntry->getGenre() );
		case 2:
			return( playListEntry->getLength().toString() );
		case 3:
			if(playListEntry->getVote() == 0)
				return "99999999999999999999";
			else
				return( QString::number(playListEntry->getVote()) );
		default:
			return( playListEntry->getSong() );
	}
}

void playListViewItem::refresh()
{
	setText( 0, playListEntry->getSong() );
	setText( 1, playListEntry->getGenre() );
	setText( 2, playListEntry->getLength().toString()+( playListEntry->getPreLength() > QTime()?" ("+playListEntry->getPreLength().toString()+")":"" ) );
	setVote( playListEntry->getVote() );
}

bool playListViewItem::acceptDrop(const QMimeSource * mime) const
{
	return mime->provides("application/x-radiomixer-playlistitem") || mime->provides("text/uri-list");
}

void playListViewItem::dropped(QDropEvent * evt)
{
	if( evt->provides("application/x-radiomixer-playlistitem") )
	{
		if( evt->source() == listView() ) // do we move the Item in our own list ?
		{
			QListView* sender = dynamic_cast<QListView*>(evt->source());
			QListViewItem* item = sender->selectedItem();
			if( item == QListViewItem::parent() )
			{
				
				QListViewItem::parent()->takeItem( item );
				QListViewItem::parent()->insertItem( item );
			}
			else
				item->moveItem( this->itemAbove() );
		}else
		{
			QDomDocument doc;
			doc.setContent( evt->encodedData("application/x-radiomixer-playlistitem") );
			if( !doc.isDocument() )
			{
				qWarning( QObject::tr("Received an invalid Document") );
				return;
			}
			playListViewItem* pli = new playListViewItem( this, doc );
			pli->moveItem( itemAbove() );

			QListView* sender = dynamic_cast<QListView*>(evt->source());
			if( sender )
				sender->takeItem( sender->selectedItem() );
		}
	}else if( evt->provides("text/uri-list") )
	{
		if( QUriDrag::canDecode( evt ) )
		{
			QStringList uriList;
			QUriDrag::decodeLocalFiles( evt, uriList );
			if(uriList.first() && ( uriList.first().contains(".ogg" ) || uriList.first().contains(".mp3" ) ) )
				new playListViewItem( QListViewItem::parent(), uriList.first(), this );
		}
	}
}


//
// songDragObject Class Below
//

songDragObject::songDragObject( playListViewItem* item, QWidget* dragSource = 0, const char * name = 0) :
QStoredDrag( "application/x-radiomixer-playlistitem", dragSource, name )
{
	QDomDocument songDocument("RadioMixerPlayListItem");
	songDocument.appendChild( item->playListEntry->toDomElement( &songDocument ) );

	QString str = songDocument.toString();
	QByteArray* data = new QByteArray( str.length() );

	memcpy( data->data(), str.latin1(), str.length() );
	setEncodedData( *data );
}

songDragObject::~songDragObject()
{
}
