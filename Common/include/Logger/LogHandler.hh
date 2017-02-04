#pragma once

#ifndef LOGHANDLER_HH_
#define LOGHANDLER_HH_

#include "Logger/LoggerOptions.hh"
#include <functional>
#include <sstream>

class LogHandler
{
public:
  typedef std::function<void(const std::string&)> FuncType;

  LogHandler(const FuncType& f,
             const LoggerOptions& options);
  ~LogHandler();

  LogHandler(LogHandler&& oth);
  LogHandler& operator=(LogHandler&& oth);

  template <typename T>
  friend LogHandler&& operator<<(LogHandler&&, const T& t);

protected:
  FuncType            _f;
  std::ostringstream  _ss;
  LoggerOptions       _options;
  bool                _firstDone;
};

template <typename T>
LogHandler&& operator<<(LogHandler&& l, const T& t)
{
  if (l._options.getAutoSeparator() && l._firstDone)
    l._ss << l._options.getSeparator();
  l._firstDone = true;
  l._ss << t;
  return std::move(l);
}

#endif // LOGHANDLER_HH_