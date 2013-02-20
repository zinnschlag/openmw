/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loaddial.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Dialogue::load(ESMReader &esm)
{
    esm.getSubNameIs("DATA");
    esm.getSubHeader();
    int si = esm.getSubSize();
    if (si == 1)
        esm.getT(mType);
    else if (si == 4)
    {
        // These are just markers, their values are not used.
        int i;
        esm.getT(i);
        esm.getHNT(i, "DELE");
        mType = Deleted;
    }
    else
        esm.fail("Unknown sub record size");
}

void Dialogue::save(ESMWriter &esm)
{
    if (mType != Deleted)
        esm.writeHNT("DATA", mType);
    else
    {
        esm.writeHNT("DATA", (int)1);
        esm.writeHNT("DELE", (int)1);
    }
}

}
