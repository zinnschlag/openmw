/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "enchantingdialog.hpp"


namespace MWGui
{


    EnchantingDialog::EnchantingDialog(MWBase::WindowManager &parWindowManager)
        : WindowBase("openmw_enchanting_dialog.layout", parWindowManager)
        , EffectEditorBase(parWindowManager)
    {
        getWidget(mCancelButton, "CancelButton");
        getWidget(mAvailableEffectsList, "AvailableEffects");
        getWidget(mUsedEffectsView, "UsedEffects");

        setWidgets(mAvailableEffectsList, mUsedEffectsView);

        mCancelButton->eventMouseButtonClick += MyGUI::newDelegate(this, &EnchantingDialog::onCancelButtonClicked);
    }

    void EnchantingDialog::open()
    {
        center();
    }

    void EnchantingDialog::startEnchanting (MWWorld::Ptr actor)
    {
        mPtr = actor;

        startEditing ();
    }

    void EnchantingDialog::onReferenceUnavailable ()
    {
        mWindowManager.removeGuiMode (GM_Dialogue);
        mWindowManager.removeGuiMode (GM_Enchanting);
    }

    void EnchantingDialog::onCancelButtonClicked(MyGUI::Widget* sender)
    {
        mWindowManager.removeGuiMode (GM_Enchanting);
    }
}
