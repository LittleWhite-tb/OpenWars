#ifndef __PARAMS_H__
#define __PARAMS_H__

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
#include <map>
#include <sstream>

#include "Utils/Logger.h"
#include "Utils/Exceptions/ParamsException.h"

class Params
{
private:

    std::map < std::string, std::string > params;   /*!< */

public:

    void add(const std::string& name, const std::string& value);
    void remove(const std::string& name);

    bool exists(const std::string& name)const;

    const std::string& get(const std::string& name)const;

    template <typename T>
    T getAs(const std::string& name)const
    {
        std::stringstream ss (this->get(name)); // Can throw ParameterNotFoundParamsException
        T value;

        ss >> value;

        return value;
    }

    template <>
    char getAs<char>(const std::string& name)const
    {
        std::string charString(this->get(name)); // Can throw ParameterNotFoundParamsException
        if ( charString.size() != 1 )
        {
            throw InvalidConvertionParamsException(name);
        }

        return charString[0];
    }

    template <typename T>
    T getAs(const std::string& name, const T defaultValue)const
    {
        std::string valueString;
        try
        {
            valueString = this->get(name);
        }
        catch (ParameterNotFoundParamsException& )
        {
            return defaultValue;
        }

        std::stringstream ss(valueString);
        T value;

        ss >> value;

        return value;
    }
};

/*! \class Params Params.h "Game/Params.h"
 *  \brief A list of values identified by a name
 *  The values are kept as string but can easily be converted
 */

/*! \fn void Params :: add(const std::string& name, const std::string& value)
 *  \brief Adds a new value corresponding to name
 *  \param name
 *  \param value
 */

/*! \fn void Params :: remove(const std::string& name);
 *  \brief Removes the value corresponding to name
 *  \param name
 */

/*! \fn bool Params :: exists(const std::string& name)const;
 *  \brief Checks if a value named name exists
 *  \param name
 *  \return true if a value named name exists
 */

/*! \fn const std::string& Params :: get(const std::string& name)const;
 *  \brief Gets the value named name
 *  \param name
 *  \return
 *  No convertion is done, the value is returned as it is
 *  ParameterNotFoundParamsException is thrown if the name is not found
 */

/*! \fn T Params :: getAs(const std::string& name)const
 *  \brief Gets the value named name
 *  \param name
 *  \return
 *  ParameterNotFoundParamsException is thrown if the name is not found
 */

/*! \fn T Params :: getAs(const std::string& name, const T defaultValue)const
 *  \brief Gets the value named name
 *  \param name
 *  \param defaultValue
 *  \return if the name is not found, the defaultValue is returned
 */

#endif
