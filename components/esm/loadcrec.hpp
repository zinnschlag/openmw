/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_CREC_H
#define OPENMW_ESM_CREC_H

#include <string>

// TODO create implementation files and remove this one
#include "esmreader.hpp"

namespace ESM {

class ESMReader;
class ESMWriter;

/* These two are only used in save games. They are not decoded yet.
 */

/// Changes a creature
struct LoadCREC
{
    std::string mId;

    void load(ESMReader &esm)
    {
      esm.skipRecord();
    }

    void save(ESMWriter &esm)
    {
    }
};

/// Changes an item list / container
struct LoadCNTC
{
    std::string mId;

    void load(ESMReader &esm)
    {
      esm.skipRecord();
    }

    void save(ESMWriter &esm)
    {
    }
};
}
#endif
