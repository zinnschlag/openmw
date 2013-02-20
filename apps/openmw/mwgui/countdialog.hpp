/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_COUNTDIALOG_H
#define MWGUI_COUNTDIALOG_H

#include "window_base.hpp"

namespace MWGui
{
    class CountDialog : public WindowModal
    {
        public:
            CountDialog(MWBase::WindowManager& parWindowManager);
            void open(const std::string& item, const std::string& message, const int maxCount);

            typedef MyGUI::delegates::CMultiDelegate2<MyGUI::Widget*, int> EventHandle_WidgetInt;

            /** Event : Ok button was clicked.\n
                signature : void method(MyGUI::Widget* _sender, int _count)\n
            */
            EventHandle_WidgetInt eventOkClicked;

        private:
            MyGUI::ScrollBar* mSlider;
            MyGUI::EditBox* mItemEdit;
            MyGUI::TextBox* mItemText;
            MyGUI::TextBox* mLabelText;
            MyGUI::Button* mOkButton;
            MyGUI::Button* mCancelButton;

            void onCancelButtonClicked(MyGUI::Widget* _sender);
            void onOkButtonClicked(MyGUI::Widget* _sender);
            void onEditTextChange(MyGUI::EditBox* _sender);
            void onSliderMoved(MyGUI::ScrollBar* _sender, size_t _position);
    };

}

#endif
