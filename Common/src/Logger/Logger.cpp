#define _CRT_SECURE_NO_WARNINGS

#include "Logger/Logger.hh"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

LoggerOptions Logger::_globalOptions;

// Helpers
void replaceAllInString(std::string& str,
                        const std::string& from,
                        const std::string& to)
{
  if (from.empty())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos)
  {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

std::string addPadding(const std::string& str,
                       const std::string& toAdd,
                       unsigned int minLen)
{
  std::string result(str);
  while (result.size() < minLen)
    result = toAdd + result;
  return result;
}

std::string formatDate(const std::tm& tm, const std::string& format)
{
  std::string result(format);

  replaceAllInString(result, "%Y", std::to_string(tm.tm_year + 1900));
  replaceAllInString(result, "%m", addPadding(std::to_string(tm.tm_mon + 1), "0", 2));
  replaceAllInString(result, "%d", addPadding(std::to_string(tm.tm_mday), "0", 2));
  replaceAllInString(result, "%H", addPadding(std::to_string(tm.tm_hour), "0", 2));
  replaceAllInString(result, "%M", addPadding(std::to_string(tm.tm_min), "0", 2));
  replaceAllInString(result, "%S", addPadding(std::to_string(tm.tm_sec), "0", 2));
  return result;
}

std::string toString(const std::chrono::system_clock::time_point& time,
                     const std::string& formatting = "%Y-%m-%d %H:%M:%S")
{
  std::ostringstream stream;
  auto time_ = std::chrono::system_clock::to_time_t(time);
  stream << formatDate(*std::localtime(&time_), formatting);
  return stream.str();
}

std::string formatToLog(const std::string& str,
                        const std::string& format,
                        LogLevel level,
                        const std::chrono::system_clock::time_point& now,
                        const std::string& dateFormat = "%Y-%m-%d %H:%M:%S",
                        unsigned int count = 1)
{
  std::string result(format);

  replaceAllInString(result, "$LEVEL$", toString(level));
  replaceAllInString(result, "$TIME$", toString(now, dateFormat));
  replaceAllInString(result, "$MESSAGE$", str);

  if (count > 1)
    result += " x" + std::to_string(count);

  return result;
}
// End helpers

Logger& Logger::getLogger()
{
  static Logger instance;
  return instance;
}

LoggerOptions  Logger::getGlobalOptions()
{
  return _globalOptions;
}

void           Logger::setGlobalOptions(const LoggerOptions& options)
{
  _globalOptions = options;
  getLogger()._localOptions = options;
  if (_globalOptions.getEnableLogging())
    _globalOptions.getProcessor().init();
}

Logger::Logger()
  : _localOptions(_globalOptions)
{
}

Logger::Logger(const LoggerOptions& options)
  : _localOptions(options)
{
}

Logger::~Logger()
{
}

LogHandler::FuncType Logger::generateHandler(LogLevel levelToLog)
{
  if (!_localOptions.getEnableLogging() || levelToLog < _localOptions.getLoggingLevel())
    return [] (const std::string& str) {};

  return [this, levelToLog] (const std::string& str) {
    std::string formatted = formatToLog(str,
                                        _localOptions.getFormat(),
                                        levelToLog,
                                        std::chrono::system_clock::now(),
                                        _localOptions.getDateFormat());
    _localOptions.getProcessor()(formatted);
  };
}

#define LOGGER_GENERATE_LOG_FUNCTION(suffix) \
LogHandler  Logger::log ## suffix() \
{ \
  return LogHandler(generateHandler(LogLevel::suffix), _localOptions); \
}
LOGGER_GENERATE_LOG_FUNCTION(Debug5)
LOGGER_GENERATE_LOG_FUNCTION(Debug4)
LOGGER_GENERATE_LOG_FUNCTION(Debug3)
LOGGER_GENERATE_LOG_FUNCTION(Debug2)
LOGGER_GENERATE_LOG_FUNCTION(Debug1)
LOGGER_GENERATE_LOG_FUNCTION(Debug)
LOGGER_GENERATE_LOG_FUNCTION(Info)
LOGGER_GENERATE_LOG_FUNCTION(Warning)
LOGGER_GENERATE_LOG_FUNCTION(Error)

#undef LOGGER_GENERATE_LOG_FUNCTION

#undef _CRT_SECURE_NO_WARNINGS