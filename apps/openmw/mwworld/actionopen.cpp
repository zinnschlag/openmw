/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "actionopen.hpp"

#include "../mwbase/environment.hpp"
#include "../mwbase/windowmanager.hpp"

#include "../mwgui/container.hpp"

#include "class.hpp"
#include "containerstore.hpp"

namespace MWWorld
{
    ActionOpen::ActionOpen (const MWWorld::Ptr& container) : Action (false, container)
    {
    }

    void ActionOpen::executeImp (const MWWorld::Ptr& actor)
    {
        if (!MWBase::Environment::get().getWindowManager()->isAllowed(MWGui::GW_Inventory))
            return;

        MWBase::Environment::get().getWindowManager()->pushGuiMode(MWGui::GM_Container);
        MWBase::Environment::get().getWindowManager()->getContainerWindow()->open(getTarget());
    }
}
