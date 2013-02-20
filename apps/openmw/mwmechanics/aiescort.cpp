/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "aiescort.hpp"
#include <iostream>

MWMechanics::AiEscort::AiEscort(const std::string &actorId,int duration, float x, float y, float z)
: mActorId(actorId), mX(x), mY(y), mZ(z), mDuration(duration)
{
}

MWMechanics::AiEscort::AiEscort(const std::string &actorId,const std::string &cellId,int duration, float x, float y, float z)
: mActorId(actorId), mCellId(cellId), mX(x), mY(y), mZ(z), mDuration(duration)
{
}


MWMechanics::AiEscort *MWMechanics::AiEscort::clone() const
{
    return new AiEscort(*this);
}

bool MWMechanics::AiEscort::execute (const MWWorld::Ptr& actor)
{
    std::cout << "AiEscort completed. \n";
    return true;
}

int MWMechanics::AiEscort::getTypeId() const
{
    return 2;
}

