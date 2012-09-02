#ifndef __SDL_SOUND_H__
#define __SDL_SOUND_H__

#include "SDL_SoundEngine.h"
#include "NEngine/Sound.h"

#include <SDL/SDL.h>

namespace NE
{
    class SoundEngine;

    struct Sample
    {
        Uint32 length;      /*!< Length of the buffer */
        Uint8* pBuffer;     /*!< Pointer to the buffer data */

        Sample():length(0),pBuffer(NULL) {}

        friend void NE::play(void* pData, Uint8 *pStream, int len);
    };

    class SDL_Sound : public Sound
    {
    private:

        Sample m_sample;            /*<! the sample of the sound */
        Uint32 m_position;          /*<! The current position of the sound */
        bool m_loop;                /*<! True if the sound loops */

    public:

        SDL_Sound(Sample sample):m_sample(sample),m_position(0),m_loop(false) {}

        void play(const int volume, const bool loop=false);
        void stop(void);

        Sample* getSample(void) { return &m_sample; }

        Uint32 getPosition()const { return m_position; }
        void setPosition(const Uint32 position);

        bool getLoop()const { return m_loop; }
        void setLoop(const bool loop) { m_loop = loop; }

        friend void NE::play(void* pData, Uint8 *pStream, int len);
    };
}

/*! \class NE::SDL_Sound SDL_Sound.h "NEngine/Native/SDL/SDL_Sound.h"
 *  \brief SDL implementation of Sound
 *
 * SDL is a bit fuzzy when it comes to sound. Effectiveky, a callback is called and a buffer needs to be loaded with sound data. All of this has to be done by hand.
 * Secondly, this is breaking the whole NEngine design, even if this implementation is hidding the stuff.
 */

 /*! \struct NE::Sample SDL_Sound.h "NEngine/Native/SDL/SDL_Sound.h"
 *  \brief Sample of sound
 */

/*! \fn bool NE::Sample::Sample()
 */

/*! \fn bool NE::SDL_Sound::SDL_Sound(Sample sample)
 * \param sample the Sample of the sound
 */

/*! \fn void NE::SDL_Sound::play(const int volume, const bool loop=false)
 * \brief Play the sound
 * \param volume the volume of the sound to play
 * \param loop true if the sound has to be looped
 */

/*! \fn void NE::SDL_Sound::stop()
 */

/*! \fn Sample* NE::SDL_Sound::getSample(void)
 * \return pointer to the Sample of the sound
 */

/*! \fn Uint32 NE::SDL_Sound::getPosition()const
 * \return the position of the sound
 */

/*! \fn void NE::SDL_Sound::setPosition(const Uint32 position)
 * \param position the position of the sound to set
 */

/*! \fn bool NE::SDL_Sound::getLoop(void)const
 * \return true if the sound is looping
 */

/*! \fn void NE::SDL_Sound::setLoop(const bool loop)
 * \param loop true if the sound is looping
 */

#endif
