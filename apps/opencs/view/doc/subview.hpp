/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_DOC_SUBVIEW_H
#define CSV_DOC_SUBVIEW_H

#include "../../model/doc/document.hpp"

#include "../../model/world/universalid.hpp"

#include "subviewfactory.hpp"

#include <QDockWidget>

class QUndoStack;

namespace CSMWorld
{
    class Data;
}

namespace CSVDoc
{
    class SubView : public QDockWidget
    {
            Q_OBJECT

            CSMWorld::UniversalId mUniversalId;

            // not implemented
            SubView (const SubView&);
            SubView& operator= (SubView&);

        public:

            SubView (const CSMWorld::UniversalId& id);

            CSMWorld::UniversalId getUniversalId() const;

            virtual void setEditLock (bool locked) = 0;

        signals:

            void focusId (const CSMWorld::UniversalId& universalId);
    };
}

#endif