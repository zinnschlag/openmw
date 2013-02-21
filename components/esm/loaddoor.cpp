/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loaddoor.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Door::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNOString("FNAM");
    mScript = esm.getHNOString("SCRI");
    mOpenSound = esm.getHNOString("SNAM");
    mCloseSound = esm.getHNOString("ANAM");
}

void Door::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNOCString("FNAM", mName);
    esm.writeHNOCString("SCRI", mScript);
    esm.writeHNOCString("SNAM", mOpenSound);
    esm.writeHNOCString("ANAM", mCloseSound);
}

}
