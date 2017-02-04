/*
    The MIT License(MIT)

    Copyright (c) 2014 Cedric Sana (Ninetainedo - cedricsana@gmail.com)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
    */

#ifndef INI_HH_
#define INI_HH_

#include <string>
#include <fstream>
#include <map>
#include <list>

  class			Ini
  {
  private:
    typedef std::map<std::string, std::string>		t_ini_sub_map;
    typedef std::map<std::string, t_ini_sub_map >	t_ini_map;

    struct		_Positions
    {
      _Positions();
      _Positions(const std::string &line);
      void		process(const std::string &line);
      size_t		_firstChar;
      size_t		_lastChar;
      size_t		_comment;
      size_t		_beginSection;
      size_t		_endSection;
      size_t		_equal;
      size_t		_firstAfterEqual;
      size_t		_lastEqual;
      size_t		_lastBeginSection;
      size_t		_lastEndSection;
      size_t		_firstQuote;
      size_t		_lastQuote;
    }; // _Positions

  public:
    Ini();
    Ini(const std::string &filename);
    ~Ini();
    void		          parse();
    void		          open(std::string const &filename, std::ios_base::openmode mode = std::fstream::in | std::fstream::out);
    void		          open(std::ios_base::openmode mode = std::fstream::in | std::fstream::out);
    void		          close();
    std::string		      get(const std::string &section, const std::string &key, const std::string &def) const;
    const t_ini_sub_map	  &getSection(const std::string &section) const;
    void		          put(const std::string &section, const std::string &key, const std::string &value);
    void		          save();
    void		          errors(int num, const Ini::_Positions &pos);

  private:
    bool		  _opened;
    std::string	  _filename;
    std::fstream  _stream;
    t_ini_map	  _map;
  }; // Ini

#endif // INI_HH_
