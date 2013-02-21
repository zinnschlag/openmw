/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_SpellBuyingWINDOW_H
#define MWGUI_SpellBuyingWINDOW_H

#include "window_base.hpp"
#include "referenceinterface.hpp"

namespace MyGUI
{
  class Gui;
  class Widget;
}

namespace MWGui
{
    class WindowManager;
}


namespace MWGui
{
    class SpellBuyingWindow : public ReferenceInterface, public WindowBase
    {
        public:
            SpellBuyingWindow(MWBase::WindowManager& parWindowManager);

            void startSpellBuying(const MWWorld::Ptr& actor);

        protected:
            MyGUI::Button* mCancelButton;
            MyGUI::TextBox* mPlayerGold;
            MyGUI::TextBox* mSpells;
            MyGUI::TextBox* mSelect;

            MyGUI::ScrollView* mSpellsView;

            std::map<MyGUI::Widget*, std::string> mSpellsWidgetMap;

            void onCancelButtonClicked(MyGUI::Widget* _sender);
            void onSpellButtonClick(MyGUI::Widget* _sender);
            void onMouseWheel(MyGUI::Widget* _sender, int _rel);
            void addSpell(const std::string& spellID);
            void clearSpells();
            int mLastPos,mCurrentY;

            static const int sLineHeight;

            void updateLabels();

            virtual void onReferenceUnavailable();
    };
}

#endif
