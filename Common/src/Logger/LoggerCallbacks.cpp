#include "Logger/LoggerCallbacks.hh"
#include <string>
#include <cassert>

namespace LoggerCallbacks
{

  // WriteToStream
  WriteToStream::WriteToStream(std::ostream& stream)
    : _stream(&stream)
  {
  }

  WriteToStream::~WriteToStream()
  {
  }

  void  WriteToStream::init()
  {
  }

  void  WriteToStream::operator()(const std::string& str)
  {
    (*_stream) << str;
  }


  // WriteToFile
  WriteToFile::WriteToFile(const std::string& pathName,
                           std::ofstream::openmode mode)
                           : _writter(nullptr)
                           , _pathName(pathName)
                           , _mode(mode)
  {
  }

  WriteToFile::~WriteToFile()
  {
  }

  void  WriteToFile::init()
  {
    _stream = std::make_shared<std::ofstream>(_pathName, _mode);
    if (!_stream->is_open())
      throw std::runtime_error("Unable to open specified log file.");
    _writter.reset(new WriteToStream(*_stream));
  }

  void  WriteToFile::operator()(const std::string& str)
  {
    assert(!!_writter);
    if (!_stream->is_open())
      throw std::runtime_error("The log file has been closed prematurely.");
    _writter->operator()(str);
    //_stream->flush();
  }

}