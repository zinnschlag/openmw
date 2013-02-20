/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_TEXT_INPUT_H
#define MWGUI_TEXT_INPUT_H

#include "window_base.hpp"

namespace MWGui
{
    class WindowManager;
}

/*
 */

namespace MWGui
{
    class TextInputDialog : public WindowBase
    {
    public:
        TextInputDialog(MWBase::WindowManager& parWindowManager);

        std::string getTextInput() const { return mTextEdit ? mTextEdit->getOnlyText() : ""; }
        void setTextInput(const std::string &text) { if (mTextEdit) mTextEdit->setOnlyText(text); }

        void setNextButtonShow(bool shown);
        void setTextLabel(const std::string &label);
        virtual void open();

    protected:
        void onOkClicked(MyGUI::Widget* _sender);
        void onTextAccepted(MyGUI::Edit* _sender);

    private:
        MyGUI::EditPtr mTextEdit;
    };
}
#endif
