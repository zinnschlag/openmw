/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_LEVELUPDIALOG_H
#define MWGUI_LEVELUPDIALOG_H

#include "window_base.hpp"

namespace MWGui
{

    class LevelupDialog : public WindowBase
    {
    public:
        LevelupDialog(MWBase::WindowManager& parWindowManager);

        virtual void open();

    private:
        MyGUI::Button* mOkButton;
        MyGUI::ImageBox* mClassImage;
        MyGUI::TextBox* mLevelText;

        std::vector<MyGUI::Button*> mAttributes;
        std::vector<MyGUI::TextBox*> mAttributeValues;
        std::vector<MyGUI::TextBox*> mAttributeMultipliers;
        std::vector<MyGUI::ImageBox*> mCoins;

        std::vector<int> mSpentAttributes;

        void onOkButtonClicked (MyGUI::Widget* sender);
        void onAttributeClicked (MyGUI::Widget* sender);

        void assignCoins();
        void resetCoins();

        void setAttributeValues();
    };

}

#endif
