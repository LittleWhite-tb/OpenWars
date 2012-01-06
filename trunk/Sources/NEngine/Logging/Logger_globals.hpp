#ifndef LOGGER_GLOBALS_HPP
#define LOGGER_GLOBALS_HPP

/** \file Logger_globals.hpp
 * Brings some help to use the Logger<br>
 * Four message priority are defined to be passed to the <a>Logger::setLevel()</a> function<br>
 * Four macros are defined to log easily the messages, without worrying about the level priority<br>
 * \sa Logger
 */

const int LL_Info = 0;          /*!< Lower message priority (i.e. "Logger Init")*/
const int LL_Debug = 1;         /*!< Debug message priority (i.e. "TODO: Fix the bug") */
const int LL_Warning = 2;       /*!< Warning message priority (i.e. "You are badly using this") */
const int LL_Error = 3;         /*!< Error message priority (i.e. "Fatal error occured") */

#define LDebug(logger) logger.setLevel(LL_Debug);logger          /*!< shortcut to send debug messages */
#define LWarning(logger) logger.setLevel(LL_Warning);logger      /*!< shortcut to send warning messages */
#define LError(logger) logger.setLevel(LL_Error);logger          /*!< shortcut to send error messages */
#define Log(logger,level) logger.setLevel(level);logger          /*!< shortcut to send log message with specified importancy level */

#endif
