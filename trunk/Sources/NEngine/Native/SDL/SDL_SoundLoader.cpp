#include "SDL_SoundLoader.h"

#include "NEngine/NEngine.h"

#include <cstring>
#include <iostream>
#include <cassert>

#include <SDL/SDL.h>

#include "SDL_Sound.h"

NE::SDL_SoundLoader::~SDL_SoundLoader(void)
{
	for( std::map<std::string, NE::Sound*>::const_iterator itSprite = soundsBank.begin() ; itSprite != soundsBank.end() ; ++itSprite )
	{
		delete static_cast<NE::SDL_Sound*>((itSprite->second))->getSample()->pBuffer;
		static_cast<NE::SDL_Sound*>((itSprite->second))->getSample()->pBuffer = NULL;
	}
}

NE::Sound* NE :: SDL_SoundLoader :: loadSound(const std::string& fileName)
{
	SDL_AudioSpec loadedSpec;
	Uint8* pBuffer=NULL;
	Uint32 length=0;
	Sample finalSample;
		
	if ( SDL_LoadWAV(fileName.c_str(), &loadedSpec, &pBuffer, &length) == NULL )
	{
		NEError << "Fail to load sound '" << fileName << "' (" << SDL_GetError() << ")\n";
		return NULL;
	}
	else
	{
		bool converted = false;
		SDL_AudioCVT cvt;

		if ( SDL_BuildAudioCVT(&cvt, loadedSpec.format, loadedSpec.channels, loadedSpec.freq, AUDIO_S8, 1, 22050) == 0)
		{
			NEError << "Fail to initialise the structure for convertion (" << SDL_GetError() << ")\n";
		}
		else
		{
			cvt.buf = new Uint8[length * cvt.len_mult];

			if ( cvt.buf == NULL )
			{
				NEError << "Fail to allocate memory for sound convertion (" << length * cvt.len_mult << ")\n";
			}

			memcpy(cvt.buf, pBuffer, length);
			cvt.len = length;

			if ( SDL_ConvertAudio(&cvt) != 0 )
			{
				NEError << "Fail to convert the audio to the appropriate format (" << SDL_GetError() << ")\n";
			}
			else
			{
				// We have to keep this converted sound
				// The lock is blocking the GP2X after second run
				// SDL_LockAudio();
				finalSample.length = cvt.len_cvt;
				finalSample.pBuffer = cvt.buf;
				// SDL_UnlockAudio();

				// We delete previous buffer
				SDL_FreeWAV(pBuffer);

				// To tell that we converted the sound
				converted = true;
			}

			if ( converted == false )
			{
				SDL_LockAudio();
				finalSample.length = length;
				finalSample.pBuffer = pBuffer;
				SDL_UnlockAudio();
			}
		}
	}

	Sound* pSound = new SDL_Sound(finalSample);
	return pSound;
}
