/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSM_TOOLS_REPORTMODEL_H
#define CSM_TOOLS_REPORTMODEL_H

#include <vector>
#include <string>

#include <QAbstractTableModel>

#include "../world/universalid.hpp"

namespace CSMTools
{
    class ReportModel : public QAbstractTableModel
    {
            Q_OBJECT

            std::vector<std::pair<CSMWorld::UniversalId, std::string> > mRows;

        public:

            virtual int rowCount (const QModelIndex & parent = QModelIndex()) const;

            virtual int columnCount (const QModelIndex & parent = QModelIndex()) const;

            virtual QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;

            virtual QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

            virtual bool removeRows (int row, int count, const QModelIndex& parent = QModelIndex());

            void add (const std::string& row);

            const CSMWorld::UniversalId& getUniversalId (int row) const;
    };
}

#endif
