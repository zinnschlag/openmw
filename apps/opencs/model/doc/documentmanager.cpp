/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "documentmanager.hpp"

#include <algorithm>
#include <stdexcept>

#include "document.hpp"

CSMDoc::DocumentManager::DocumentManager() {}

CSMDoc::DocumentManager::~DocumentManager()
{
    for (std::vector<Document *>::iterator iter (mDocuments.begin()); iter!=mDocuments.end(); ++iter)
        delete *iter;
}

CSMDoc::Document *CSMDoc::DocumentManager::addDocument (const std::vector<boost::filesystem::path>& files,
    bool new_)
{
    Document *document = new Document (files, new_);

    mDocuments.push_back (document);

    return document;
}

bool CSMDoc::DocumentManager::removeDocument (Document *document)
{
    std::vector<Document *>::iterator iter = std::find (mDocuments.begin(), mDocuments.end(), document);

    if (iter==mDocuments.end())
            throw std::runtime_error ("removing invalid document");

    mDocuments.erase (iter);
    delete document;

    return mDocuments.empty();
}