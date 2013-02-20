/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "aifollow.hpp"
#include <iostream>

MWMechanics::AiFollow::AiFollow(const std::string &actorId,float duration, float x, float y, float z)
: mDuration(duration), mX(x), mY(y), mZ(z), mActorId(actorId)
{
}
MWMechanics::AiFollow::AiFollow(const std::string &actorId,const std::string &cellId,float duration, float x, float y, float z)
: mDuration(duration), mX(x), mY(y), mZ(z), mActorId(actorId), mCellId(cellId)
{
}

MWMechanics::AiFollow *MWMechanics::AiFollow::clone() const
{
    return new AiFollow(*this);
}

 bool MWMechanics::AiFollow::execute (const MWWorld::Ptr& actor)
{
    std::cout << "AiFollow completed.\n";
    return true;
}

 int MWMechanics::AiFollow::getTypeId() const
{
    return 3;
}
