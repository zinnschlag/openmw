/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_CONFIRMATIONDIALOG_H
#define MWGUI_CONFIRMATIONDIALOG_H

#include "window_base.hpp"

namespace MWGui
{
    class ConfirmationDialog : public WindowModal
    {
        public:
            ConfirmationDialog(MWBase::WindowManager& parWindowManager);
            void open(const std::string& message);

            typedef MyGUI::delegates::CMultiDelegate0 EventHandle_Void;

            /** Event : Ok button was clicked.\n
                signature : void method()\n
            */
            EventHandle_Void eventOkClicked;
            EventHandle_Void eventCancelClicked;

        private:
            MyGUI::EditBox* mMessage;
            MyGUI::Button* mOkButton;
            MyGUI::Button* mCancelButton;

            void onCancelButtonClicked(MyGUI::Widget* _sender);
            void onOkButtonClicked(MyGUI::Widget* _sender);
    };

}

#endif
