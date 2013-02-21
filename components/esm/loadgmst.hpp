/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_GMST_H
#define OPENMW_ESM_GMST_H

#include <string>

#include "defs.hpp"

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 *  Game setting, with automatic cleaning of "dirty" entries.
 *
 */

struct GameSetting
{
    std::string mId;
    // One of these is used depending on the variable type
    std::string mStr;
    int mI;
    float mF;
    VarType mType;

    void load(ESMReader &esm);

    int getInt() const;
    ///< Throws an exception if GMST is not of type int or float.

    float getFloat() const;
    ///< Throws an exception if GMST is not of type int or float.

    std::string getString() const;
    ///< Throwns an exception if GMST is not of type string.

    void save(ESMWriter &esm);

    void blank();
    ///< Set record to default state (does not touch the ID).
};

    bool operator== (const GameSetting& left, const GameSetting& right);
}
#endif
