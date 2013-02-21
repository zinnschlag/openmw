/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef GAME_MWWORLD_ACTIONAPPLY_H
#define GAME_MWWORLD_ACTIONAPPLY_H

#include <string>

#include "action.hpp"
#include "ptr.hpp"

namespace MWWorld
{
    class ActionApply : public Action
    {
            std::string mId;

            virtual void executeImp (const Ptr& actor);

        public:

            ActionApply (const Ptr& target, const std::string& id);
    };

    class ActionApplyWithSkill : public Action
    {
            std::string mId;
            int mSkillIndex;
            int mUsageType;

            virtual void executeImp (const Ptr& actor);

        public:

            ActionApplyWithSkill (const Ptr& target, const std::string& id,
                int skillIndex, int usageType);
    };
}

#endif
