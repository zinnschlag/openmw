/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_BOOKWINDOW_H
#define MWGUI_BOOKWINDOW_H

#include "window_base.hpp"

#include "../mwworld/ptr.hpp"

#include "imagebutton.hpp"

namespace MWGui
{
    class BookWindow : public WindowBase
    {
        public:
            BookWindow(MWBase::WindowManager& parWindowManager);

            void open(MWWorld::Ptr book);
            void setTakeButtonShow(bool show);

            void setInventoryAllowed(bool allowed);

        protected:
            void onNextPageButtonClicked (MyGUI::Widget* sender);
            void onPrevPageButtonClicked (MyGUI::Widget* sender);
            void onCloseButtonClicked (MyGUI::Widget* sender);
            void onTakeButtonClicked (MyGUI::Widget* sender);

            void updatePages();
            void clearPages();

        private:
            MWGui::ImageButton* mCloseButton;
            MWGui::ImageButton* mTakeButton;
            MWGui::ImageButton* mNextPageButton;
            MWGui::ImageButton* mPrevPageButton;
            MyGUI::TextBox* mLeftPageNumber;
            MyGUI::TextBox* mRightPageNumber;
            MyGUI::Widget* mLeftPage;
            MyGUI::Widget* mRightPage;

            unsigned int mCurrentPage; // 0 is first page
            std::vector<MyGUI::Widget*> mPages;

            MWWorld::Ptr mBook;

            bool mTakeButtonShow;
            bool mTakeButtonAllowed;
    };

}

#endif
