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

#include "Unit.h"

#include <cassert>

Unit* UnitFactory(const UnitType type)
{
	switch (type)
	{
		case UT_NO_UNIT:
			return new Unit();
			break;

		case UT_R_INFANTRY:
		case UT_B_INFANTRY:
		case UT_G_INFANTRY:
		case UT_Y_INFANTRY:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND,3,1,3);
			break;

		case UT_R_BAZOOKA:
		case UT_B_BAZOOKA:
		case UT_G_BAZOOKA:
		case UT_Y_BAZOOKA:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND,2,1,3);
			break;

		case UT_R_RECON:
		case UT_B_RECON:
		case UT_G_RECON:
		case UT_Y_RECON:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND,6,2,5);
			break;

		case UT_R_TANK:
		case UT_B_TANK:
		case UT_G_TANK:
		case UT_Y_TANK:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND,5,2,5);
			break;

		case UT_R_TANKM:
		case UT_B_TANKM:
		case UT_G_TANKM:
		case UT_Y_TANKM:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND,4,3,5);
			break;

		case UT_R_NEOTANK:
		case UT_B_NEOTANK:
		case UT_G_NEOTANK:
		case UT_Y_NEOTANK:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND,5,4,5);
			break;

		case UT_R_ANTIAIR:
		case UT_B_ANTIAIR:
		case UT_G_ANTIAIR:
		case UT_Y_ANTIAIR:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND | Unit::UC_AIR,5,2,5);
			break;

		case UT_R_ARTILLERY:
		case UT_B_ARTILLERY:
		case UT_G_ARTILLERY:
		case UT_Y_ARTILLERY:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND,3,2,5);
			// ToDo, sub class for attack overloading
			break;

		case UT_R_ROCKETS:
		case UT_B_ROCKETS:
		case UT_G_ROCKETS:
		case UT_Y_ROCKETS:
			return new Unit(type,Unit::UC_LAND,Unit::UC_LAND,3,2,5);
			// ToDo, sub class for attack overloading
			break;

		case UT_R_MISSILES:
		case UT_B_MISSILES:
		case UT_G_MISSILES:
		case UT_Y_MISSILES:
			return new Unit(type,Unit::UC_LAND,Unit::UC_AIR,3,2,5);
			// ToDo, sub class for attack overloading
			break;

		case UT_R_APC:
		case UT_B_APC:
		case UT_G_APC:
		case UT_Y_APC:
			return new Unit(type,Unit::UC_LAND,Unit::UC_NONE,4,2,0);
			// ToDo, sub class for transport
			break;


		case UT_R_LANDER:
		case UT_B_LANDER:
		case UT_G_LANDER:
		case UT_Y_LANDER:
			return new Unit(type,Unit::UC_LAND,Unit::UC_NONE,3,2,0);
			// ToDo, sub class for transport
			break;

		case UT_R_SUB:
		case UT_B_SUB:
		case UT_G_SUB:
		case UT_Y_SUB:
			return new Unit(type,Unit::UC_NAVY,Unit::UC_NAVY,3,2,0);
			// ToDo, sub class for submarine
			break;

		case UT_R_BOMBERSHIP:
		case UT_B_BOMBERSHIP:
		case UT_G_BOMBERSHIP:
		case UT_Y_BOMBERSHIP:
			return new Unit(type,Unit::UC_NAVY,Unit::UC_NAVY | Unit::UC_LAND ,4,2,5);
			// ToDo, sub class for attack by range
			break;

		case UT_R_CRUISER:
		case UT_B_CRUISER:
		case UT_G_CRUISER:
		case UT_Y_CRUISER:
			return new Unit(type,Unit::UC_NAVY,Unit::UC_NAVY | Unit::UC_AIR ,4,2,5);
			// ToDO -> sub class for transport ( copter )
			break;

		case UT_R_TCOPTER:
		case UT_B_TCOPTER:
		case UT_G_TCOPTER:
		case UT_Y_TCOPTER:
			return new Unit(type,Unit::UC_AIR,Unit::UC_NONE,6,5,0);
			// ToDO -> sub class for transport copter
			break;

		case UT_R_COPTER:
		case UT_B_COPTER:
		case UT_G_COPTER:
		case UT_Y_COPTER:
			return new Unit(type,Unit::UC_AIR,Unit::UC_AIR | Unit::UC_LAND,6,5,5);
			break;

		case UT_R_FIGHTER:
		case UT_B_FIGHTER:
		case UT_G_FIGHTER:
		case UT_Y_FIGHTER:
			return new Unit(type,Unit::UC_AIR,Unit::UC_AIR,7,5,5);
			break;

		case UT_R_BOMBER:
		case UT_B_BOMBER:
		case UT_G_BOMBER:
		case UT_Y_BOMBER:
			return new Unit(type,Unit::UC_AIR,Unit::UC_LAND,7,5,5);
			break;
	}

	assert(0);
	return new Unit();
}

