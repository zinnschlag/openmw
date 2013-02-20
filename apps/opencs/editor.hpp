/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CS_EDITOR_H
#define CS_EDITOR_H

#include <QObject>

#include "model/doc/documentmanager.hpp"

#include "view/doc/viewmanager.hpp"
#include "view/doc/startup.hpp"
#include "view/doc/opendialog.hpp"

namespace CS
{
    class Editor : public QObject
    {
            Q_OBJECT

            int mNewDocumentIndex; ///< \todo remove when the proper new document dialogue is implemented.

            CSMDoc::DocumentManager mDocumentManager;
            CSVDoc::ViewManager mViewManager;
            CSVDoc::StartupDialogue mStartup;
            OpenDialog mOpenDialog;

            // not implemented
            Editor (const Editor&);
            Editor& operator= (const Editor&);

        public:

            Editor();

            int run();
            ///< \return error status

        private slots:

            void createDocument();

            void loadDocument();
            void openFiles();
    };
}

#endif