#include "MapGame.h"

#include "../Engine/Renderer.h"
#include "../Engine/ResourcesManager/SpriteManager.h"
#include "../Game/Camera.h"

#include "../Utils/Scaler.h"
#include "../Utils/Logger.h"

#include "../globals.h"

MapGame :: MapGame(SpriteManager& sm, const std::string& fileName):Map(sm,fileName)
{
	unitMap = new Unit**[this->height];
	if ( unitMap == NULL )
	{
		LError << "Fail to allocate memory for the unit map";
		valid = false;
		return;
	}

	for (unsigned int y = 0 ; y < this->height ; y++ )
	{
		unitMap[y] = new Unit*[this->width];
		if ( unitMap[y] == NULL)
		{
			LError << "Fail to allocate memory for the unit map (y=" << y << ")";
			valid = false;
			// It's smelling good the memory leak ...
			delete [] unitMap;
			return;
		}

		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			unitMap[y][x] = NULL;
		}
	}

	LDebug << "MapGame created";
}

MapGame :: ~MapGame()
{
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			delete unitMap[y][x];
		}

		delete[] unitMap[y];
	}

	delete[] unitMap;
}

void MapGame :: enableUnits(void)
{
    for ( unsigned int y = 0 ; y < height ; y++ )
	{
		for ( unsigned int x = 0 ; x < width ; x++ )
		{
            unitMap[y][x]->enabled = true;
        }
    }
}

bool MapGame :: draw(const Renderer& r, const Camera& c, const unsigned int time)
{
	UVec2 cameraPosition = c.getPosition();
	UVec2 mapOffset = Scaler::getOffset();
	IVec2 tilePos(0,mapOffset.y);
	bool bError = true;

	LDebug << "Map :: draw";

	this->drawTerrain(r,c,time);

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = mapOffset.x;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = tilesSet[map[y][x]].pASprite->getHeight() - (static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_DEFAULT_HEIGHT));

			// Apply offset
			tilePos.y -= yOffset;

			if ( unitViewMap[y][x] != UT_NO_UNIT )	// If we have a unit
			{
                if ( unitMap[y][x]->enabled )
                {
                    bError &= r.drawTile(*unitsSet[unitViewMap[y][x]].pASprite,tilePos,time);
                }
                else
                {
                    static const SDL_Colour mask = {128,128,128,255};
                    
                    bError &= r.drawTile(*unitsSet[unitViewMap[y][x]].pASprite,tilePos,mask);
                }
			}
			tilePos.x += tilesSet[map[y][x]].pASprite->getWidth();

			// Remove offset ( to not affect other sprite )
			tilePos.y += yOffset;
		}

		// To put 0 here, can be a bit dangerous
		tilePos.y += (static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_DEFAULT_HEIGHT));
	}

	return bError;
}

bool MapGame :: setTile(const UVec2& position, const UnitType unitType)
{
	unitViewMap[position.y][position.x] = unitType;
	if ( unitMap[position.y][position.x] != NULL )
	{
		delete unitMap[position.y][position.x];
	}

	unitMap[position.y][position.x] = new Unit(unitType, unitsSet[unitType]);

	return true;
}