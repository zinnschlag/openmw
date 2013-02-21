/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_AIWANDER_H
#define GAME_MWMECHANICS_AIWANDER_H

#include "aipackage.hpp"
#include <vector>

namespace MWMechanics
{

    class AiWander : public AiPackage
    {
    public:

        AiWander(int distance, int duration, int timeOfDay, const std::vector<int>& idle);
        virtual AiPackage *clone() const;
        virtual bool execute (const MWWorld::Ptr& actor);
        ///< \return Package completed?
        virtual int getTypeId() const;
        ///< 0: Wander

    private:
        int mDistance;
        int mDuration;
        int mTimeOfDay;
        std::vector<int> mIdle;
    };
    }

#endif
