/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_SSCR_H
#define OPENMW_ESM_SSCR_H

#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 Startup script. I think this is simply a 'main' script that is run
 from the begining. The SSCR records contain a DATA identifier which
 is totally useless (TODO: don't remember what it contains exactly,
 document it below later.), and a NAME which is simply a script
 reference.
 */

struct StartScript
{
    std::string mData;
    std::string mId, mScript;

    // Load a record and add it to the list
    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};

}
#endif