const std::string parseName(const UnitType unitType)
{
	switch (unitType)
	{
		case UT_NO_UNIT:
			return "Eraser";
			break;

		case UT_R_INFANTRY:
		case UT_B_INFANTRY:
		case UT_G_INFANTRY:
		case UT_Y_INFANTRY:
			return "Inftry";
			break;

		case UT_R_BAZOOKA:
		case UT_B_BAZOOKA:
		case UT_G_BAZOOKA:
		case UT_Y_BAZOOKA:
			return "Mech";
			break;

		case UT_R_RECON:
		case UT_B_RECON:
		case UT_G_RECON:
		case UT_Y_RECON:
			return "Recon";
			break;

		case UT_R_TANK:
		case UT_B_TANK:
		case UT_G_TANK:
		case UT_Y_TANK:
			return "Tank";
			break;

		case UT_R_TANKM:
		case UT_B_TANKM:
		case UT_G_TANKM:
		case UT_Y_TANKM:
			return "Md Tank";
			break;

		case UT_R_NEOTANK:
		case UT_B_NEOTANK:
		case UT_G_NEOTANK:
		case UT_Y_NEOTANK:
			return "Neo";
			break;

		case UT_R_ANTIAIR:
		case UT_B_ANTIAIR:
		case UT_G_ANTIAIR:
		case UT_Y_ANTIAIR:
			return "A-air";
			break;

		case UT_R_ARTILLERY:
		case UT_B_ARTILLERY:
		case UT_G_ARTILLERY:
		case UT_Y_ARTILLERY:
			return "Artly";
			break;

		case UT_R_ROCKETS:
		case UT_B_ROCKETS:
		case UT_G_ROCKETS:
		case UT_Y_ROCKETS:
			return "Rckts";
			break;

		case UT_R_MISSILES:
		case UT_B_MISSILES:
		case UT_G_MISSILES:
		case UT_Y_MISSILES:
			return "Mssls";
			break;

		case UT_R_APC:
		case UT_B_APC:
		case UT_G_APC:
		case UT_Y_APC:
			return "APC";
			break;


		case UT_R_LANDER:
		case UT_B_LANDER:
		case UT_G_LANDER:
		case UT_Y_LANDER:
			return "Lndr";
			break;

		case UT_R_SUB:
		case UT_B_SUB:
		case UT_G_SUB:
		case UT_Y_SUB:
			return "Sub";
			break;

		case UT_R_BOMBERSHIP:
		case UT_B_BOMBERSHIP:
		case UT_G_BOMBERSHIP:
		case UT_Y_BOMBERSHIP:
			return "BShp";
			break;

		case UT_R_CRUISER:
		case UT_B_CRUISER:
		case UT_G_CRUISER:
		case UT_Y_CRUISER:
			return "Crsr";
			break;

		case UT_R_TCOPTER:
		case UT_B_TCOPTER:
		case UT_G_TCOPTER:
		case UT_Y_TCOPTER:
			return "T Cptr";
			break;

		case UT_R_COPTER:
		case UT_B_COPTER:
		case UT_G_COPTER:
		case UT_Y_COPTER:
			return "B Cptr";
			break;

		case UT_R_FIGHTER:
		case UT_B_FIGHTER:
		case UT_G_FIGHTER:
		case UT_Y_FIGHTER:
			return "Fghtr";
			break;

		case UT_R_BOMBER:
		case UT_B_BOMBER:
		case UT_G_BOMBER:
		case UT_Y_BOMBER:
			return "Bmbr";
			break;
	}

	assert(0);
	return "";
}