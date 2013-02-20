/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "actionapply.hpp"

#include "class.hpp"

namespace MWWorld
{
    ActionApply::ActionApply (const Ptr& target, const std::string& id)
    : Action (false, target), mId (id)
    {}

    void ActionApply::executeImp (const Ptr& actor)
    {
        MWWorld::Class::get (getTarget()).apply (getTarget(), mId, actor);
    }


    ActionApplyWithSkill::ActionApplyWithSkill (const Ptr& target, const std::string& id,
        int skillIndex, int usageType)
    : Action (false, target), mId (id), mSkillIndex (skillIndex), mUsageType (usageType)
    {}

    void ActionApplyWithSkill::executeImp (const Ptr& actor)
    {
        if (MWWorld::Class::get (getTarget()).apply (getTarget(), mId, actor) && mUsageType!=-1)
            MWWorld::Class::get (getTarget()).skillUsageSucceeded (actor, mSkillIndex, mUsageType);
    }
}
