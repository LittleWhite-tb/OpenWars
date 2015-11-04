#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game similar to Advance Wars (c)
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/OpenWars
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "ConstructionIGS.h"

#include "NEngine/NEngine.h"
#include "NEngine/Exceptions/ConstructionFailedException.h"

#include "Engine/Params.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Cursor.h"
#include "Game/GameState/GameObjects/GameInfo.h"

#include "UI/ConstructBox.h"

ConstructionIGS :: ConstructionIGS(Map* pMap, const Camera* pCamera, Cursor* pCursor, GameInfo* pGameInfo)
	:InGameState(pMap,pCamera,pCursor,pGameInfo)
{
	std::list<const Tile* > tilesList;
    pMap->getTheme()->getTilesList(&tilesList);

    std::list<const UnitTemplateFactionList* > unitsList;
    pMap->getTheme()->getUnitsList(&unitsList);

    // Construct all the contruction boxes needed by going throw the tile list
    for ( std::list < const Tile* >::const_iterator itPTile = tilesList.begin() ;
                itPTile != tilesList.end() ; ++itPTile )
    {
        const Params* tileParams = (*itPTile)->getParams();
        // For each unique producer name (if existing)
        if ( tileParams->exists("producerName") &&
             constructionBoxes.find(tileParams->get("producerName")) == constructionBoxes.end() )
        {
            constructionBoxes[tileParams->get("producerName")] = new ConstructBox(pMap->getTheme());
        }
    }

    // For each unit, we get the tile indicated where the unit is produced
    // If not existing, the loading fails
    for ( std::list < const UnitTemplateFactionList* >::const_iterator itPUnit = unitsList.begin() ;
              itPUnit != unitsList.end() ; ++itPUnit )
    {
        const Params* unitParams = (*itPUnit)->get(0)->getParams();

        if ( unitParams->exists("producedIn") )
        {
            if ( constructionBoxes.find(unitParams->get("producedIn")) != constructionBoxes.end() )
            {
                constructionBoxes[unitParams->get("producedIn")]->add(*itPUnit);
            }
            else
            {
                NEError << "A unit is producable in a tile (producer) not existing -> '" << (*itPUnit)->get(0)->getParams()->get("producedIn") << "'\n";
				throw ConstructionFailedException("ConstructionIGS");
            }
        }
    }
}

ConstructionIGS :: ~ConstructionIGS()
{
	for ( std::map<std::string, ConstructBox*>::iterator itPCB = constructionBoxes.begin() ; itPCB != constructionBoxes.end() ; ++itPCB )
    {
        delete itPCB->second;
    }
}

bool ConstructionIGS :: draw(NE::Renderer* pRenderer, unsigned int time)
{
    // We can draw it
	return constructionBoxes[pCursor->getTileUnderCursor()->getParams()->get("producerName")]->draw(*pRenderer,pGameInfo->getCurrentFaction(),pGameInfo->getFactionMoney()->getMoney(),time);
}

IGState ConstructionIGS :: update(NE::InputManager* pInputManager, unsigned int time)
{
	(void) time;

	// Some protections
    if ( !pCursor->getTileUnderCursor()->getParams()->exists("producerName") )
    {
        NEWarning << "Tile '" << pCursor->getTileUnderCursor()->getInternalName() << "' selected for construction but not having a producer name\n";
        return IGS_Idle;
    }

    if ( constructionBoxes.find(pCursor->getTileUnderCursor()->getParams()->get("producerName")) == constructionBoxes.end() )
    {
        NEWarning << "Tile '" << pCursor->getTileUnderCursor()->getInternalName() << "' does not have a producerName known\n";
        return IGS_Idle;
    }

    // We can update it
    constructionBoxes[pCursor->getTileUnderCursor()->getParams()->get("producerName")]->update(pInputManager->getDirectionsPressed(0));
    if ( pInputManager->getButtonState(0,NE::InputManager::INPUT_X) == NE::InputManager::BS_JUSTPRESSED )
    {
		const std::string& unitInternalName = constructionBoxes[pCursor->getTileUnderCursor()->getParams()->get("producerName")]->getUnitSelected(pGameInfo->getCurrentFaction())->getInternalName();
		if ( pGameInfo->getFactionMoney()->buy(pMap->getTheme()->getUnit(unitInternalName,pGameInfo->getCurrentFaction())))
		{
			pMap->setUnit(pCursor->getPosition(),unitInternalName,pGameInfo->getCurrentFaction());
			pMap->getUnit(pCursor->getPosition())->state=US_DONE;
		}

        return IGS_Idle;
    }
	if ( pInputManager->getButtonState(0,NE::InputManager::INPUT_Y) == NE::InputManager::BS_JUSTPRESSED )
	{
		return IGS_Idle;
	}

	return IGS_Construction;
}
