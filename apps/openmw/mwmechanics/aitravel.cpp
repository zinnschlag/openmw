/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "aitravel.hpp"
#include <iostream>

MWMechanics::AiTravel::AiTravel(float x, float y, float z)
: mX(x),mY(y),mZ(z)
{
}

MWMechanics::AiTravel * MWMechanics::AiTravel::clone() const
{
    return new AiTravel(*this);
}

bool MWMechanics::AiTravel::execute (const MWWorld::Ptr& actor)
{
    std::cout << "AiTravel completed.\n";
    return true;
}

int MWMechanics::AiTravel::getTypeId() const
{
    return 1;
}


