/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_MISC_H
#define OPENMW_ESM_MISC_H

#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Misc inventory items, basically things that have no use but can be
 * carried, bought and sold. It also includes keys.
 */

struct Miscellaneous
{
    struct MCDTstruct
    {
        float mWeight;
        int mValue;
        int mIsKey; // There are many keys in Morrowind.esm that has this
                   // set to 0. TODO: Check what this field corresponds to
                   // in the editor.
    };
    MCDTstruct mData;

    std::string mId, mName, mModel, mIcon, mScript;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
