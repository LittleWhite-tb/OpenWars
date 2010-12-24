#ifndef __INPUT_H__
#define __INPUT_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010  Alexandre LAURENT

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

website: http://code.google.com/p/openawars/
e-mail: lw.demoscene@gmail.com
**/
#endif

class Input
{
public:
	typedef int ArrowsDirection;
	typedef int Buttons;

	// Bit field definition for arrows direction
	static const ArrowsDirection AD_UP = 1;
	static const ArrowsDirection AD_UPRIGHT = 3;
	static const ArrowsDirection AD_RIGHT = 2;
	static const ArrowsDirection AD_RIGHTDOWN = 6;
	static const ArrowsDirection AD_DOWN = 4;
	static const ArrowsDirection AD_DOWNLEFT = 12;
	static const ArrowsDirection AD_LEFT = 8;
	static const ArrowsDirection AD_LEFTUP = 9;
	static const ArrowsDirection AD_NONE = 0;

	// Bit Field definition
	static const Buttons INPUT_NONE = 0;
	static const Buttons INPUT_A = 1;
	static const Buttons INPUT_B = 2;
	static const Buttons INPUT_X = 4;
	static const Buttons INPUT_Y = 8;
	static const Buttons INPUT_L = 16;
	static const Buttons INPUT_R = 32;
	static const Buttons INPUT_START = 64;
	static const Buttons INPUT_SELECT = 128;
	static const Buttons INPUT_VOLUMEUP = 256;
	static const Buttons INPUT_VOLUMEDOWN = 512;

	Input(void) {}
	virtual ~Input(void) {}

	virtual ArrowsDirection getDirection(void)=0;
	virtual Buttons getButtons(void)=0;
};

#endif