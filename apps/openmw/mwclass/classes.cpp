/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "classes.hpp"

#include "activator.hpp"
#include "creature.hpp"
#include "npc.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "potion.hpp"
#include "apparatus.hpp"
#include "book.hpp"
#include "clothing.hpp"
#include "container.hpp"
#include "door.hpp"
#include "ingredient.hpp"
#include "creaturelevlist.hpp"
#include "itemlevlist.hpp"
#include "light.hpp"
#include "lockpick.hpp"
#include "misc.hpp"
#include "probe.hpp"
#include "repair.hpp"
#include "static.hpp"

namespace MWClass
{
    void registerClasses()
    {
        Activator::registerSelf();
        Creature::registerSelf();
        Npc::registerSelf();
        Weapon::registerSelf();
        Armor::registerSelf();
        Potion::registerSelf();
        Apparatus::registerSelf();
        Book::registerSelf();
        Clothing::registerSelf();
        Container::registerSelf();
        Door::registerSelf();
        Ingredient::registerSelf();
        CreatureLevList::registerSelf();
        ItemLevList::registerSelf();
        Light::registerSelf();
        Lockpick::registerSelf();
        Miscellaneous::registerSelf();
        Probe::registerSelf();
        Repair::registerSelf();
        Static::registerSelf();
    }
}
