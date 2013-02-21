/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "operations.hpp"

#include <QVBoxLayout>

#include "operation.hpp"

CSVDoc::Operations::Operations()
{
    /// \todo make widget height fixed (exactly the height required to display all operations)

    setFeatures (QDockWidget::NoDockWidgetFeatures);

    QWidget *widget = new QWidget;
    setWidget (widget);

    mLayout = new QVBoxLayout;

    widget->setLayout (mLayout);
}

void CSVDoc::Operations::setProgress (int current, int max, int type, int threads)
{
    for (std::vector<Operation *>::iterator iter (mOperations.begin()); iter!=mOperations.end(); ++iter)
        if ((*iter)->getType()==type)
        {
            (*iter)->setProgress (current, max, threads);
            return;
        }

    Operation *operation = new Operation (type);

    mLayout->addWidget (operation);
    mOperations.push_back (operation);
    operation->setProgress (current, max, threads);
}

void CSVDoc::Operations::quitOperation (int type)
{
    for (std::vector<Operation *>::iterator iter (mOperations.begin()); iter!=mOperations.end(); ++iter)
        if ((*iter)->getType()==type)
        {
            delete *iter;
            mOperations.erase (iter);
            break;
        }
}