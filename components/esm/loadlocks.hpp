/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_LOCKS_H
#define OPENMW_ESM_LOCKS_H

#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * This file covers lockpicks (LOCK), probes (PROB) and armor repair
 * items (REPA). These have nearly identical data structures.
 */

struct Tool
{
    enum Type
    {
        Type_Pick,
        Type_Probe,
        Type_Repair
    };

    struct Data
    {
        float mWeight;
        int mValue;

        float mQuality; // And when I say nearly identical structure, I
        int mUses;      // mean perfectly identical except that these two
                       // variables are swaped for repair items. Don't ask
                       // me why.
    }; // Size = 16

    Data mData;
    Type mType;
    std::string mId, mName, mModel, mIcon, mScript;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};

struct Probe: Tool
{
    Probe() { mType = Type_Probe; }
};

struct Repair: Tool
{
    Repair() { mType = Type_Repair; }
};

}
#endif
