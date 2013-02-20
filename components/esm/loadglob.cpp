/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "loadglob.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Global::load(ESMReader &esm)
{
    std::string tmp = esm.getHNString("FNAM");
    if (tmp == "s")
        mType = VT_Short;
    else if (tmp == "l")
        mType = VT_Int;
    else if (tmp == "f")
        mType = VT_Float;
    else
        esm.fail("Illegal global variable type " + tmp);

    // Note: Both floats and longs are represented as floats.
    esm.getHNT(mValue, "FLTV");
}

void Global::save(ESMWriter &esm)
{
    switch(mType)
    {
    case VT_Short:
        esm.writeHNString("FNAM", "s");
        break;

    case VT_Int:
        esm.writeHNString("FNAM", "l");
        break;

    case VT_Float:
        esm.writeHNString("FNAM", "f");
        break;

    default:
        return;
    }
    esm.writeHNT("FLTV", mValue);
}

    void Global::blank()
    {
        mValue = 0;
        mType = VT_Float;
    }

    bool operator== (const Global& left, const Global& right)
    {
        return left.mId==right.mId && left.mValue==right.mValue && left.mType==right.mType;
    }
}
