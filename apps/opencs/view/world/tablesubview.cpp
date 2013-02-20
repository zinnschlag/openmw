/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "tablesubview.hpp"

#include "../../model/doc/document.hpp"

#include "table.hpp"

CSVWorld::TableSubView::TableSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document,
    bool createAndDelete)
: SubView (id)
{
    setWidget (mTable = new Table (id, document.getData(), document.getUndoStack(), createAndDelete));

    connect (mTable, SIGNAL (doubleClicked (const QModelIndex&)), this, SLOT (rowActivated (const QModelIndex&)));
}

void CSVWorld::TableSubView::setEditLock (bool locked)
{
    mTable->setEditLock (locked);
}

void CSVWorld::TableSubView::rowActivated (const QModelIndex& index)
{
    /// \todo re-enable, after dialogue sub views have been fixed up
//    focusId (mTable->getUniversalId (index.row()));
}