#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010  Alexandre LAURENT

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

website: http://code.google.com/p/openawars/
e-mail: lw.demoscene@gmail.com
**/
#endif

#include <SDL/SDL.h>

#include "../NEngine/NETypes.h"

#include "Sprite.h"

#include "../Types/Vec2.h"

class Renderer;
class SpriteManager;

class AnimatedSprite : public Sprite
{
private:
	unsigned int widthSprite;				/*!< width of the animation */
	unsigned int heightSprite;				/*!< height of the animation */

	unsigned int numberAnimation;			/*!< number of animation in the sprite */
	unsigned int animationCounter;			/*!< number of the current animation */

	unsigned int lastUpdate;				/*!< last time that the animated sprite has been updated */

	unsigned int msInterval;				/*!< interval between two sprites of the animation */

	// Disallow the copy
	AnimatedSprite(const AnimatedSprite& as);
	void operator= (const AnimatedSprite& as);

	void update(const unsigned int time);

public:
	AnimatedSprite(SpriteManager& sm, const std::string& fileName, const unsigned int width, const unsigned int height, const unsigned int msInterval, const bool needScaling);
	~AnimatedSprite(void);

	SDL_Rect getSrcRect(const unsigned int time);

	int getWidth(void)const { return widthSprite; }
	int getHeight(void)const { return heightSprite; }

	unsigned int getInterval(void)const { return msInterval; }
	void setInterval(const unsigned int newInterval) { msInterval = newInterval; }
};

/*! \class AnimatedSprite AnimatedSprite.h "Engine/AnimatedSprite.h"
 *  \brief AnimatedSprite management class
 *
 * Inherits from the Sprite class to handle the case of set of sprites to do animation
 * Can do the following:
 *		- Load from file (directly in the constructor)
 *		- Get the width
 *		- Get the height
 *		- Get the rectangle to use to draw the correct animation
 *		- Get interval between two sprites of the animation, in milliseconds
 *		- Set interval between two sprites of the animation, in milliseconds
 */

/*! \fn void AnimatedSprite::update(const unsigned int time)
 * \brief Updates the instance to change the sprite to show if needed
 * \param time the actual time
 */

/*! \fn AnimatedSprite::AnimatedSprite(SpriteManager& sm, const std::string& fileName, const unsigned int width, const unsigned int height, const unsigned int msInterval, const bool needScaling)
 * Load the sprite set, using the SpriteManager
 * \param sm the sprite manager to use to load the image
 * \param fileName the file to load
 * \param width of the sprite
 * \param height of the sprite
 * \param msInterval interval between two sprite in milliseconds
 * \param needScaling if some scaling operation has to be done on this sprite 
 */

/*! \fn AnimatedSprite::~AnimatedSprite(void)
 */

/*! \fn SDL_Rect AnimatedSprite::getSrcRect(const unsigned int time)
 * \brief Get the source rectangle for the internal surface, to draw
 * Following the current frame, the rectangle to draw will be returned
 * \param time the actual time
 */

/*! \fn int AnimatedSprite::getWidth(void)const
 * \brief Get the width
 * \return returns the width of the sprite
 */

/*! \fn int AnimatedSprite::getHeight(void)const
 * \brief Get the height
 * \return returns the height of the sprite
 */

/*! \fn unsigned int AnimatedSprite::getInterval(void)const
 * \brief Get the interval between two frames
 * \return returns the interval in millisecond
 */

/*! \fn void AnimatedSprite::setInterval(const unsigned int newInterval)
 * \brief Set the interval between two frames
 * \param newInterval the new interval in millisecond
 */

#endif
