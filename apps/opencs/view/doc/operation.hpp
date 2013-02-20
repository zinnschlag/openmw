/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_DOC_OPERATION_H
#define CSV_DOC_OPERATION_H

#include <QProgressBar>

namespace CSVDoc
{
    class Operation : public QProgressBar
    {
            Q_OBJECT

            int mType;
            bool mStalling;

            // not implemented
            Operation (const Operation&);
            Operation& operator= (const Operation&);

            void updateLabel (int threads = -1);

        public:

            Operation (int type);

            void setProgress (int current, int max, int threads);

            int getType() const;

        private:

            void setBarColor (int type);
    };
}

#endif
