/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include <openengine/gui/layout.hpp>

#include "imagebutton.hpp"

namespace MWGui
{

    class MainMenu : public OEngine::GUI::Layout
    {
    public:
        MainMenu(int w, int h);

        void onResChange(int w, int h);

    private:
        MyGUI::Widget* mButtonBox;

        std::map<std::string, MWGui::ImageButton*> mButtons;

        void onButtonClicked (MyGUI::Widget* sender);
    };

}
