/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_SCROLLWINDOW_H
#define MWGUI_SCROLLWINDOW_H

#include "window_base.hpp"
#include "imagebutton.hpp"

#include "../mwworld/ptr.hpp"

namespace MWGui
{
    class ScrollWindow : public WindowBase
    {
        public:
            ScrollWindow (MWBase::WindowManager& parWindowManager);

            void open (MWWorld::Ptr scroll);
            void setTakeButtonShow(bool show);
            void setInventoryAllowed(bool allowed);

        protected:
            void onCloseButtonClicked (MyGUI::Widget* _sender);
            void onTakeButtonClicked (MyGUI::Widget* _sender);

        private:
            MWGui::ImageButton* mCloseButton;
            MWGui::ImageButton* mTakeButton;
            MyGUI::ScrollView* mTextView;

            MWWorld::Ptr mScroll;

            bool mTakeButtonShow;
            bool mTakeButtonAllowed;

    };

}

#endif
