/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWWORLD_CELLFUNCTORS_H
#define GAME_MWWORLD_CELLFUNCTORS_H

#include <vector>
#include <string>

#include "refdata.hpp"

namespace ESM
{
    class CellRef;
}

namespace MWWorld
{
    /// List all (Ogre-)handles.
    struct ListHandles
    {
        std::vector<Ogre::SceneNode*> mHandles;

        bool operator() (ESM::CellRef& ref, RefData& data)
        {
            Ogre::SceneNode* handle = data.getBaseNode();
            if (handle)
                mHandles.push_back (handle);
            return true;
        }
    };
}

#endif
