/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "aiwander.hpp"
#include <iostream>

MWMechanics::AiWander::AiWander(int distance, int duration, int timeOfDay, const std::vector<int>& idle):
    mDistance(distance), mDuration(duration), mTimeOfDay(timeOfDay), mIdle(idle)
{
}

MWMechanics::AiPackage * MWMechanics::AiWander::clone() const
{
    return new AiWander(*this);
}

bool MWMechanics::AiWander::execute (const MWWorld::Ptr& actor)
{
    std::cout << "AiWadner completed.\n";
    return true;
}

int MWMechanics::AiWander::getTypeId() const
{
    return 0;
}
