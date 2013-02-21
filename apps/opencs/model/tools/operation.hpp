/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSM_TOOLS_OPERATION_H
#define CSM_TOOLS_OPERATION_H

#include <vector>

#include <QThread>

namespace CSMTools
{
    class Stage;

    class Operation : public QThread
    {
            Q_OBJECT

            int mType;
            std::vector<std::pair<Stage *, int> > mStages; // stage, number of steps
            std::vector<std::pair<Stage *, int> >::iterator mCurrentStage;
            int mCurrentStep;
            int mCurrentStepTotal;
            int mTotalSteps;

            void prepareStages();

        public:

            Operation (int type);

            virtual ~Operation();

            virtual void run();

            void appendStage (Stage *stage);
            ///< The ownership of \a stage is transferred to *this.
            ///
            /// \attention Do no call this function while this Operation is running.

        signals:

            void progress (int current, int max, int type);

            void reportMessage (const QString& message, int type);

        public slots:

            void abort();

        private slots:

            void verify();
    };
}

#endif