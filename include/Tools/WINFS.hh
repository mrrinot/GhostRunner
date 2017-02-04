#ifndef WINFS_HH_
#define WINFS_HH_

#include <string>

class	WINFS
{
public:
  WINFS();
  ~WINFS();

  WINFS(const WINFS &) = delete;
  WINFS		&operator=(const WINFS &) = delete;

private:
  std::string	_name;
  bool		_isDir;
  bool		_isDLL;
  bool		_isLink;
  bool		_isRegular;

public:

  void			init(const std::string &, bool, bool, bool);
  const	std::string	&getName() const;
  bool			isDir() const;
  bool			isDLL() const;
  bool			isLink() const;
  bool			isRegular() const;
};

#endif
