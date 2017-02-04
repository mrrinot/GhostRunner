#pragma once

#ifndef LOGGERCALLBACKS_HH_
#define LOGGERCALLBACKS_HH_

#include <functional>
#include <iostream>
#include <memory>
#include <fstream>

namespace LoggerCallbacks
{
  typedef std::function<void(const std::string&)> ProcessorType;

  class IBaseLoggerCallback
  {
  public:
    virtual ~IBaseLoggerCallback(){}
    virtual void  init() = 0;
    virtual void  operator()(const std::string& str) = 0;
  };

  class WriteToStream : public IBaseLoggerCallback
  {
  public:
    WriteToStream(std::ostream& stream);
    ~WriteToStream();

    void  init() override;
    void  operator()(const std::string& str) override;

  private:
    std::ostream* _stream;
  };

  class WriteToFile : public IBaseLoggerCallback
  {
  public:
    WriteToFile(const std::string& pathName,
                std::ofstream::openmode mode = std::ofstream::out);
    ~WriteToFile();

    void  init() override;
    void  operator()(const std::string& str) override;

  private:
    std::shared_ptr<WriteToStream>  _writter;
    std::shared_ptr<std::ofstream>  _stream;
    std::string                     _pathName;
    std::ofstream::openmode         _mode;
  };


} // namespace LoggerCallbacks

#endif // LOGGERCALLBACKS_HH_