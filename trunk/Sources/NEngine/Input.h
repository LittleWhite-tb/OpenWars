#ifndef __NE_INPUT_H__
#define __NE_INPUT_H__

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

namespace NE
{
	class Input
	{
	public:
		typedef int ArrowsDirection;		/*!< Type for the directions */
		typedef int Buttons;				/*!< Type for the buttons */

		// Bit field definition for arrows direction
		static const ArrowsDirection AD_UP = 1;			/*!< Arrow UP */
		static const ArrowsDirection AD_UPRIGHT = 3;	/*!< Arrow UP and RIGHT */
		static const ArrowsDirection AD_RIGHT = 2;		/*!< Arrow RIGHT */
		static const ArrowsDirection AD_RIGHTDOWN = 6;	/*!< Arrow RIGHT and DOWN */
		static const ArrowsDirection AD_DOWN = 4;		/*!< Arrow DOWN */
		static const ArrowsDirection AD_DOWNLEFT = 12;	/*!< Arrow DOWN and LEFT */
		static const ArrowsDirection AD_LEFT = 8;		/*!< Arrow LEFT */
		static const ArrowsDirection AD_LEFTUP = 9;		/*!< Arrow LEFT and UP */
		static const ArrowsDirection AD_NONE = 0;		/*!< No direction pressed */

		// Bit Field definition
		static const Buttons INPUT_NONE = 0;			/*!< No button pressed */
		static const Buttons INPUT_A = 1;				/*!< Button A */
		static const Buttons INPUT_B = 2;				/*!< Button B */
		static const Buttons INPUT_X = 4;				/*!< Button X */
		static const Buttons INPUT_Y = 8;				/*!< Button Y */
		static const Buttons INPUT_L = 16;				/*!< Button L */
		static const Buttons INPUT_R = 32;				/*!< Button R */
		static const Buttons INPUT_START = 64;			/*!< Button START */
		static const Buttons INPUT_SELECT = 128;		/*!< Button SELECT */

		Input(void) {}
		virtual ~Input(void) {}

		virtual ArrowsDirection getDirection(void)=0;
		virtual Buttons getButtons(void)=0;
	};
}

/*! \class NE::Input Input.h "NEngine/Input.h"
 *  \brief Input interface
 *
 * The Input class gives an interface to implement new platform specific inputs.
 */

/*! \fn NE::Input::Input(void)
 */

/*! \fn virtual NE::Input::~Input(void)
 */

/*! \fn virtual NE::Input::ArrowsDirection NE::Input::getDirection(void)=0
 * \brief Get the direction where the user wants to go
 * \return the direction
 */

/*! \fn virtual NE::Input::Buttons NE::Input::getButtons(void)=0
 * \brief Get the buttons pressed by the user
 * \return the buttons
 */

#endif
