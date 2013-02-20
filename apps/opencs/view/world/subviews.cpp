/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "subviews.hpp"

#include "../doc/subviewfactoryimp.hpp"

#include "tablesubview.hpp"
#include "dialoguesubview.hpp"

void CSVWorld::addSubViewFactories (CSVDoc::SubViewFactoryManager& manager)
{
    manager.add (CSMWorld::UniversalId::Type_Globals,
        new CSVDoc::SubViewFactoryWithCreateFlag<TableSubView> (true));

    manager.add (CSMWorld::UniversalId::Type_Gmsts,
        new CSVDoc::SubViewFactoryWithCreateFlag<TableSubView> (false));

    manager.add (CSMWorld::UniversalId::Type_Global,
        new CSVDoc::SubViewFactoryWithCreateFlag<DialogueSubView> (true));
}