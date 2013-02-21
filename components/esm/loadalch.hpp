/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_ALCH_H
#define OPENMW_ESM_ALCH_H

#include <string>

#include "effectlist.hpp"

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Alchemy item (potions)
 */

struct Potion
{
    struct ALDTstruct
    {
        float mWeight;
        int mValue;
        int mAutoCalc;
    };
    ALDTstruct mData;

    std::string mId, mName, mModel, mIcon, mScript;
    EffectList mEffects;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
    };
}
#endif
