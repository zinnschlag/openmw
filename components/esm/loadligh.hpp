/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_LIGH_H
#define OPENMW_ESM_LIGH_H

#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Lights. Includes static light sources and also carryable candles
 * and torches.
 */

struct Light
{
    enum Flags
    {
        Dynamic     = 0x001,
        Carry       = 0x002, // Can be carried
        Negative    = 0x004, // Negative light - i.e. darkness
        Flicker     = 0x008,
        Fire        = 0x010,
        OffDefault  = 0x020, // Off by default
        FlickerSlow = 0x040,
        Pulse       = 0x080,
        PulseSlow   = 0x100
    };

    struct LHDTstruct
    {
        float mWeight;
        int mValue;
        int mTime; // Duration
        int mRadius;
        int mColor; // 4-byte rgba value
        int mFlags;
    }; // Size = 24 bytes

    LHDTstruct mData;

    std::string mSound, mScript, mModel, mIcon, mName, mId;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
