/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_CLOT_H
#define OPENMW_ESM_CLOT_H

#include <string>

#include "loadarmo.hpp"

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Clothing
 */

struct Clothing
{
    enum Type
    {
        Pants = 0,
        Shoes = 1,
        Shirt = 2,
        Belt = 3,
        Robe = 4,
        RGlove = 5,
        LGlove = 6,
        Skirt = 7,
        Ring = 8,
        Amulet = 9
    };

    struct CTDTstruct
    {
        int mType;
        float mWeight;
        short mValue;
        short mEnchant;
    };
    CTDTstruct mData;

    PartReferenceList mParts;

    std::string mId, mName, mModel, mIcon, mEnchant, mScript;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
