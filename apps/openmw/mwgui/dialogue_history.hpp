/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_DIALOGE_HISTORY_H
#define MWGUI_DIALOGE_HISTORY_H
#include <openengine/gui/layout.hpp>

namespace MWGui
{
    class DialogueHistory : public MyGUI::EditBox
    {
        MYGUI_RTTI_DERIVED( DialogueHistory )
        public:
            Widget* getClient() { return mClient; }
            MyGUI::UString getColorAtPos(size_t _pos);
            MyGUI::UString getColorTextAt(size_t _pos);
            void addDialogHeading(const MyGUI::UString& parText);
            void addDialogText(const MyGUI::UString& parText);
    };
}
#endif

