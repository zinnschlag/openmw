/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "window_pinnable_base.hpp"

#include "../mwbase/windowmanager.hpp"

#include "exposedwindow.hpp"

using namespace MWGui;

WindowPinnableBase::WindowPinnableBase(const std::string& parLayout, MWBase::WindowManager& parWindowManager)
  : WindowBase(parLayout, parWindowManager), mPinned(false), mVisible(false)
{
    ExposedWindow* window = static_cast<ExposedWindow*>(mMainWidget);
    mPinButton = window->getSkinWidget ("Button");

    mPinButton->eventMouseButtonClick += MyGUI::newDelegate(this, &WindowPinnableBase::onPinButtonClicked);
}

void WindowPinnableBase::onPinButtonClicked(MyGUI::Widget* _sender)
{
    mPinned = !mPinned;

    if (mPinned)
        mPinButton->changeWidgetSkin ("PinDown");
    else
        mPinButton->changeWidgetSkin ("PinUp");

    onPinToggled();
}
