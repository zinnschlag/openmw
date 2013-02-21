/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NATURALSORT_H
#define NATURALSORT_H

#include <QString>

bool naturalSortLessThanCS( const QString &left, const QString &right );
bool naturalSortLessThanCI( const QString &left, const QString &right );
bool naturalSortGreaterThanCS( const QString &left, const QString &right );
bool naturalSortGreaterThanCI( const QString &left, const QString &right );

#endif
