#ifndef __NENGINE_H__
#define __NENGINE_H__

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

class Window;
class Renderer;
class Input;
class Time;

class NEngine
{
protected:
	Window* pWin;
	Renderer* pRenderer;
	Input* pInput;
	Time* pTime;

public:
	NEngine(void) {}
	virtual ~NEngine(void) {}

	virtual bool init(void)=0;
	virtual bool stop(void)=0;

	Window* getWindow(void) { return pWin; }
	// void setWindow(Window* const pWin) { this->pWin = pWin; }

	Renderer* getRenderer(void) { return pRenderer; }
	// void setRenderer(Renderer* const pRenderer) { this->pRenderer = pRenderer; }

	Input* getInput(void) { return pInput; }
	// void setInput(Input* const pInput) { this->pInput = pInput; }

	Time* getTime(void) { return pTime; }
	// void setTime(Time* const pTime) { this->pTime = pTime; }
};

#endif