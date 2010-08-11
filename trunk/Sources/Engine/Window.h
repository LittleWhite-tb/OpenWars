#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

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

website: 
e-mail: lw.demoscene@gmail.com
**/

#include <SDL/SDL.h>

#include <vector>

typedef struct ResolutionInfo
{
	int w;
	int h;
	int bpp;

	ResolutionInfo():w(0),h(0),bpp(0) {}
	ResolutionInfo(const int w, const int h, const int bpp):w(w),h(h),bpp(bpp) {}
}ResolutionInfo;

class Window
{
private:
	const SDL_VideoInfo* pVideoInfo;
	SDL_Surface* pWindowSurface;

	bool isFullscreen;
	bool isOpenGL;

	Uint32 getFlags(const bool isFullscreen, const bool isOpenGL)const;

public:
	Window();
	~Window();

	bool openWindow(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen, const bool isOpenGL);
	bool changeResolution(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen, const bool isOpenGL);

	void getResolutionsAvailable(const bool isOpenGL, std::vector<ResolutionInfo>& riList)const;

	int getHeight(void)const;
	int getWidth(void)const;
	int getBitsPerPixel(void)const;
};

#endif