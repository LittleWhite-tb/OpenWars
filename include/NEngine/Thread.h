#ifndef __NE_THREAD_H__
#define __NE_THREAD_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
NEngine: Native Engine abstracts multimedia libraries such as SDL, SFML, Allegro
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

website: https://github.com/LittleWhite-tb/NEngine
e-mail: lw.demoscene@gmail.com
**/
#endif

namespace NE
{
	class Thread
	{
	protected:
		int (*fct)(void*);			/*!< Pointer on the function to run in the Thread */
		void* data;					/*!< data to pass to the Thread */

		Thread(int (*fct)(void*),void* data):fct(fct),data(data) {}
		virtual ~Thread(void) {}

	public:

		virtual void start(void)=0;
		virtual void stop(void)=0;
		virtual void wait(void)=0;

		friend class NEngine;
	};
}

/*! \class NE::Thread Thread.h "NEngine/Thread.h"
 *  \brief Thread interface
 *
 * The Thread allows to run a specific function in a separate thread.
 */

/*! \fn NE::Thread::Thread(int (*fct)(void*),void* data);
 * \param fct the function pointer to run in the thread
 * \param data the data to pass to the thread
 */

/*! \fn virtual NE::Thread::~Thread(void);
 */

/*! \fn virtual void  NE::Thread::start(void)=0;
 * \brief Starts the thread
 */

/*! \fn virtual void  NE::Thread::stop(void)=0;
 * \brief Stops the thread
 */

/*! \fn virtual void NE::Thread::wait(void)=0;
 * \brief Make the caller waiting for the thread
 */

#endif
