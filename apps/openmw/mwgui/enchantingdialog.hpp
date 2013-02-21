/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_ENCHANTINGDIALOG_H
#define MWGUI_ENCHANTINGDIALOG_H

#include "window_base.hpp"
#include "referenceinterface.hpp"
#include "spellcreationdialog.hpp"

#include "../mwbase/windowmanager.hpp"

namespace MWGui
{

    class EnchantingDialog : public WindowBase, public ReferenceInterface, public EffectEditorBase
    {
    public:
        EnchantingDialog(MWBase::WindowManager& parWindowManager);

        virtual void open();
        void startEnchanting(MWWorld::Ptr actor);

    protected:
        virtual void onReferenceUnavailable();

        void onCancelButtonClicked(MyGUI::Widget* sender);

        MyGUI::Button* mCancelButton;
    };

}

#endif
