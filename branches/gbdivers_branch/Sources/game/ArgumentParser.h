#ifndef __ARGUMENTPARSER_H__
#define __ARGUMENTPARSER_H__

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

#include <string>
#include <vector>
#include <sstream>

#include <NEngine/Exception.h>

class ArgumentParser
{
private:
	std::vector<std::string> args;

	const std::string& parseArgument(const std::string& shortOptionName, const std::string& longOptionName="")const;

public:
	ArgumentParser(int argc, char** argv);

	const std::string& getArgument(const std::string& shortOptionName, const std::string& longOptionName="")const;
	bool isPresent(const std::string& shortOptionName, const std::string& longOptionName="")const;

	template <typename T>
	T getAs(const std::string& shortOptionName, const std::string& longOptionName="")const
	{
		std::stringstream ss(this->parseArgument(shortOptionName, longOptionName)); // Throw exception
		T optionValue;
		
		ss >> optionValue;
		
		return optionValue;
	}
};

class MissingOptionException : public Exception
{
public:
	MissingOptionException():Exception("The option is found but nothing valid is following it") {}
	MissingOptionException(const std::string& optionName):Exception("The option " + optionName + " is found but nothing valid is following it") {}
};

class OptionNotFoundException : public Exception
{
public:
	OptionNotFoundException():Exception("The option is not found") {}
	OptionNotFoundException(const std::string& shortOptionName, const std::string& longOptionName=""):Exception("The options (" + shortOptionName + ";" + longOptionName + ") is not found") {}

};

/*! \class ArgumentParser ArgumentParser.h "ArgumentParser.h"
 *  \brief Class to parse the arguments from the command line
 */

/*! \fn ArgumentParser :: ArgumentParser(int argc, char** argv)
 *	\brief Put all the arguments in a list
 *	\param argc the number of arguments
 *	\param argv the arguments
 */

/*!	\fn const std::string& ArgumentParser :: parseArgument(const std::string& shortOptionName, const std::string& longOptionName="")const
 *	\brief Check if either the short or long argument are present. If one is, return the next argument (the parameter for the argument)
 *	\param shortOptionName the short name of the argument to search
 *	\param longOptionName the long name of the argument to search
 *	\return the argument following the argument found
 */

/*!	\fn const std::string& ArgumentParser :: getArgument(const std::string& shortOptionName, const std::string& longOptionName="")const
 *	\brief Get the argument following the option passed
 *	\param shortOptionName the short name of the argument to search
 *	\param longOptionName the long name of the argument to search
 *	\return the argument following the argument found
 */

/*!	\fn bool ArgumentParser :: isPresent(const std::string& shortOptionName, const std::string& longOptionName="")const
 *	\brief Check if the option is present
 *	\param shortOptionName the short name of the argument to search
 *	\param longOptionName the long name of the argument to search
 *	\return true if the option if present
 */

/*!	\fn T ArgumentParser :: getAs(const std::string& shortOptionName, const std::string& longOptionName="")const
 *	\brief Get the argument as T for the option name given
 *	\param shortOptionName the short name of the argument to search
 *	\param longOptionName the long name of the argument to search
 *	\return returns the argument converted to the type wanted
 */


/*! \class MissingOptionException ArgumentParser.h "ArgumentParser.h"
 *  \brief Exception thrown when no valid argument is following the option
 */

/*! \fn MissingOptionException::MissingOptionException()
 *	\brief Create a message of the format: "The option is found but nothing valid is following it"
 */

/*! \fn MissingOptionException::MissingOptionException(const std::string& optionName)
 *	\brief Create a message of the format: "The option + optionName + is found but nothing valid is following it"
 *	\param optionName the name of the option searched
 */


/*! \class OptionNotFoundException ArgumentParser.h "ArgumentParser.h"
 *  \brief Exception thrown when the option wanted is not found
 */

/*! \fn OptionNotFoundException::OptionNotFoundException()
 *	\brief Create a message of the format: "The option is not found"
 */

/*! \fn OptionNotFoundException::OptionNotFoundException(const std::string& shortOptionName, const std::string& longOptionName="")
 *	\brief Create a message of the format: "The options ( + shortOptionName + ; + longOptionName + ) is not found"
 *	\param shortOptionName the short name of the option searched
 *	\param longOptionName the long name of the option searched
 */

#endif
