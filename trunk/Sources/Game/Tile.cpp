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

#include "tile.h"

#include <cassert>

#include "../Utils/Logger.h"
#include "../globals.h"

#ifdef _DEBUG
	extern unsigned int nbTAllocation;
	extern unsigned int nbTDestruction;
#endif

Tile :: Tile(void):tileType(TT_Invalid),defence(0),isRoad(false),isBridge(false),isRiver(false),isSee(true),isBeach(false),isBuilding(false),needBackground(false),cityLife(0)
{
#ifdef _DEBUG
	nbTAllocation++; 
#endif
}

Tile :: Tile(const TileType tileType, const unsigned char defence, const bool isRoad, const bool isBridge, const bool isRiver, const bool isSee, const bool isBeach, const bool isBuilding, const bool needBackground, const unsigned char cityLife)
		:tileType(tileType),defence(defence),isRoad(isRoad),isBridge(isBridge),isRiver(isRiver),isSee(isSee),isBeach(isBeach),isBuilding(isBuilding),needBackground(needBackground),cityLife(cityLife) 
{ 
#ifdef _DEBUG
	nbTAllocation++; 
#endif
}

Tile :: Tile(const Tile& t)
	:tileType(t.tileType),defence(t.defence),isRoad(t.isRoad),isBridge(t.isBridge),isRiver(t.isRiver),isSee(t.isSee),isBeach(t.isBeach),isBuilding(t.isBuilding),needBackground(t.needBackground),cityLife(t.cityLife)
{
#ifdef _DEBUG
	nbTAllocation++; 
#endif
}

Tile& Tile :: operator=(const Tile& t)
{
	this->tileType = t.tileType;
	this->defence = t.defence;
	this->isRoad = t.isRoad;
	this->isBridge = t.isBridge;
	this->isRiver = t.isRiver;
	this->isSee = t.isSee;
	this->isBeach = t.isBeach;
	this->isBuilding = t.isBuilding;
	this->needBackground = t.needBackground;
	this->cityLife = t.cityLife;

#ifdef _DEBUG
	//nbTAllocation++; 
#endif

	return *this;
}

Tile :: ~Tile(void)
{
#ifdef _DEBUG
	nbTDestruction++; 
#endif
}

unsigned char parseDefence(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_Coast:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_River_X:
			return 0;
			break;
		case TT_Plain:
		case TT_Reef:
			return 1;
			break;
		case TT_Tree:
			return 2;
			break;
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
			return 3;
			break;
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Red_HQ:
		case TT_Blue_HQ:
		case TT_Green_HQ:
		case TT_Yellow_HQ:
			return 4;
			break;
	}

	assert(0);
	return 0;
}

bool parseIsRoad(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Plain:
		case TT_Tree:
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_River_X:
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Reef:
		case TT_Coast:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
		case TT_Bridge_H:
		case TT_Bridge_V:
			return false;
			break;
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
			return true;
			break; 
	}

	assert(0);
	return false;
}

bool parseIsBridge(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Plain:
		case TT_Tree:
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_River_X:
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Reef:
		case TT_Coast:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
			return false;
			break;
		case TT_Bridge_H:
		case TT_Bridge_V:
			return true;
			break; 
	}

	assert(0);
	return false;
}


bool parseIsRiver(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Plain:
		case TT_Tree:
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Reef:
		case TT_Coast:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_Bridge_H:
		case TT_Bridge_V:
			return false;
			break;
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_River_X:
			return true;
			break; 
	}

	assert(0);
	return false;
}

bool parseIsSea(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Plain:
		case TT_Tree:
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_X:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
			return false;
			break;
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Reef:
		case TT_Coast:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
			return true;
	}

	assert(0);
	return false;
}

bool parseIsBeach(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Plain:
		case TT_Tree:
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_X:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Reef:
		case TT_Coast:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
			return false;
			break;
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
			return true;
	}

	assert(0);
	return false;
}

bool parseIsBuilding(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Plain:
		case TT_Tree:
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_River_X:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Road_X:
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Reef:
		case TT_Coast:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
			return false;
			break;
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
			return true;
			break;
	}

	assert(0);
	return false;
}

bool parseNeedBackground(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Tree:
		case TT_Mountain_2:
		case TT_Coast:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
			return true;
			break;
		case TT_Plain:
		case TT_Mountain_1:
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_River_X:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Reef:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
			return false;
	}

	assert(0);
	return false;
}

bool parseIsHQ(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Red_HQ:
		case TT_Blue_HQ:
		case TT_Green_HQ:
		case TT_Yellow_HQ:
			return true;
			break;
		case TT_Tree:
		case TT_Mountain_2:
		case TT_Coast:
		case TT_Road_TL:
		case TT_Road_TR:
		case TT_Road_BL:
		case TT_Road_BR:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
		case TT_Plain:
		case TT_Mountain_1:
		case TT_Beach_TL:
		case TT_Beach_TL_R:
		case TT_Beach_TL_B:
		case TT_Beach_TL_2:
		case TT_Beach_TR:
		case TT_Beach_TR_B:
		case TT_Beach_TR_L:
		case TT_Beach_TR_2:
		case TT_Beach_BL:
		case TT_Beach_BL_T:
		case TT_Beach_BL_R:
		case TT_Beach_BL_2:
		case TT_Beach_BR:
		case TT_Beach_BR_L:
		case TT_Beach_BR_T:
		case TT_Beach_BR_2:
		case TT_Beach_EL:
		case TT_Beach_ER:
		case TT_Beach_ET:
		case TT_Beach_EB:
		case TT_Beach_T:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_2:
		case TT_Beach_B:
		case TT_Beach_B_R:
		case TT_Beach_B_L:
		case TT_Beach_B_2:
		case TT_Beach_L:
		case TT_Beach_L_T:
		case TT_Beach_L_B:
		case TT_Beach_L_2:
		case TT_Beach_R:
		case TT_Beach_R_T:
		case TT_Beach_R_B:
		case TT_Beach_R_2:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_See_T:
		case TT_River_See_B:
		case TT_River_See_L:
		case TT_River_See_R:
		case TT_River_X:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_Sea:
		case TT_Sea_TL:
		case TT_Sea_TR:
		case TT_Sea_BL:
		case TT_Sea_BR:
		case TT_Reef:
		case TT_Coast_ET:
		case TT_Coast_EB:
		case TT_Coast_EL:
		case TT_Coast_ER:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_RTL:
		case TT_Coast_RTR:
		case TT_Coast_RBL:
		case TT_Coast_RBR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_T_TL:
		case TT_Coast_T_TR:
		case TT_Coast_T_BL:
		case TT_Coast_T_BR:
		case TT_Coast_T_LT:
		case TT_Coast_T_RT:
		case TT_Coast_T_LB:
		case TT_Coast_T_RB:
		case TT_Coast_X:
		case TT_Coast_XL:
		case TT_Coast_XR:
		case TT_Coast_XB:
		case TT_Coast_XT:
		case TT_Coast_XTL:
		case TT_Coast_XTR:
		case TT_Coast_XBL:
		case TT_Coast_XBR:
		case TT_Coast_XTLBR:
		case TT_Coast_XBLTR:
			return false;
	}

	assert(0);
	return false;
}

Tile TileFactory(const TileType tileType)
{
	return Tile(tileType,
				parseDefence(tileType),
				parseIsRoad(tileType),
				parseIsBridge(tileType),
				parseIsRiver(tileType),
				parseIsSea(tileType),
				parseIsBeach(tileType),
				parseNeedBackground(tileType),
				parseIsBuilding(tileType),
				20);
}