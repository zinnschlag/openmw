/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "idtableproxymodel.hpp"

#include "idtable.hpp"

CSMWorld::IdTableProxyModel::IdTableProxyModel (QObject *parent)
: QSortFilterProxyModel (parent)
{}

void CSMWorld::IdTableProxyModel::addRecord (const std::string& id)
{
    dynamic_cast<IdTable&> (*sourceModel()).addRecord (id);
}

QModelIndex CSMWorld::IdTableProxyModel::getModelIndex (const std::string& id, int column) const
{
    return mapFromSource (dynamic_cast<IdTable&> (*sourceModel()).getModelIndex (id, column));
}