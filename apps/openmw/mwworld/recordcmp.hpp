/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_MWWORLD_RECORDCMP_H
#define OPENMW_MWWORLD_RECORDCMP_H

#include <cctype>

#include <components/esm/records.hpp>

namespace MWWorld
{
    struct RecordCmp
    {
        template <class T>
        bool operator()(const T &x, const T& y) const {
            return x.mId < y.mId;
        }
    };

    template <>
    inline bool RecordCmp::operator()<ESM::Dialogue>(const ESM::Dialogue &x, const ESM::Dialogue &y) const {
        return Misc::StringUtils::ciLess(x.mId, y.mId);
    }

    template <>
    inline bool RecordCmp::operator()<ESM::Cell>(const ESM::Cell &x, const ESM::Cell &y) const {
        return Misc::StringUtils::ciLess(x.mName, y.mName);
    }

    template <>
    inline bool RecordCmp::operator()<ESM::Pathgrid>(const ESM::Pathgrid &x, const ESM::Pathgrid &y) const {
        return Misc::StringUtils::ciLess(x.mCell, y.mCell);
    }

} // end namespace
#endif
