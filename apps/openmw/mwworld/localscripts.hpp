/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWWORLD_LOCALSCRIPTS_H
#define GAME_MWWORLD_LOCALSCRIPTS_H

#include <list>
#include <string>

#include "ptr.hpp"

namespace MWWorld
{
    struct ESMStore;
    class CellStore;
    class RefData;

    /// \brief List of active local scripts
    class LocalScripts
    {
            std::list<std::pair<std::string, Ptr> > mScripts;
            std::list<std::pair<std::string, Ptr> >::iterator mIter;
            MWWorld::Ptr mIgnore;
            const MWWorld::ESMStore& mStore;

        public:

            LocalScripts (const MWWorld::ESMStore& store);

            void setIgnore (const Ptr& ptr);
            ///< Mark a single reference for ignoring during iteration over local scripts (will revoke
            /// previous ignores).

            void startIteration();
            ///< Set the iterator to the begin of the script list.

            bool isFinished() const;
            ///< Is iteration finished?

            std::pair<std::string, Ptr> getNext();
            ///< Get next local script (must not be called if isFinished())

            void add (const std::string& scriptName, const Ptr& ptr);
            ///< Add script to collection of active local scripts.

            void addCell (CellStore *cell);
            ///< Add all local scripts in a cell.

            void clear();
            ///< Clear active local scripts collection.

            void clearCell (CellStore *cell);
            ///< Remove all scripts belonging to \a cell.
            
            void remove (RefData *ref);

            void remove (const Ptr& ptr);
            ///< Remove script for given reference (ignored if reference does not have a scirpt listed).
    };
}

#endif
