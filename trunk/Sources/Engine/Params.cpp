#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2011  Alexandre LAURENT

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

#include "Params.h"

#include <map>
#include <string>

#include "Utils/Logger.h"

void Params :: add(const std::string& name, const std::string& value)
{
	if ( this->exists(name) )
	{
		LWarning << "Params will overwrite key '" << name << "'";
	}

	params[name] = value;
}

void Params :: remove(const std::string& name)
{
	if ( this->exists(name) )
	{
		params.erase(name);
	}
	// else silently ignored
}

bool Params :: exists(const std::string& name)const
{
	if ( params.find(name) != params.end() )
	{
		return true;
	}

	return false;
}

const std::string& Params :: get(const std::string& name)const
{
	std::map < std::string, std::string >::const_iterator itParam = params.find(name);
	if ( itParam == params.end() )
	{
		throw ParameterNotFoundParamsException(name);
	}

	return itParam->second;
}