#include "Logger/LoggerOptions.hh"

LoggerOptions::LoggerOptions()
  : _level(LogLevel::Debug5),
  _autoLineBreak(false),
  _autoSeparator(false),
  _loggingEnabled(true),
  _separator(" "),
  _processor(new LoggerCallbacks::WriteToStream(std::cout)),
  _format("[$TIME$][$LEVEL$]: $MESSAGE$"),
  _dateFormat("%Y-%m-%d %H:%M:%S")
{
}

#define LOGGEROPTIONS_GENERATE_DEFINITION(type, id, name) \
  type LoggerOptions::get##id() const {return name;} \
  LoggerOptions& LoggerOptions::set##id(type id) {name = id; return *this;}

LOGGEROPTIONS_GENERATE_DEFINITION(LogLevel, LoggingLevel, _level)
LOGGEROPTIONS_GENERATE_DEFINITION(bool, AutoLineBreak, _autoLineBreak)
LOGGEROPTIONS_GENERATE_DEFINITION(bool, AutoSeparator, _autoSeparator)
LOGGEROPTIONS_GENERATE_DEFINITION(bool, EnableLogging, _loggingEnabled)
LOGGEROPTIONS_GENERATE_DEFINITION(std::string, Separator, _separator)
LOGGEROPTIONS_GENERATE_DEFINITION(std::string, Format, _format)
LOGGEROPTIONS_GENERATE_DEFINITION(std::string, DateFormat, _dateFormat)

#undef LOGGEROPTIONS_GENERATE_DEFINITION

LoggerCallbacks::IBaseLoggerCallback& LoggerOptions::getProcessor()
{
  return *_processor;
}