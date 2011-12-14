#ifndef LOGGERMESSAGE_HPP
#define LOGGERMESSAGE_HPP

#include <string>
#include <cstdarg>

namespace NE
{


    enum LogLevel
    {
        LL_Info = 0,
        LL_Debug = 1,
        LL_Warning = 2,
        LL_Error = 3
    };

    struct LoggerMessage
    {
        int level;
        std::string format;
        va_list* messages;

        std::string formatedMessage;

        LoggerMessage(int level, const std::string& format, va_list* messages)
            :level(level),format(format)
        {
            this->messages = messages;
            // va_copy(this->messages,messages);
        }
    /*
        LoggerMessage(int level, const std::string& format, ...)
            :level(level),format(format)
        {
            va_start(messages,format);
        }
    */
    /*
        ~LoggerMessage()
        {
            va_end(messages);
        }
        */
    };
}

#endif
