/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_DOC_OPERATIONS_H
#define CSV_DOC_OPERATIONS_H

#include <vector>

#include <QDockWidget>

class QVBoxLayout;

namespace CSVDoc
{
    class Operation;

    class Operations : public QDockWidget
    {
            Q_OBJECT

            QVBoxLayout *mLayout;
            std::vector<Operation *> mOperations;

            // not implemented
            Operations (const Operations&);
            Operations& operator= (const Operations&);

        public:

            Operations();

            void setProgress (int current, int max, int type, int threads);
            ///< Implicitly starts the operation, if it is not running already.

            void quitOperation (int type);
            ///< Calling this function for an operation that is not running is a no-op.
    };
}

#endif