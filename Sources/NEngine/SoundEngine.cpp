#include "SoundEngine.h"

#include "SoundLoader.h"

bool NE :: SoundEngine :: load(const std::string& fileName)
{
	if ( pSoundLoader->loadSoundFromFile(fileName) != NULL )
	{
		return true;
	}

	return false;
}