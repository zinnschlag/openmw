/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_DOC_SUBVIEWFACTORY_H
#define CSV_DOC_SUBVIEWFACTORY_H

#include <map>

#include "../../model/world/universalid.hpp"

namespace CSMDoc
{
    class Document;
}

namespace CSVDoc
{
    class SubView;

    class SubViewFactoryBase
    {
            // not implemented
            SubViewFactoryBase (const SubViewFactoryBase&);
            SubViewFactoryBase& operator= (const SubViewFactoryBase&);

        public:

            SubViewFactoryBase();

            virtual ~SubViewFactoryBase();

            virtual SubView *makeSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document) = 0;
            ///< The ownership of the returned sub view is not transferred.
    };

    class SubViewFactoryManager
    {
            std::map<CSMWorld::UniversalId::Type, SubViewFactoryBase *> mSubViewFactories;

            // not implemented
            SubViewFactoryManager (const SubViewFactoryManager&);
            SubViewFactoryManager& operator= (const SubViewFactoryManager&);

        public:

            SubViewFactoryManager();

            ~SubViewFactoryManager();

            void add (const CSMWorld::UniversalId::Type& id, SubViewFactoryBase *factory);
            ///< The ownership of \a factory is transferred to this.

            SubView *makeSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document);
            ///< The ownership of the returned sub view is not transferred.
    };
}

#endif
