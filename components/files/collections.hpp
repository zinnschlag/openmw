/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPONENTS_FILES_COLLECTION_HPP
#define COMPONENTS_FILES_COLLECTION_HPP

#include <boost/filesystem.hpp>

#include "multidircollection.hpp"

namespace Files
{
    class Collections
    {
        public:
            Collections();

            ///< Directories are listed with increasing priority.
            Collections(const Files::PathContainer& directories, bool foldCase);

            ///< Return a file collection for the given extension. Extension must contain the
            /// leading dot and must be all lower-case.
            const MultiDirCollection& getCollection(const std::string& extension) const;

            const Files::PathContainer& getPaths() const;

        private:
            typedef std::map<std::string, MultiDirCollection> MultiDirCollectionContainer;
            Files::PathContainer mDirectories;

            bool mFoldCase;
            mutable MultiDirCollectionContainer mCollections;
    };
}

#endif
