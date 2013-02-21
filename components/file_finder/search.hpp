/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FILE_FINDER_SEARCH_H
#define FILE_FINDER_SEARCH_H

#include <boost/filesystem.hpp>
#include <string>

namespace FileFinder
{
  struct ReturnPath
  {
    virtual void add(const boost::filesystem::path &pth) = 0;
  };

  /** Search the given path and return all file paths through 'ret'. If
      recurse==true, all files in subdirectories are returned as well.
  */
  void find(const boost::filesystem::path & dir_path, ReturnPath &ret, bool recurse=true);
}

#endif
