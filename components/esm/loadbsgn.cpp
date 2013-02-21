/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadbsgn.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void BirthSign::load(ESMReader &esm)
{
    mName = esm.getHNString("FNAM");
    mTexture = esm.getHNOString("TNAM");
    mDescription = esm.getHNOString("DESC");

    mPowers.load(esm);
}

void BirthSign::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mName);
    esm.writeHNOCString("TNAM", mTexture);
    esm.writeHNOCString("DESC", mDescription);

    mPowers.save(esm);
}

}
