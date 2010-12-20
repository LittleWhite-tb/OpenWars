#ifndef __NESDL_H__
#define __NESDL_H__

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

#include "../NEngine.h"
#include "../NETypes.h"
#include "../../Types/Vec2.h"

#include <string>

class NESDL : public NEngine
{
private:

	Uint32 getFlags(const bool isFullscreen, const bool isOpenGL)const;

public:
	static bool isRedCrossPressed;				/*!< Tell if the red cross button has been pressed */


	NESDL(void);
	~NESDL(void);

	Window createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const bool isOpenGL);
	USize2 getWindowSize(const Window win);
	int getBitsPerPixel(const Window win);
	void destroyWindow(Window win);

	bool isCursorVisible(void)const;
	void setCursorVisible(const bool mustShowCursor)const;
	void setCaption(const std::string& windowName, const std::string& iconName)const;

	bool needWindowClosure(void)const { return isRedCrossPressed; }
};

#endif