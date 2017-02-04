#ifndef WINFSREADER_HH_
#define WINFSREADER_HH_

#include <iostream>
#include <vector>
#include "WINFS.hh"

class	WINFSReader
{
private:
  WINFSReader(const WINFSReader &);
  WINFSReader		&operator=(const WINFSReader &);

public:
  WINFSReader();
  ~WINFSReader();
  void		getFilesInDir(std::vector<WINFS *> &out, const std::string &dir);
};

#endif
