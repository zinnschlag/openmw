/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "aiactivate.hpp"
#include <iostream>

MWMechanics::AiActivate::AiActivate(const std::string &objectId)
: mObjectId(objectId)
{
}
MWMechanics::AiActivate *MWMechanics::AiActivate::clone() const
{
    return new AiActivate(*this);
}
bool MWMechanics::AiActivate::execute (const MWWorld::Ptr& actor)
{
    std::cout << "AiActivate completed.\n";
    return true;
}

int MWMechanics::AiActivate::getTypeId() const
{
    return 4;
}
