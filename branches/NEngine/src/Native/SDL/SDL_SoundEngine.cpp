#include "SDL_SoundEngine.h"

#include <SDL/SDL.h>

#include <iostream>
#include <cassert>

#include "NEngine/NEngine.h"
#include "NEngine/SoundLoader.h"
#include "SDL_Sound.h"

bool NE::SDL_SoundEngine::SoundInfo::play(Uint8 *pStream, int len)
{
    int amount = 0;

    if (this->pSoundData == NULL )
    {
        return false;
    }
    if ( this->pSoundData->getSample()->pBuffer == NULL )
    {
        return false;
    }

    if ( this->pSoundData->getSample()->length == 0 )
        return false;


    if ( this->pSoundData->getPosition() >= this->pSoundData->getSample()->length )
    {
        // Looping
        if ( this->pSoundData->getLoop() )
        {
            this->pSoundData->setPosition(0);
        }
        else // We are after the sound
        {
            return false;
        }
    }

    // On regarde ce qui reste à jouer
    amount = (this->pSoundData->getSample()->length - this->pSoundData->getPosition());

    // Check
    if ( amount > len )
        amount = len;

    // Mixing sound
    SDL_MixAudio(pStream, &this->pSoundData->getSample()->pBuffer[this->pSoundData->getPosition()], amount, static_cast<int>(this->m_volume));

    // Update of the position
    this->pSoundData->setPosition(this->pSoundData->getPosition()+amount);

    return true;
}

void NE::SDL_SoundEngine::SoundInfo::clear(void)
{
    pSoundData->setPosition(0);
    pSoundData->setLoop(false);
    m_volume = 0;
    pSoundData = NULL;
}

    // Callback for the sound
// small visibility ... only available in this file
void NE::play(void* pData, Uint8 *pStream, int len)
{
    // Pointer protection
    assert(pData);
    assert(pStream);

    NE::SDL_SoundEngine* pSoundEngine = static_cast<SDL_SoundEngine*>(pData);

    SDL_LockMutex(pSoundEngine->m_pSoundMutex);

    for (unsigned int i = 0 ; i < pSoundEngine->m_numberPlayingSound ; )
    {
        if (pSoundEngine->m_playingSounds[i].play(pStream,len) == false)
        {
            // m_playingSounds[i].stop();

            // Move the song to another position in the pool
            // To keep all playing song at the beginning

            pSoundEngine->m_playingSounds[i] = pSoundEngine->m_playingSounds[pSoundEngine->m_numberPlayingSound-1];
            /*
            pSoundEngine->m_playingSounds[i].pSoundData->setPosition(pSoundEngine->m_playingSounds[pSoundEngine->m_numberPlayingSound-1].pSoundData->getPosition());
            pSoundEngine->m_playingSounds[i].pSoundData->setLoop(pSoundEngine->m_playingSounds[pSoundEngine->m_numberPlayingSound-1].pSoundData->getLoop());
            pSoundEngine->m_playingSounds[pSoundEngine->m_numberPlayingSound-1].clear();
            */
            pSoundEngine->m_numberPlayingSound--;

            // not incrementing because we have to play this one (since we just move it here)
        }
        else
        {
            ++i;
        }
    }

    SDL_UnlockMutex(pSoundEngine->m_pSoundMutex);
}

void fill_audio(void* pData, Uint8 *pStream, int len)
{
    NE::play(pData,pStream,len);
}

void NE :: SDL_SoundEngine :: applyNewVolume(void)
{
    for (unsigned int i = 0 ; i < m_numberPlayingSound ; i++ )
    {
        m_playingSounds[i].m_volume = this->m_globalVolume;
    }
}

NE :: SDL_SoundEngine :: SDL_SoundEngine(SoundLoader* const pSoundLoader):SoundEngine(pSoundLoader)
{
    // Set the audio format
    m_audioSpec.freq = 22050;
    // m_audioSpec.format = AUDIO_S16;  // On Linux this line has to be used ... otherwise the program is strangely freezing
    m_audioSpec.format = AUDIO_S8;
    m_audioSpec.channels = 1;    // 1 = mono, 2 = stereo
    m_audioSpec.samples = 1024;  // Good low-latency value for callback
    m_audioSpec.callback = fill_audio;
    m_audioSpec.userdata = (void*)this;

    if ( SDL_OpenAudio(&m_audioSpec, NULL) < 0 )
    {
        NEError << "SDL_SoundEngine failed to get the desired audio\n";
    }
    else
    {
        NEDebug << "SDL_SoundEngine created\n";
    }

    m_pSoundMutex = SDL_CreateMutex();

    // Allocating memory
    this->m_playingSounds.reserve(SOUND_LIMIT);
    this->m_playingSounds.resize(SOUND_LIMIT);
    m_numberPlayingSound = 0;
}

NE :: SDL_SoundEngine :: ~SDL_SoundEngine()
{
    SDL_PauseAudio(1);

    SDL_LockMutex(m_pSoundMutex);
    for ( unsigned int i = 0 ; i < m_numberPlayingSound ; i++ )
    {
        m_playingSounds[i].clear();
    }

    m_playingSounds.clear();
    SDL_UnlockMutex(m_pSoundMutex);

    SDL_CloseAudio();

    SDL_DestroyMutex(m_pSoundMutex);

    NEDebug << "SDL_SoundEngine ended\n";
}

NE::Sound* NE::SDL_SoundEngine::play(const std::string& fileName, const bool loop)
{
    Sound* pSound = pSoundLoader->loadSoundFromFile(fileName);

    if ( pSound == NULL )
    {
        return NULL;
    }

    SDL_LockMutex(m_pSoundMutex);

    if ( m_numberPlayingSound <  NE::SDL_SoundEngine::SOUND_LIMIT)
    {
        // Make the Audio start
        SDL_PauseAudio(0);

        m_playingSounds[m_numberPlayingSound].pSoundData = static_cast<SDL_Sound*>(pSound);
        m_playingSounds[m_numberPlayingSound].pSoundData->setLoop(loop);
        m_playingSounds[m_numberPlayingSound].m_volume = this->m_globalVolume;

        m_numberPlayingSound++;
    }
    else
    {
        NEWarning << "Impossible to have more sound playing (limit reached)\n";
    }
    SDL_UnlockMutex(m_pSoundMutex);

    return pSound;
}
