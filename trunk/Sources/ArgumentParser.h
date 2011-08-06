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

class MissingOptionException : public std::exception
{
private:
	std::string message;	/*!< error message to display */

public:
	MissingOptionException():message("The option is found but nothing valid is following it") {}
	MissingOptionException(const std::string& optionName):message("The option " + optionName + " is found but nothing valid is following it") {}
    virtual ~MissingOptionException(void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};

class OptionNotFoundException : public std::exception
{
private:
	std::string message;	/*!< error message to display */

public:
	OptionNotFoundException():message("The option is not found") {}
	OptionNotFoundException(const std::string& shortOptionName, const std::string& longOptionName=""):message("The options (" + shortOptionName + ";" + longOptionName + ") is not found") {}
    virtual ~OptionNotFoundException(void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};


#endif