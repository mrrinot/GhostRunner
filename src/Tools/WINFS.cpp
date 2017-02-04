#include <Tools/WINFS.hh>

WINFS::WINFS()
	: _name(""), _isDir(false), _isDLL(false), _isLink(false), _isRegular(false)
{
}

WINFS::~WINFS()
{
}

void			WINFS::init(const std::string &name, bool isDir, bool isLink, bool isRegular)
{
  this->_name = name;
  this->_isDir = isDir;
  this->_isLink = isLink;
  this->_isRegular = isRegular;
  if (this->_name.rfind(".dll") == this->_name.size() - 4)
    this->_isDLL = true;
  else
    this->_isDLL = false;
}

const std::string	&WINFS::getName() const
{
  return (this->_name);
}

bool			WINFS::isDir() const
{
  return (this->_isDir);
}

bool			WINFS::isDLL() const
{
  return (this->_isDLL);
}

bool			WINFS::isLink() const
{
	return (this->_isLink);
}

bool			WINFS::isRegular() const
{
	return (this->_isLink);
}