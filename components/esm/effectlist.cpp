/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "effectlist.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM {

void EffectList::load(ESMReader &esm)
{
    ENAMstruct s;
    while (esm.isNextSub("ENAM")) {
        esm.getHT(s, 24);
        mList.push_back(s);
    }
}

void EffectList::save(ESMWriter &esm)
{
    for (std::vector<ENAMstruct>::iterator it = mList.begin(); it != mList.end(); ++it) {
        esm.writeHNT<ENAMstruct>("ENAM", *it, 24);
    }
}

} // end namespace
