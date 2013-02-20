/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "collections.hpp"

namespace Files
{
    Collections::Collections()
        : mDirectories()
        , mFoldCase(false)
        , mCollections()
    {
    }

    Collections::Collections(const Files::PathContainer& directories, bool foldCase)
        : mDirectories(directories)
        , mFoldCase(foldCase)
        , mCollections()
    {
    }

    const MultiDirCollection& Collections::getCollection(const std::string& extension) const
    {
        MultiDirCollectionContainer::iterator iter = mCollections.find(extension);
        if (iter==mCollections.end())
        {
            std::pair<MultiDirCollectionContainer::iterator, bool> result =
                mCollections.insert(std::make_pair(extension, MultiDirCollection(mDirectories, extension, mFoldCase)));

            iter = result.first;
        }

        return iter->second;
    }

    const Files::PathContainer& Collections::getPaths() const
    {
        return mDirectories;
    }
}
