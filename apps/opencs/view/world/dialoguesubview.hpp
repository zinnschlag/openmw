/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_WORLD_DIALOGUESUBVIEW_H
#define CSV_WORLD_DIALOGUESUBVIEW_H

#include "../doc/subview.hpp"

class QDataWidgetMapper;

namespace CSMDoc
{
    class Document;
}

namespace CSVWorld
{
    class DialogueSubView : public CSVDoc::SubView
    {
            QDataWidgetMapper *mWidgetMapper;

        public:

            DialogueSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document, bool createAndDelete);

            virtual void setEditLock (bool locked);
    };
}

#endif