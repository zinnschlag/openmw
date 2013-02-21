/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_IMAGEBUTTON_H
#define MWGUI_IMAGEBUTTON_H

#include "MyGUI_ImageBox.h"

namespace MWGui
{

    /**
     * @brief allows using different image textures depending on the button state
     */
    class ImageButton : public MyGUI::ImageBox
    {
        MYGUI_RTTI_DERIVED(ImageButton)

    public:
        MyGUI::IntSize getRequestedSize();

    protected:
        virtual void setPropertyOverride(const std::string& _key, const std::string& _value);
        virtual void onMouseLostFocus(MyGUI::Widget* _new);
        virtual void onMouseSetFocus(MyGUI::Widget* _old);
        virtual void onMouseButtonPressed(int _left, int _top, MyGUI::MouseButton _id);
        virtual void onMouseButtonReleased(int _left, int _top, MyGUI::MouseButton _id);

        std::string mImageHighlighted;
        std::string mImageNormal;
        std::string mImagePushed;
    };

}

#endif
