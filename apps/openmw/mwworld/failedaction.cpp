/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "failedaction.hpp"
#include "../mwbase/world.hpp"

#include "../mwbase/environment.hpp"
#include "../mwbase/windowmanager.hpp"


namespace MWWorld
{
    FailedAction::FailedAction (const std::string& msg) : Action (false), message(msg)
    {   }


    void FailedAction::executeImp (const Ptr& actor)
    {
        if ( actor.getRefData().getHandle()=="player" && !(message.empty()))
	{
	  MWBase::Environment::get().getWindowManager() ->messageBox(message, std::vector<std::string>());
	}
    }
}
