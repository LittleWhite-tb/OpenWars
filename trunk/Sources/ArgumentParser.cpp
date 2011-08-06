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

#include "ArgumentParser.h"

#include <cassert>

ArgumentParser :: ArgumentParser(int argc, char** argv)
{
	assert(argv);

	for ( int i = 1 ; i < argc ; i++ )	// Start at 1 to skip the program name
	{
		assert(argv[i]); // We have a huge problem here, since it should not occur at all
		args.push_back(std::string(argv[i]));
	}
}

const std::string& ArgumentParser :: parseArgument(const std::string& shortOptionName, const std::string& longOptionName)const
{
	unsigned int i = 0;
	std::string optionAvailable = "";

	for(i = 0 ; i < args.size() ; i++ )
	{
		if ( args[i] == shortOptionName )
		{
			optionAvailable = shortOptionName;
			break;	// Ends the research when we have it
		}
		else if ( args[i] == longOptionName )
		{
			optionAvailable = longOptionName;
			break;	// Ends the research when we have it
		}
	}
	
	// Check if the option is in the arguments
	if ( i == args.size() )
	{
		throw OptionNotFoundException(shortOptionName,longOptionName);
	}
	else
	{
		if ( i+1 >= args.size() || args[i+1][0] == '-' )	// If we have nothing after, of if the next argument is an option
		{
			throw MissingOptionException(optionAvailable);
		}
		else
		{
			return args[i+1];
		}
	}
}

const std::string& ArgumentParser :: getArgument(const std::string& shortOptionName, const std::string& longOptionName)const
{
	return this->parseArgument(shortOptionName, longOptionName);
}

bool ArgumentParser :: isPresent(const std::string& shortOptionName, const std::string& longOptionName)const
{
	try
	{
		this->parseArgument(shortOptionName, longOptionName);
	}
	catch ( OptionNotFoundException& onfe )
	{
		(onfe);
		 return false;
	}
	catch ( MissingOptionException& moe )
	{
		(moe);
		// We don't mind ; we are just catching it to not see it in a higher level
	}
	
	return true;
}