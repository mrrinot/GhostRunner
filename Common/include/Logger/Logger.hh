#pragma once

//
//
// To improve :
// - Add collapse mode (Items are counted and shown only once with number of occurrences)
// - Add buffered mode with a flush method.
// - Add formatting depending on DebugLevel
//
//

#ifndef LOGGER_HH_
#define LOGGER_HH_

#include "LoggerOptions.hh"
#include "LogHandler.hh"

class Logger
{
public:
  Logger();
  Logger(const LoggerOptions& options);
  ~Logger();

public:
  LoggerOptions getLocalOptions() const;

  LogHandler  logDebug5();
  LogHandler  logDebug4();
  LogHandler  logDebug3();
  LogHandler  logDebug2();
  LogHandler  logDebug1();
  LogHandler  logDebug();
  LogHandler  logInfo();
  LogHandler  logWarning();
  LogHandler  logError();

private:
  LoggerOptions _localOptions;

private:
  LogHandler::FuncType  generateHandler(LogLevel levelToLog);

  // Static
private:
  static LoggerOptions _globalOptions;

public:
  static LoggerOptions  getGlobalOptions();
  static void           setGlobalOptions(const LoggerOptions& options);

  static Logger& getLogger();
};

#define LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(suffix) \
inline auto Log ## suffix() -> decltype(Logger::getLogger().log ## suffix()) \
{ \
  return Logger::getLogger().log ## suffix(); \
}
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Debug5)
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Debug4)
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Debug3)
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Debug2)
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Debug1)
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Debug)
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Info)
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Warning)
LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION(Error)

#undef LOGGER_GENERATE_INLINE_SHORTCUT_FUNCTION

#endif // LOGGER_HH_