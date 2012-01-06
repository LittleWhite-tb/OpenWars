#ifndef SIMPLEFORMATER_HPP
#define SIMPLEFORMATER_HPP

#include "LoggerFormater.hpp"

namespace NE
{
    class SimpleFormater : public NE::LoggerFormater
    {
        protected:
            /*! \brief Format the input <i>message</i> to be outputted exactly the same
             *  \param level the priority level (unused here)
             *  \param message
             *  \return the new formed message (just a copy of message as a std::string)
             */
            std::string format(int level, const std::string& message)
            {
                return message;
            }
    };
}

/*! \class NE::SimpleFormater SimpleFormater.hpp Logging/Formater/SimpleFormater.hpp
 *  \brief Formater letting the information passing through without any changes
 *  \sa Logger
 */

#endif
