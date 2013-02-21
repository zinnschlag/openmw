/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWWORLD_ACTIONTELEPORT_H
#define GAME_MWWORLD_ACTIONTELEPORT_H

#include <string>

#include <components/esm/defs.hpp>

#include "action.hpp"

namespace MWWorld
{
    class ActionTeleport : public Action
    {
            std::string mCellName;
            ESM::Position mPosition;

            virtual void executeImp (const Ptr& actor);

        public:

            ActionTeleport (const std::string& cellName, const ESM::Position& position);
            ///< If cellName is empty, an exterior cell is asumed.
    };
}

#endif
