/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_DOC_VIEWMANAGER_H
#define CSV_DOC_VIEWMANAGER_H

#include <vector>

#include <QObject>

namespace CSMDoc
{
    class Document;
    class DocumentManager;
}

namespace CSVWorld
{
    class CommandDelegateFactoryCollection;
}

namespace CSVDoc
{
    class View;

    class ViewManager : public QObject
    {
            Q_OBJECT

            CSMDoc::DocumentManager& mDocumentManager;
            std::vector<View *> mViews;
            CSVWorld::CommandDelegateFactoryCollection *mDelegateFactories;

            // not implemented
            ViewManager (const ViewManager&);
            ViewManager& operator= (const ViewManager&);

            void updateIndices();

        public:

            ViewManager (CSMDoc::DocumentManager& documentManager);

            virtual ~ViewManager();

            View *addView (CSMDoc::Document *document);
            ///< The ownership of the returned view is not transferred.

            int countViews (const CSMDoc::Document *document) const;
            ///< Return number of views for \a document.

            bool closeRequest (View *view);

        signals:

            void newDocumentRequest();

            void loadDocumentRequest();

        private slots:

            void documentStateChanged (int state, CSMDoc::Document *document);

            void progress (int current, int max, int type, int threads, CSMDoc::Document *document);
    };

}

#endif