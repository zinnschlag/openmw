/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "actionteleport.hpp"

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

namespace MWWorld
{
    ActionTeleport::ActionTeleport (const std::string& cellName,
        const ESM::Position& position)
    : Action (true), mCellName (cellName), mPosition (position)
    {
    }

    void ActionTeleport::executeImp (const Ptr& actor)
    {
        if (mCellName.empty())
            MWBase::Environment::get().getWorld()->changeToExteriorCell (mPosition);
        else
            MWBase::Environment::get().getWorld()->changeToInteriorCell (mCellName, mPosition);
    }
}
