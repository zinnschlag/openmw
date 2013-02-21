/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "reportsubview.hpp"

#include <QTableView>
#include <QHeaderView>

#include "../../model/tools/reportmodel.hpp"

CSVTools::ReportSubView::ReportSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document)
: CSVDoc::SubView (id), mModel (document.getReport (id))
{
    setWidget (mTable = new QTableView (this));
    mTable->setModel (mModel);

    mTable->horizontalHeader()->setResizeMode (QHeaderView::Interactive);
    mTable->verticalHeader()->hide();
    mTable->setSortingEnabled (true);
    mTable->setSelectionBehavior (QAbstractItemView::SelectRows);
    mTable->setSelectionMode (QAbstractItemView::ExtendedSelection);

    connect (mTable, SIGNAL (doubleClicked (const QModelIndex&)), this, SLOT (show (const QModelIndex&)));
}

void CSVTools::ReportSubView::setEditLock (bool locked)
{
    // ignored. We don't change document state anyway.
}

void CSVTools::ReportSubView::show (const QModelIndex& index)
{
    focusId (mModel->getUniversalId (index.row()));
}