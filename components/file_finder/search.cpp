/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "search.hpp"

#include <iostream>

void FileFinder::find(const boost::filesystem::path & dir_path, ReturnPath &ret, bool recurse)
{
    if (boost::filesystem::exists(dir_path))
    {
        if (!recurse)
        {
            boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end
            for (boost::filesystem::directory_iterator itr(dir_path); itr != end_itr; ++itr)
            {
                if (!boost::filesystem::is_directory( *itr ))
                {
                    ret.add(*itr);
                }
            }
        }
        else
        {
            boost::filesystem::recursive_directory_iterator end_itr; // default construction yields past-the-end
            for (boost::filesystem::recursive_directory_iterator itr(dir_path); itr != end_itr; ++itr)
            {
                if (!boost::filesystem::is_directory(*itr))
                {
                    ret.add(*itr);
                }
            }
        }
    }
    else
    {
        std::cout << "Path " << dir_path << " not found" << std::endl;
    }
}
