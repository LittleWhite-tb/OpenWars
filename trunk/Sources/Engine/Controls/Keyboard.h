#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

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

enum ArrowsDirection
{
	AD_UP,
	AD_UPRIGHT,
	AD_RIGHT,
	AD_RIGHTDOWN,
	AD_DOWN,
	AD_DOWNLEFT,
	AD_LEFT,
	AD_LEFTUP,
	AD_NONE
};

class Keyboard
{
private:
	int nbKeys;					/*!< The number of keys repertoried in the array */
	unsigned char* keys;		/*!< Array of keys state */

public:
	//! Basic constructor
	/*!
      Call the update function to have an array ready
    */
	Keyboard(void);

	//! Basic destructor
	/*!
      Do nothing because the array get is an internal SDL array
    */
	~Keyboard(void);

	//! Check if the escape key is pressed
	/*!
	  \return 0 if the escape key is not pressed
    */
	unsigned char isEscapePressed(void)const;

	//! Check which direction the user wants to go
	/*!
	  The function is checking the arrow keys and determine which direction the user wants to go. The check allows diagonals directions.
	  \return the direction
    */
	ArrowsDirection getDirectionPressed(void)const;

	//! Check the specified key
	/*!
	  \param key the key to check
	  \return 0 if the key is not pressed
	*/
	unsigned char isKey(unsigned int key);

	//! Update the keys array
	/*!
	*/
	void update(void);
};

/*! \class Keyboard Keyboard.h "Engine/Controls/Keyboard.h"
 *  \brief Handle the pressed keys
 *
 * Can check the following:
 *		- If the escape key is pressed
 *		- Which direction is pressed ( by checking the arrows keys )
 */

/*! \enum ArrowsDirection
 * Identify the direction on which one the user wants to go
 * The diagonals are handled
 */

#endif