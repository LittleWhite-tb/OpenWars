#ifndef __NE_SDL_SOUNDENGINE__
#define __NE_SDL_SOUNDENGINE__

#include "NEngine/SoundEngine.h"

#include <SDL/SDL.h>

#include <vector>

namespace NE
{
    class Sound;
    class SDL_Sound;
    class SoundLoader;

    class SDL_SoundEngine : public SoundEngine
    {
        struct SoundInfo
        {
            NE::SDL_Sound* pSoundData;  /*<! Pointer on SDL_Sound informations (buffer ; position) */
            int m_volume;               /*<! Volume to play the sound */

            bool isPlaying;             /*<! true if the sound is currently playiung */

            SoundInfo(void):pSoundData(NULL),m_volume(0) {}

            bool play(Uint8 *pStream, int len);

            void clear(void);
        };


    private:

        static const unsigned int SOUND_LIMIT = 256;                /*<! Maximal number of sounds that can be played at the same time */

        SDL_AudioSpec m_audioSpec;                      /*<! currently used audio spec (internal to SDL) */

        std::vector<SoundInfo> m_playingSounds;         /*<! pool of Sound */
        unsigned int m_numberPlayingSound;                  /*<! number of playing Sound */

        /**
            The mutex will avoid race condition when adding a sound and updating the sound buffer.
            Both are using the m_playingSounds vertex, one in addition, one in deletion
        */
        SDL_mutex* m_pSoundMutex;               /*<! Mutex to avoid race condition */

    private:
        void applyNewVolume(void);

    public:
        SDL_SoundEngine(SoundLoader* const pSoundLoader);
        ~SDL_SoundEngine();

        Sound* play(const std::string& fileName, const bool loop);

        friend void play(void* pData, Uint8 *pStream, int len);
    };

    void play(void* pData, Uint8 *pStream, int len);
}

/*! \class NE::SDL_SoundEngine SDL_SoundEngine.h "NEngine/Native/SDL/SDL_SoundEngine.h"
 *  \brief SDL implementation of SDL_SoundEngine
 *
 * SDL implementation of the SDL_SoundEngine
 * The SoundEngine contains a memory pool of preallocated sounds
 */

/*! \fn NE::SDL_SoundEngine::SoundInfo::SoundInfo(void)
 */

/*! \fn bool NE::SDL_SoundEngine::SoundInfo::play(Uint8 *pStream, int len)
 * \brief play function to fill the SDL buffer with the data from the sound
 * \param pStream the buffer to fill
 * \param len the length of buffer to copy
 * \param bool true if all goes right ; false if an error occurs of the sound is finished.
 */

/*! \fn void NE::SDL_SoundEngine::SoundInfo::clear(void);
 * \brief clear the sound info to prepare it for next sound
 */

/*! \fn void NE::SDL_SoundEngine::SoundInfo::clear(void);
 * \brief clear the sound info to prepare it for next sound
 */


/*! \fn NE::SDL_SoundEngine::SDL_SoundEngine(SoundLoader* const pSoundLoader)
 * \param pSoundLoader pointer on the SoundLoader
 */

/*! \fn NE::SDL_SoundEngine::~SDL_SoundEngine()
 */


/*! \fn void NE::play(void* pData, Uint8 *pStream, int len);
 * \brief function for the SDL callback
 * \param pData additionnal data (Should contain pointer to the SDL_SoundEngine)
 * \param pStream the buffer to fill
 * \param len the length of buffer to copy
 */



#endif
