/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_TOOLS_REPORTSUBVIEW_H
#define CSV_TOOLS_REPORTSUBVIEW_H

#include "../doc/subview.hpp"

class QTableView;
class QModelIndex;

namespace CSMDoc
{
    class Document;
}

namespace CSMTools
{
    class ReportModel;
}

namespace CSVTools
{
    class Table;

    class ReportSubView : public CSVDoc::SubView
    {
            Q_OBJECT

            CSMTools::ReportModel *mModel;
            QTableView *mTable;

        public:

            ReportSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document);

            virtual void setEditLock (bool locked);

        private slots:

            void show (const QModelIndex& index);
    };
}

#endif