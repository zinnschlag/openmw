/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_TravelWINDOW_H
#define MWGUI_TravelWINDOW_H

#include "container.hpp"
#include "window_base.hpp"

#include "../mwworld/ptr.hpp"

namespace MyGUI
{
  class Gui;
  class Widget;
}

namespace MWGui
{
    class WindowManager;
}


namespace MWGui
{
    class TravelWindow : public ReferenceInterface, public WindowBase
    {
        public:
            TravelWindow(MWBase::WindowManager& parWindowManager);

            void startTravel(const MWWorld::Ptr& actor);

        protected:
            MyGUI::Button* mCancelButton;
            MyGUI::TextBox* mPlayerGold;
            MyGUI::TextBox* mDestinations;
            MyGUI::TextBox* mSelect;

            MyGUI::ScrollView* mDestinationsView;

            std::map<MyGUI::Widget*, std::string> mDestinationsWidgetMap;

            void onCancelButtonClicked(MyGUI::Widget* _sender);
            void onTravelButtonClick(MyGUI::Widget* _sender);
            void onMouseWheel(MyGUI::Widget* _sender, int _rel);
            void addDestination(const std::string& destinationID,ESM::Position pos,bool interior);
            void clearDestinations();
            int mLastPos,mCurrentY;

            static const int sLineHeight;

            void updateLabels();

            virtual void onReferenceUnavailable();
    };
}

#endif
