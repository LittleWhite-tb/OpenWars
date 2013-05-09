#ifndef __NE_SOUNDENGINE_H__
#define __NE_SOUNDENGINE_H__

#include <list>
#include <string>

namespace NE
{
	class SoundLoader;
	class Sound;

	class SoundEngine
	{
	private:

	protected:

		SoundLoader* pSoundLoader;		/*!< Pointer on the SoundLoader to use */

		unsigned int m_globalVolume;	/*!< amount of global volume */

		virtual void applyNewVolume(void)=0;

	public:
		SoundEngine(SoundLoader* pSoundLoader):pSoundLoader(pSoundLoader),m_globalVolume(50) {}
		virtual ~SoundEngine() {}

		bool load(const std::string& fileName);
		virtual Sound* play(const std::string& fileName, const bool loop)=0;

		unsigned int getGlobalVolume(void) { return m_globalVolume; }
		void globalVolumeUp(void) { if ( m_globalVolume < 100 ) m_globalVolume+=5; applyNewVolume(); }
		void globalVolumeDown(void) { if ( m_globalVolume > 0 ) m_globalVolume-=5; applyNewVolume(); }
	};
}

/*! \class NE::SoundEngine SoundEngine.h "NEngine/SoundEngine.h"
 *  \brief SoundEngine interface to handle sound system Sprites
 *
 * The SoundEngine handle the sounds. It is possible to change the master volume.
 */

/*! \fn virtual void NE::SoundEngine::applyNewVolume(void)=0;
 * \brief Applies the new global volume on the sounds
 */
 
/*! \fn NE::SoundEngine::SoundEngine(SoundLoader* pSoundLoader);
 * \param pSoundLoader pointer on the SoundLoader to use
 */

/*! \fn NE::SoundEngine::~SoundEngine();
 */

/*! \fn bool NE::SoundEngine::load(const std::string& fileName);
 * \brief Load a sound file using the SoundLoader.
 * \param fileName the name of the file to load
 * \return true if the sound is correctly loaded. In error cases, messages are output in consoles. Can fail if the file does not exists
 */
 
/*! \fn virtual Sound* NE::SoundEngine::play(const std::string& fileName, const bool loop)=0;
 * \brief Play a sound
 * \param fileName the name of the file to play (will not load, just used as id)
 * \param loop true if the sound needs to be looped
 * \return a pointer on a Sound to control the sound played.
 */

/*! \fn unsigned int NE::SoundEngine::getGlobalVolume(void);
 * \brief Get the amount of master volume
 * \return the master volume amount
 */

/*! \fn void NE::SoundEngine::globalVolumeUp(void);
 * \brief Increase the global volume by 5. Maximum is 100
 */

/*! \fn void NE::SoundEngine::globalVolumeDown(void);
 * \brief Decrease the global volume by 5. Maximum is 100
 */

#endif