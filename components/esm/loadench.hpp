/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_ENCH_H
#define OPENMW_ESM_ENCH_H

#include <string>

#include "effectlist.hpp"

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Enchantments
 */

struct Enchantment
{
    enum Type
    {
        CastOnce = 0,
        WhenStrikes = 1,
        WhenUsed = 2,
        ConstantEffect = 3
    };

    struct ENDTstruct
    {
        int mType;
        int mCost;
        int mCharge;
        int mAutocalc; // Guessing this is 1 if we are supposed to auto
        // calculate
    };

    std::string mId;
    ENDTstruct mData;
    EffectList mEffects;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
