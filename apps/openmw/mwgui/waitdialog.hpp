/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_WAIT_DIALOG_H
#define MWGUI_WAIT_DIALOG_H

#include "window_base.hpp"

namespace MWGui
{

    class WaitDialogProgressBar : public WindowBase
    {
    public:
        WaitDialogProgressBar(MWBase::WindowManager& parWindowManager);

        virtual void open();

        void setProgress(int cur, int total);

    protected:
        MyGUI::ProgressBar* mProgressBar;
        MyGUI::TextBox* mProgressText;
    };

    class WaitDialog : public WindowBase
    {
    public:
        WaitDialog(MWBase::WindowManager& parWindowManager);

        virtual void open();

        void onFrame(float dt);

        void bedActivated() { setCanRest(true); }

        bool getSleeping() { return mWaiting && mSleeping; }
        void wakeUp();

    protected:
        MyGUI::TextBox* mDateTimeText;
        MyGUI::TextBox* mRestText;
        MyGUI::TextBox* mHourText;
        MyGUI::ScrollBar* mHourSlider;
        MyGUI::Button* mUntilHealedButton;
        MyGUI::Button* mWaitButton;
        MyGUI::Button* mCancelButton;

        bool mWaiting;
        bool mSleeping;
        int mCurHour;
        int mHours;
        int mManualHours; // stores the hours to rest selected via slider
        float mRemainingTime;

        WaitDialogProgressBar mProgressBar;

        void onUntilHealedButtonClicked(MyGUI::Widget* sender);
        void onWaitButtonClicked(MyGUI::Widget* sender);
        void onCancelButtonClicked(MyGUI::Widget* sender);
        void onHourSliderChangedPosition(MyGUI::ScrollBar* sender, size_t position);

        void setCanRest(bool canRest);

        void startWaiting(int hoursToWait);
        void stopWaiting();
    };

}

#endif
