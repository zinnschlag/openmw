/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "itemselection.hpp"

namespace MWGui
{

    ItemSelectionDialog::ItemSelectionDialog(const std::string &label, ContainerBase::Filter filter, MWBase::WindowManager& parWindowManager)
        : ContainerBase(NULL)
        , WindowModal("openmw_itemselection_dialog.layout", parWindowManager)
    {
        mFilter = filter;

        MyGUI::ScrollView* itemView;
        MyGUI::Widget* containerWidget;
        getWidget(containerWidget, "Items");
        getWidget(itemView, "ItemView");
        setWidgets(containerWidget, itemView);

        MyGUI::TextBox* l;
        getWidget(l, "Label");
        l->setCaptionWithReplacing (label);

        MyGUI::Button* cancelButton;
        getWidget(cancelButton, "CancelButton");
        cancelButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ItemSelectionDialog::onCancelButtonClicked);

        center();
    }

    void ItemSelectionDialog::onSelectedItemImpl(MWWorld::Ptr item)
    {
        eventItemSelected(item);
    }

    void ItemSelectionDialog::onCancelButtonClicked(MyGUI::Widget* sender)
    {
        eventDialogCanceled();
    }

}
