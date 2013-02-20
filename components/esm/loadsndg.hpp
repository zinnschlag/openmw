/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_SNDG_H
#define OPENMW_ESM_SNDG_H

#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Sound generator. This describes the sounds a creature make.
 */

struct SoundGenerator
{
    enum Type
    {
        LeftFoot = 0,
        RightFoot = 1,
        SwimLeft = 2,
        SwimRight = 3,
        Moan = 4,
        Roar = 5,
        Scream = 6,
        Land = 7
    };

    // Type
    int mType;

    std::string mId, mCreature, mSound;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
