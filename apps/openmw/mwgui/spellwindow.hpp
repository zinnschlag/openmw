/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_SPELLWINDOW_H
#define MWGUI_SPELLWINDOW_H

#include "window_pinnable_base.hpp"

namespace MWGui
{
    class SpellWindow : public WindowPinnableBase
    {
    public:
        SpellWindow(MWBase::WindowManager& parWindowManager);

        void updateSpells();

    protected:
        MyGUI::ScrollView* mSpellView;
        MyGUI::Widget* mEffectBox;

        int mHeight;
        int mWidth;

        std::string mSpellToDelete;

        void addGroup(const std::string& label, const std::string& label2);

        int estimateHeight(int numSpells) const;

        void onWindowResize(MyGUI::Window* _sender);
        void onEnchantedItemSelected(MyGUI::Widget* _sender);
        void onSpellSelected(MyGUI::Widget* _sender);
        void onMouseWheel(MyGUI::Widget* _sender, int _rel);
        void onDeleteSpellAccept();

        virtual void onPinToggled();
        virtual void open();
    };
}

#endif
