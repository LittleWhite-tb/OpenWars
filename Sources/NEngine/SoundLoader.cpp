#include "SoundLoader.h"

#include <string>
#include <iostream>

#include "NEngine/NEngine.h"

#include "Sound.h"

NE::SoundLoader :: ~SoundLoader(void)
{
    for( std::map<std::string, NE::Sound*>::const_iterator itSprite = soundsBank.begin() ; itSprite != soundsBank.end() ; ++itSprite )
	{
		delete (itSprite->second);
	}
	soundsBank.clear();
}

NE::Sound* NE :: SoundLoader :: loadSoundFromFile(const std::string& fileName)
{
	if ( soundsBank.find(fileName) == soundsBank.end() ) // Not found
    {
        Sound* pSound = this->loadSound(fileName);
        if ( pSound == NULL )
        {
            NEError << "NE::SpriteLoader (Fail to load the Sprite ('" << fileName << "')\n";
            return NULL;
        }
        
        soundsBank[fileName] = pSound;
        
        return pSound;
    }
    else
    {
        return soundsBank[fileName];
    }
}
