/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSM_DOC_DOCUMENTMGR_H
#define CSM_DOC_DOCUMENTMGR_H

#include <vector>
#include <string>

#include <boost/filesystem/path.hpp>

namespace CSMDoc
{
    class Document;

    class DocumentManager
    {
            std::vector<Document *> mDocuments;

            DocumentManager (const DocumentManager&);
            DocumentManager& operator= (const DocumentManager&);

        public:

            DocumentManager();

            ~DocumentManager();

            Document *addDocument (const std::vector<boost::filesystem::path>& files, bool new_);
            ///< The ownership of the returned document is not transferred to the caller.
            ///
            /// \param new_ Do not load the last content file in \a files and instead create in an
            /// appropriate way.

            bool removeDocument (Document *document);
            ///< \return last document removed?
    };
}

#endif