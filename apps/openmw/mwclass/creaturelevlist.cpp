/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "creaturelevlist.hpp"

#include <components/esm/loadlevlist.hpp>

namespace MWClass
{
    std::string CreatureLevList::getName (const MWWorld::Ptr& ptr) const
    {
        return "";
    }

    void CreatureLevList::registerSelf()
    {
        boost::shared_ptr<Class> instance (new CreatureLevList);

        registerClass (typeid (ESM::CreatureLevList).name(), instance);
    }
}
