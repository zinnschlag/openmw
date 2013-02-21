/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadsoun.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Sound::load(ESMReader &esm)
{
    mSound = esm.getHNString("FNAM");
    esm.getHNT(mData, "DATA", 3);
    /*
     cout << "vol=" << (int)data.volume
     << " min=" << (int)data.minRange
     << " max=" << (int)data.maxRange
     << endl;
     */
}
void Sound::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mSound);
    esm.writeHNT("DATA", mData, 3);
}

}
