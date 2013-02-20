/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWWORLD_ACTIONTALK_H
#define GAME_MWWORLD_ACTIONTALK_H

#include "ptr.hpp"
#include "action.hpp"

namespace MWWorld
{
    class ActionTalk : public Action
    {
            virtual void executeImp (const Ptr& actor);

        public:

            ActionTalk (const Ptr& actor);
            ///< \param actor The actor the player is talking to
    };
}

#endif
