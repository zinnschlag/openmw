/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_WORLD_TABLESUBVIEW_H
#define CSV_WORLD_TABLESUBVIEW_H

#include "../doc/subview.hpp"

class QModelIndex;

namespace CSMDoc
{
    class Document;
}

namespace CSVWorld
{
    class Table;

    class TableSubView : public CSVDoc::SubView
    {
            Q_OBJECT

            Table *mTable;

        public:

            TableSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document, bool createAndDelete);

            virtual void setEditLock (bool locked);

        private slots:

            void rowActivated (const QModelIndex& index);
    };
}

#endif