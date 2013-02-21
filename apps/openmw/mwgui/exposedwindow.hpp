/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_EXPOSEDWINDOW_H
#define MWGUI_EXPOSEDWINDOW_H

#include "MyGUI_Window.h"

namespace MWGui
{

    /**
     * @brief subclass to provide access to some Widget internals.
     */
    class ExposedWindow : public MyGUI::Window
    {
        MYGUI_RTTI_DERIVED(ExposedWindow)

    public:
        MyGUI::VectorWidgetPtr getSkinWidgetsByName (const std::string &name);

        MyGUI::Widget* getSkinWidget(const std::string & _name, bool _throw = true);
        ///< Get a widget defined in the inner skin of this window.
    };

}

#endif

