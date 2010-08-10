#include "Window.h"

#include <iostream>

#include <SDL/SDL.h>

Window :: Window()
	:pWindowSurface(NULL),width(0),height(0),isFullscreen(false)
{
	std::cout << "Window created" << std::endl;
}

Window :: ~Window()
{
	// We don't need to close anything

	std::cout << "Window deleted";
}

bool Window :: openWindow(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen)
{
	Uint32 sdlVideoFlags = SDL_HWSURFACE | SDL_DOUBLEBUF;

	if ( isFullscreen )
	{
		// We add the flag for fullscreen
		sdlVideoFlags = sdlVideoFlags | SDL_FULLSCREEN;
	}

	std::cout << "Window :: openWindow (" << width << ";" << height << "x" << bpp << "|" << isFullscreen << ")" << std::endl;

	pWindowSurface = SDL_SetVideoMode(width,height,bpp,sdlVideoFlags);

	if ( pWindowSurface != NULL )
	{
		this->width = width;
		this->height = height;
		this->isFullscreen = isFullscreen;

		return true;
	}
	else
	{
		std::cerr << "Error while opening the window" << std::endl;
		return false;
	}
}

bool Window :: changeResolution(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen)
{
	bool error = true;

	std::cout << "Window :: changeResolution (" << width << ";" << height << "x" << bpp << "|" << isFullscreen << ")" << std::endl;

	// From the SDL documentation for the SDL_SetVideoMode():
	/*
		The surface returned is freed by SDL_Quit() and should nt be freed by the caller.
	*/
	// So we close the surface, we restart SDL and reopen
	SDL_Quit();
	if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		std::cerr << "Error while reopening SDL" << std::endl;
		return false;
	}

	error = this->openWindow(width,height,bpp,isFullscreen);
	
	return error;
}