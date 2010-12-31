#ifndef __NE_SPRITE_H__
#define __NE_SPRITE_H__

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

#include "../Types/Size2.h"

namespace NE
{
	class Sprite
	{
	protected:
		void* pData;		/*!< The pointer on the native Sprite */
	public:
		Sprite(void* pData):pData(pData) {}
		virtual ~Sprite(void) {}

		virtual USize2 getSize(void)const=0;

		friend class Renderer;
	};
}

/*! \class NE::Sprite Sprite.h "NEngine/Sprite.h"
 *  \brief Sprite interface
 *
 * The Sprite class gives an interface to implement new platform specific Sprite functions.
 */

/*! \fn NE::Sprite::Sprite(void* pData)
 * \param pData the pointer on the native sprite data
 */

/*! \fn virtual NE::Sprite::~Sprite(void)
 */

/*! \fn virtual USize2 NE::Sprite::getSize(void)const=0
 * \brief Get the size of the Sprite
 * \return the size of the Sprite
 */

#endif