/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "window_base.hpp"

#include <components/settings/settings.hpp>

#include "../mwbase/windowmanager.hpp"

using namespace MWGui;

WindowBase::WindowBase(const std::string& parLayout, MWBase::WindowManager& parWindowManager)
  : Layout(parLayout)
  , mWindowManager(parWindowManager)
{
}

void WindowBase::setVisible(bool visible)
{
    bool wasVisible = mMainWidget->getVisible();
    mMainWidget->setVisible(visible);

    if (visible)
        open();
    else if (wasVisible && !visible)
        close();
}

void WindowBase::center()
{
    // Centre dialog

    // MyGUI::IntSize gameWindowSize = MyGUI::RenderManager::getInstance().getViewSize();
    // Note by scrawl: The following works more reliably in the case when the window was _just_
    // resized and MyGUI RenderManager doesn't know about the new size yet
    MyGUI::IntSize gameWindowSize = MyGUI::IntSize(Settings::Manager::getInt("resolution x", "Video"),
            Settings::Manager::getInt("resolution y", "Video"));

    MyGUI::IntCoord coord = mMainWidget->getCoord();
    coord.left = (gameWindowSize.width - coord.width)/2;
    coord.top = (gameWindowSize.height - coord.height)/2;
    mMainWidget->setCoord(coord);
}

WindowModal::WindowModal(const std::string& parLayout, MWBase::WindowManager& parWindowManager)
    : WindowBase(parLayout, parWindowManager)
{
}

void WindowModal::open()
{
    MyGUI::InputManager::getInstance ().addWidgetModal (mMainWidget);
}

void WindowModal::close()
{
    MyGUI::InputManager::getInstance ().removeWidgetModal (mMainWidget);
}
