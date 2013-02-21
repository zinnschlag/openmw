/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "exposedwindow.hpp"

#include "MyGUI_Window.h"

namespace MWGui
{
    MyGUI::VectorWidgetPtr ExposedWindow::getSkinWidgetsByName (const std::string &name)
    {
        return MyGUI::Widget::getSkinWidgetsByName (name);
    }

    MyGUI::Widget* ExposedWindow::getSkinWidget(const std::string & _name, bool _throw)
    {
        MyGUI::VectorWidgetPtr widgets = getSkinWidgetsByName (_name);

        if (widgets.empty())
        {
            MYGUI_ASSERT( ! _throw, "widget name '" << _name << "' not found in skin of layout '" << getName() << "'");
            return nullptr;
        }
        else
        {
            return widgets[0];
        }
    }
}
