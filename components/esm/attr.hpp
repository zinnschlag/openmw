/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_ATTR_H
#define OPENMW_ESM_ATTR_H

#include <string>

namespace ESM {

/*
 * Attribute definitions
 */

struct Attribute
{
    enum AttributeID
    {
        Strength = 0,
        Intelligence = 1,
        Willpower = 2,
        Agility = 3,
        Speed = 4,
        Endurance = 5,
        Personality = 6,
        Luck = 7,
        Length
    };

    AttributeID mId;
    std::string mName, mDescription;

    static const AttributeID sAttributeIds[Length];
    static const std::string sGmstAttributeIds[Length];
    static const std::string sGmstAttributeDescIds[Length];
    static const std::string sAttributeIcons[Length];

    Attribute(AttributeID id, const std::string &name, const std::string &description)
        : mId(id)
        , mName(name)
        , mDescription(description)
    {
    }
};
}
#endif
