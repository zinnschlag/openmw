/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_INGR_H
#define OPENMW_ESM_INGR_H

#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Alchemy ingredient
 */

struct Ingredient
{
    struct IRDTstruct
    {
        float mWeight;
        int mValue;
        int mEffectID[4]; // Effect, 0 or -1 means none
        int mSkills[4]; // SkillEnum related to effect
        int mAttributes[4]; // Attribute related to effect
    };

    IRDTstruct mData;
    std::string mId, mName, mModel, mIcon, mScript;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
