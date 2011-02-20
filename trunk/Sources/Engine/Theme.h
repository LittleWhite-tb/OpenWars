#ifndef __THEME_H__
#define __THEME_H__

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

#include <string>
#include <map>

#include "../Game/Tile.h"
#include "../Game/Unit.h"
#include "../UI/UIType.h"


namespace NE { class SpriteLoader; }
class AnimatedSprite;
class LineParser;

class Theme
{
private:

    std::string name;
    std::map<TileType, AnimatedSprite*> tiles;
    std::map<UnitType, AnimatedSprite*> units;
    std::map<UIType, AnimatedSprite*> ui;

    AnimatedSprite* loadFromThemeFile(NE::SpriteLoader* const pSL, LineParser& lpTiles, const std::string& subFolder, const int number, int* pSpriteID);

    template <typename T>
    bool loadSprites(NE::SpriteLoader* const pSL, LineParser& lpTiles, const std::string& subFolder, std::map<T, AnimatedSprite*>& bank, T final)
    {
        for ( int i = 0 ; i < final ; i++ )
        {
            int spriteID = 0;

            AnimatedSprite* pASprite = this->loadFromThemeFile(pSL,lpTiles,subFolder,static_cast<int>(final), &spriteID);
            T type = static_cast<T>(spriteID);
            bank[type] = NULL;

            if ( pASprite == NULL )
            {
                return false;
            }

            bank[type] = pASprite;
        }

        return true;
    }

public:
    Theme(const std::string& name):name(name) {}
    ~Theme(void);

    bool load(NE::SpriteLoader* const pSL);
    AnimatedSprite* getTile(const TileType tType);
    AnimatedSprite* getUnit(const UnitType uType);
    AnimatedSprite* getUI(const UIType uType);

    std::string& getName() { return name; }
};

#endif
