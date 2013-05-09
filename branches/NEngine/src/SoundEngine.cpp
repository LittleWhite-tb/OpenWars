#include "NEngine/SoundEngine.h"

#include "NEngine/SoundLoader.h"

bool NE :: SoundEngine :: load(const std::string& fileName)
{
	if ( pSoundLoader->loadSoundFromFile(fileName) != NULL )
	{
		return true;
	}

	return false;
}
