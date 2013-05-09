#include "SDL_Sound.h"

// I agree, this stuff look useless.
// This is mainly because SDL has a strange way of managing sound
// Other librairies are just doing Sound.play / Sound.stop

void NE :: SDL_Sound :: play(const int volume, const bool loop)
{
	(void)volume;
	(void)loop;
}

void NE :: SDL_Sound :: stop(void)
{
	this->m_loop = false;
	this->m_position = this->m_sample.length;
}

void NE :: SDL_Sound :: setPosition(const Uint32 position) 
{ 
	if ( position < m_sample.length ) 
	{
		m_position = position; 
	}
	else
	{
		m_position = m_sample.length;
	}
}