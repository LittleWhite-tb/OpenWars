#ifndef __SDL_NTHREAD_H__
#define __SDL_NTHREAD_H__

#include "NEngine/Thread.h"

struct SDL_Thread;

namespace NE
{
    class SDL_NThread : public Thread
    {
    private:

        SDL_Thread* pThread;

        SDL_NThread(int (*fct)(void*),void* data):Thread(fct,data),pThread(0) {}
        ~SDL_NThread(void) {}

    public:

        void start(void);
        void stop(void);
        void wait(void);

        friend class SDL_NEngine;
    };
}

/*! \class NE::SDL_NThread SDL_NThread.h "NEngine/Native/SDL/SDL_NThread.h"
 *  \brief SDL Thread implementation
 *
 * SDL implementation of the Thread
 */

/*! \fn NE::SDL_NThread::SDL_NThread(int (*fct)(void*),void* data);
 * \param fct the function pointer to run in the thread
 * \param data the data to pass to the thread
 */

/*! \fn virtual NE::SDL_NThread::~SDL_NThread(void);
 */

#endif
