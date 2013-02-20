/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "container.hpp"

#include "../mwworld/ptr.hpp"

namespace MWGui
{

    class ItemSelectionDialog : public ContainerBase, public WindowModal
    {
    public:
        ItemSelectionDialog(const std::string& label, ContainerBase::Filter filter, MWBase::WindowManager& parWindowManager);

        typedef MyGUI::delegates::CMultiDelegate0 EventHandle_Void;
        typedef MyGUI::delegates::CMultiDelegate1<MWWorld::Ptr> EventHandle_Item;

        EventHandle_Item eventItemSelected;
        EventHandle_Void eventDialogCanceled;


    private:
        virtual void onReferenceUnavailable() { ; }

        virtual void onSelectedItemImpl(MWWorld::Ptr item);

        void onCancelButtonClicked(MyGUI::Widget* sender);
    };

}
