#ifndef __UNIT_H__
#define __UNIT_H__

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

enum UnitType
{
	UT_NO_UNIT = 0,

	// Red
	// Ground units
	UT_R_INFANTRY,
	UT_R_BAZOOKA,
	UT_R_RECON,
	UT_R_TANK,
	UT_R_TANKM,
	UT_R_NEOTANK,
	UT_R_APC,
	UT_R_ARTILLERY,
	UT_R_ROCKETS,
	UT_R_ANTIAIR,
	UT_R_MISSILES,				// Anti air long range

	// Navy units
	UT_R_LANDER,
	UT_R_SUB,
	UT_R_BOMBERSHIP,
	UT_R_CRUISER,

	// Air Units
	UT_R_TCOPTER,				// Transport copter
	UT_R_COPTER,
	UT_R_FIGHTER,
	UT_R_BOMBER,

	// Blue units
	// Ground units
	UT_B_INFANTRY,
	UT_B_BAZOOKA,
	UT_B_RECON,
	UT_B_TANK,
	UT_B_TANKM,
	UT_B_NEOTANK,
	UT_B_APC,
	UT_B_ARTILLERY,
	UT_B_ROCKETS,
	UT_B_ANTIAIR,
	UT_B_MISSILES,				// Anti air long range

	// Navy units
	UT_B_LANDER,
	UT_B_SUB,
	UT_B_BOMBERSHIP,
	UT_B_CRUISER,

	// Air Units
	UT_B_TCOPTER,				// Transport copter
	UT_B_COPTER,
	UT_B_FIGHTER,
	UT_B_BOMBER,

	// Green
	// Ground units
	UT_G_INFANTRY,
	UT_G_BAZOOKA,
	UT_G_RECON,
	UT_G_TANK,
	UT_G_TANKM,
	UT_G_NEOTANK,
	UT_G_APC,
	UT_G_ARTILLERY,
	UT_G_ROCKETS,
	UT_G_ANTIAIR,
	UT_G_MISSILES,				// Anti air long range

	// Navy units
	UT_G_LANDER,
	UT_G_SUB,
	UT_G_BOMBERSHIP,
	UT_G_CRUISER,

	// Air Units
	UT_G_TCOPTER,				// Transport copter
	UT_G_COPTER,
	UT_G_FIGHTER,
	UT_G_BOMBER,

	// Yellow
	// Ground units
	UT_Y_INFANTRY,
	UT_Y_BAZOOKA,
	UT_Y_RECON,
	UT_Y_TANK,
	UT_Y_TANKM,
	UT_Y_NEOTANK,
	UT_Y_APC,
	UT_Y_ARTILLERY,
	UT_Y_ROCKETS,
	UT_Y_ANTIAIR,
	UT_Y_MISSILES,				// Anti air long range

	// Navy units
	UT_Y_LANDER,
	UT_Y_SUB,
	UT_Y_BOMBERSHIP,
	UT_Y_CRUISER,

	// Air Units
	UT_Y_TCOPTER,				// Transport copter
	UT_Y_COPTER,
	UT_Y_FIGHTER,
	UT_Y_BOMBER,

	UT_END_LIST					// Stopper
};

class Unit
{
private:

	UnitType type;

	unsigned int category;
	unsigned targetCategory;

	unsigned int movement;
	unsigned int fuel;
	unsigned int fuelConsumption;
	unsigned int ammo;

	unsigned int life;

public:
	static const unsigned int UC_NONE = 0;		// For non attacking unit
	static const unsigned int UC_LAND = 1;
	static const unsigned int UC_NAVY = 2;
	static const unsigned int UC_AIR = 4;


	Unit(void):type(UT_NO_UNIT),category(UC_LAND),targetCategory(UC_LAND),movement(0),fuel(0),ammo(0),life(0) {}
	Unit(const UnitType type, const unsigned int category, const unsigned int targetCategory, const unsigned int movement, const unsigned int fuelConsumption, const unsigned int ammo)
		:type(type),category(category),targetCategory(targetCategory),movement(movement),fuel(99),fuelConsumption(fuelConsumption),ammo(ammo),life(10) {}

	virtual ~Unit(void) {}

	UnitType getType(void)const { return type; }
};

Unit* UnitFactory(const UnitType type);

#endif