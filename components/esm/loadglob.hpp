/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_GLOB_H
#define OPENMW_ESM_GLOB_H

#include <string>

#include "defs.hpp"

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Global script variables
 */

struct Global
{
    std::string mId;
    float mValue;
    VarType mType;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);

    void blank();
    ///< Set record to default state (does not touch the ID).
};

bool operator== (const Global& left, const Global& right);

}
#endif
