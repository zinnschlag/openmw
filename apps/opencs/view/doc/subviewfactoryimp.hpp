/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_DOC_SUBVIEWFACTORYIMP_H
#define CSV_DOC_SUBVIEWFACTORYIMP_H

#include "../../model/doc/document.hpp"

#include "subviewfactory.hpp"

namespace CSVDoc
{
    template<class SubViewT>
    class SubViewFactory : public SubViewFactoryBase
    {
        public:

            virtual CSVDoc::SubView *makeSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document);
    };

    template<class SubViewT>
    CSVDoc::SubView *SubViewFactory<SubViewT>::makeSubView (const CSMWorld::UniversalId& id,
        CSMDoc::Document& document)
    {
        return new SubViewT (id, document);
    }

    template<class SubViewT>
    class SubViewFactoryWithCreateFlag : public SubViewFactoryBase
    {
        bool mCreateAndDelete;

        public:

            SubViewFactoryWithCreateFlag (bool createAndDelete);

            virtual CSVDoc::SubView *makeSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document);
    };

    template<class SubViewT>
    SubViewFactoryWithCreateFlag<SubViewT>::SubViewFactoryWithCreateFlag (bool createAndDelete)
    : mCreateAndDelete (createAndDelete)
    {}

    template<class SubViewT>
    CSVDoc::SubView *SubViewFactoryWithCreateFlag<SubViewT>::makeSubView (const CSMWorld::UniversalId& id,
        CSMDoc::Document& document)
    {
        return new SubViewT (id, document, mCreateAndDelete);
    }
}

#endif