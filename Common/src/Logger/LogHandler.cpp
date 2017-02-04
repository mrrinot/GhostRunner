#include "Logger/LogHandler.hh"

LogHandler::LogHandler(const FuncType& f,
                       const LoggerOptions& options)
  : _f(f),
  _options(options),
  _firstDone(false)
{
}

LogHandler::~LogHandler()
{
  if (_options.getAutoLineBreak())
    _ss << "\n";
  _f(_ss.str());
}

LogHandler::LogHandler(LogHandler&& oth)
  : _f(std::move(oth._f)),
  _ss(std::move(oth._ss)),
  _options(std::move(oth._options)),
  _firstDone(std::move(oth._firstDone))
{
}

LogHandler& LogHandler::operator=(LogHandler&& oth)
{
  _f = std::move(oth._f);
  _ss = std::move(oth._ss);
  _options = std::move(oth._options);
  _firstDone = std::move(oth._firstDone);
  return *this;
}