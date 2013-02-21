/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_BOOK_H
#define OPENMW_ESM_BOOK_H

#include <string>

namespace ESM
{
/*
 * Books, magic scrolls, notes and so on
 */

class ESMReader;
class ESMWriter;

struct Book
{
    struct BKDTstruct
    {
        float mWeight;
        int mValue, mIsScroll, mSkillID, mEnchant;
    };

    BKDTstruct mData;
    std::string mName, mModel, mIcon, mScript, mEnchant, mText;
    std::string mId;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
