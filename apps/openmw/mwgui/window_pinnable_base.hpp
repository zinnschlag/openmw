/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_WINDOW_PINNABLE_BASE_H
#define MWGUI_WINDOW_PINNABLE_BASE_H

#include "window_base.hpp"

namespace MWGui
{
    class WindowManager;

    class WindowPinnableBase: public WindowBase
    {
    public:
        WindowPinnableBase(const std::string& parLayout, MWBase::WindowManager& parWindowManager);
        bool pinned() { return mPinned; }

    private:
        void onPinButtonClicked(MyGUI::Widget* _sender);

    protected:
        virtual void onPinToggled() = 0;

        MyGUI::Widget* mPinButton;
        bool mPinned;
        bool mVisible;
    };
}

#endif
