#ifndef __VTIME_H__
#define __VTIME_H__

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

class VTime
{
private:

	unsigned int time;					/*!< The virtual time */
	unsigned int lastDrawTime;			/*!< The last update of the virtual time (drawing synchro) */
	unsigned int lastUpdateTime;		/*!< The last update of the update (update synchro) */

	const unsigned int msSecondsBetweenTwoFrame;		/*!< Time between two frames */
	const unsigned int msSecondsBetweenTwoUpdate;		/*!< Time between two updates */

	//! Update the class
	/*!
		Will increment the virtual time, and update the lastDrawTime variable
	*/
	void update(void);
public:
	//! Construct the VTime
	/*!
		Assign the different frequencies
		\param nbFPS The number of FPS between two frames
		\param updateNbFPS The number of FPS between two updates
	*/
	VTime(const unsigned int nbFPS, const unsigned int updateNbFPS);

	//! Wait until the next frame has to be displayed
	/*!
		Use the lastDrawTime variable to know the time to wait
	*/
	void waitNextFrame(void);

	//! Ask if we have to update the game (update synchro)
	/*!
		\return true if we have to update
	*/
	bool canUpdate(void);

	//! Get the actual virtual time
	/*!
		\return the virtual time
	*/
	unsigned int getTime()const { return time; }
#ifdef _DEBUG
	void getTime(const unsigned int newTime) { time = newTime; }
#endif
};

/*! \class VTime VTime.h "Engine/VTime.h"
 *  \brief Virtual Time class
 *
 * Gives an new time, that has to be used with the rest of the program.
 * The new time gives the posssibility to manage the time, independently of the real time
 * Two frenquencies are defined in the class. The first is used for the drawing synchronisation (often 60FPS), the second for the update.
 */

#endif