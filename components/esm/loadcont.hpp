/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_CONT_H
#define OPENMW_ESM_CONT_H

#include <string>
#include <vector>

#include "esmcommon.hpp"

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Container definition
 */

struct ContItem
{
    int mCount;
    NAME32 mItem;
};

struct InventoryList
{
    std::vector<ContItem> mList;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};

struct Container
{
    enum Flags
    {
        Organic = 1, // Objects cannot be placed in this container
        Respawn = 2, // Respawns after 4 months
        Unknown = 8
    };

    std::string mId, mName, mModel, mScript;

    float mWeight; // Not sure, might be max total weight allowed?
    int mFlags;
    InventoryList mInventory;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
