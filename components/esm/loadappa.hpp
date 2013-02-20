/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_APPA_H
#define OPENMW_ESM_APPA_H

#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Alchemist apparatus
 */

struct Apparatus
{
    enum AppaType
    {
        MortarPestle = 0,
        Albemic = 1,
        Calcinator = 2,
        Retort = 3
    };

    struct AADTstruct
    {
        int mType;
        float mQuality;
        float mWeight;
        int mValue;
    };

    AADTstruct mData;
    std::string mId, mModel, mIcon, mScript, mName;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
