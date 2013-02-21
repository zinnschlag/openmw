/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "itemlevlist.hpp"

#include <components/esm/loadlevlist.hpp>

namespace MWClass
{
    std::string ItemLevList::getName (const MWWorld::Ptr& ptr) const
    {
        return "";
    }

    void ItemLevList::registerSelf()
    {
        boost::shared_ptr<Class> instance (new ItemLevList);

        registerClass (typeid (ESM::ItemLevList).name(), instance);
    }
}
