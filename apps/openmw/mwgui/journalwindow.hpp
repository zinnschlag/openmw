/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_JOURNAL_H
#define MWGUI_JOURNAL_H

#include <sstream>
#include <set>
#include <string>
#include <utility>

#include "window_base.hpp"
#include "imagebutton.hpp"

namespace MWGui
{
    class JournalWindow : public WindowBase
    {
        public:
            JournalWindow(MWBase::WindowManager& parWindowManager);
            virtual void open();
            virtual void close();

        private:
            void displayLeftText(std::string text);
            void displayRightText(std::string text);


            /**
            *Called when next/prev button is used.
            */
            void notifyNextPage(MyGUI::Widget* _sender);
            void notifyPrevPage(MyGUI::Widget* _sender);

            MyGUI::EditPtr mLeftTextWidget;
            MyGUI::EditPtr mRightTextWidget;
            MWGui::ImageButton* mPrevBtn;
            MWGui::ImageButton* mNextBtn;
            std::vector<std::string> mLeftPages;
            std::vector<std::string> mRightPages;
            int mPageNumber; //store the number of the current left page
    };

}

#endif
