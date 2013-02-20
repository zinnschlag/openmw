/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "referenceinterface.hpp"

#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"

#include "../mwworld/player.hpp"

namespace MWGui
{
    ReferenceInterface::ReferenceInterface()
        : mCurrentPlayerCell(NULL)
    {
    }

    ReferenceInterface::~ReferenceInterface()
    {
    }

    void ReferenceInterface::checkReferenceAvailable()
    {
        if (mPtr.isEmpty())
            return;

        MWWorld::Ptr::CellStore* playerCell = MWBase::Environment::get().getWorld()->getPlayer().getPlayer().getCell();

        // check if player has changed cell, or count of the reference has become 0
        if ((playerCell != mCurrentPlayerCell && mCurrentPlayerCell != NULL)
            || mPtr.getRefData().getCount() == 0)
            onReferenceUnavailable();

        mCurrentPlayerCell = playerCell;
    }
}
