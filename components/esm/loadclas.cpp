/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadclas.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

const Class::Specialization Class::sSpecializationIds[3] = {
  Class::Combat,
  Class::Magic,
  Class::Stealth
};

const char *Class::sGmstSpecializationIds[3] = {
  "sSpecializationCombat",
  "sSpecializationMagic",
  "sSpecializationStealth"
};

void Class::load(ESMReader &esm)
{
    mName = esm.getHNString("FNAM");
    esm.getHNT(mData, "CLDT", 60);

    if (mData.mIsPlayable > 1)
        esm.fail("Unknown bool value");

    mDescription = esm.getHNOString("DESC");
}
void Class::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mName);
    esm.writeHNT("CLDT", mData, 60);
    esm.writeHNOString("DESC", mDescription);
}

}
