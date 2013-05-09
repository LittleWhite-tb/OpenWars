#ifndef __NE_SDL_SEMAPHORE_H__
#define __NE_SDL_SEMAPHORE_H__

#include "NEngine/Semaphore.h"

struct SDL_semaphore;

namespace NE
{
	class SDL_Semaphore : public Semaphore
	{
	private:

		SDL_semaphore* pSem;

	protected:

		SDL_Semaphore(const unsigned int initialValue);
		~SDL_Semaphore(void);

	public:

		void wait(void);
		void post(void);

		friend class SDL_NEngine;
	};
}

/*! \class NE::SDL_Semaphore SDL_Semaphore.h "NEngine/Native/SDL/SDL_Semaphore.h"
 *  \brief SDL Semaphore implementation
 *
 * SDL implementation of the Semaphore
 */

/*! \fn NE::SDL_Semaphore::SDL_Semaphore(const unsigned int initialValue);
 * \param initialValue The initial value of the semaphore
 */

/*! \fn virtual NE::SDL_Semaphore::~SDL_Semaphore(void);
 */

#endif
