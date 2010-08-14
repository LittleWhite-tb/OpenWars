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

#include "Sprite.h"

#include <SDL/SDL.h>

#include <string>

#include "../Utils/Logger.h"

Sprite :: Sprite(const std::string fileName)
{
	LDebug << "Sprite created from file (" << fileName.c_str() << ")";
}

Sprite :: ~Sprite(void)
{
	LDebug << "Sprite deleted";
}

const int Sprite :: getWidth(void)
{
	LDebug << "Sprite :: getWidth (" << this->sprite->w << ")";

	return this->sprite->w;
}

const int Sprite :: getHeight(void)
{
	LDebug << "Sprite :: getHeight (" << this->sprite->h << ")";

	return this->sprite->h;
}