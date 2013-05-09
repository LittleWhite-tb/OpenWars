#include "SoundLoader.h"

#include <string>
#include <iostream>

#include "NEngine/NEngine.h"
#include "NEngine/Exceptions/FileNotFoundException.h"

#include "Sound.h"

NE::Sound* NE :: SoundLoader :: loadSoundFromFile(const std::string& fileName)
{
    NE::Sound* pSound = m_bank.get(fileName);
    
    if ( pSound == NULL ) // It was not in the bank
    {
        for ( std::list<NE::ISoundLoader*>::const_iterator itLoader = m_loaders.begin() ; 
            itLoader != m_loaders.end() ;
            ++itLoader )
        {
            pSound = (*itLoader)->loadSoundFromFile(fileName);
            if ( pSound != NULL )  // It is loaded, we can stop
            {
                m_bank.add(fileName,pSound);
                break;
            }
        }

        // We gone through all loaders, and the sprite is not loaded ... so, error
        if ( pSound == NULL )
        {
            NEError << "Fail to load sound '" << fileName << "'\n";
            throw FileNotFoundException(fileName);
        }
    }
    
    return pSound;
}
