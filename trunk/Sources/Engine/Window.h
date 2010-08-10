#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

struct SDL_Surface;

class Window
{
private:
	SDL_Surface* pWindowSurface;

	unsigned int width;
	unsigned int height;
	bool isFullscreen;

public:
	Window();
	~Window();

	bool openWindow(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen);
	bool changeResolution(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen);

};

#endif