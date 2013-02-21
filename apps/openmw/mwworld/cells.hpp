/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWWORLD_CELLS_H
#define GAME_MWWORLD_CELLS_H

#include <map>
#include <list>
#include <string>

#include "ptr.hpp"

namespace ESM
{
    class ESMReader;
}

namespace MWWorld
{
    class ESMStore;

    /// \brief Cell container
    class Cells
    {
            const MWWorld::ESMStore& mStore;
            std::vector<ESM::ESMReader>& mReader;
            std::map<std::string, CellStore> mInteriors;
            std::map<std::pair<int, int>, CellStore> mExteriors;
            std::vector<std::pair<std::string, CellStore *> > mIdCache;
            std::size_t mIdCacheIndex;

            Cells (const Cells&);
            Cells& operator= (const Cells&);

            CellStore *getCellStore (const ESM::Cell *cell);

            void fillContainers (CellStore& cellStore);

            Ptr getPtrAndCache (const std::string& name, CellStore& cellStore);

        public:

            Cells (const MWWorld::ESMStore& store, std::vector<ESM::ESMReader>& reader);
            ///< \todo pass the dynamic part of the ESMStore isntead (once it is written) of the whole
            /// world

            CellStore *getExterior (int x, int y);

            CellStore *getInterior (const std::string& name);

            Ptr getPtr (const std::string& name, CellStore& cellStore);

            Ptr getPtr (const std::string& name);
    };
}

#endif
