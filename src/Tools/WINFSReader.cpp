#include <Tools/WINFSReader.hh>
#include <windows.h>

WINFSReader::WINFSReader()
{
}

WINFSReader::~WINFSReader()
{
}

void				WINFSReader::getFilesInDir(std::vector<WINFS *> &out, const std::string &directory)
{
  HANDLE			dir;
  WIN32_FIND_DATA	data;

  if ((dir = FindFirstFile((directory + "/*").c_str(), &data)) == INVALID_HANDLE_VALUE)
    return;
  out.clear();
  do
  {
    const std::string name = data.cFileName;
    const std::string fullname = directory + "/" + name;
    if (*(name.begin()) != '.')
    {
      WINFS *	fs = new WINFS();
      fs->init(fullname, ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0),
        ((data.dwFileAttributes & FILE_ATTRIBUTE_VIRTUAL) != 0),
        ((data.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) != 0));
      out.push_back(fs);
    }
  } while (FindNextFile(dir, &data));
}
